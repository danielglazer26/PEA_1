#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include "../../Header/B&B/BranchAndBoundThreads.h"
#include "../../Header/B&B/ThreadPool.h"




void BranchAndBoundThreads::makeInfinity(Node *parent, Node *child) {

    ///kopiowanie zredukowanej macierzy do węzła dziecka
    child->copyMatrix(parent->matrixReduced);

    ///dodanie kosztu dostępu z wierzchołka rodzica do wierzchołka dziecka
    child->cost += child->matrixReduced[parent->vertex][child->vertex];

    ///ustawienie nieskończoności na koszcie dostępu z wierzchołka dziecka do wierzchołka rodzica
    child->matrixReduced[child->vertex][parent->vertex] = INT_MAX;

    ///uzupełnienie nieskończonościami wiersza rodzica
    std::fill_n(child->matrixReduced[parent->vertex], matrixWeights->getSize(), INT_MAX);

    ///uzupełnienie nieskończonościami kolumny dziecka
    for (int i = 0; i < matrixWeights->getSize(); i++) {
        child->matrixReduced[i][child->vertex] = INT_MAX;
    }

    child->cost += parent->cost;
}


void BranchAndBoundThreads::solveLevel() {

    int cost = INT_MAX;

    auto *threadPool = new ThreadPool();
    threadPool->start(numberOfThreads);


    while (!priorityQueue.empty()) {


        ///pobieranie węzła ze szczytu kolejki
        std::shared_ptr<Node> nodeTop(priorityQueue.top());

        priorityQueue.pop();

        int vertexTop = nodeTop->vertex;

        /*///wyświetlanie procentowego odchylenia od wartości optymalnej
        if (cost != nodeTop->cost) {
            std::cout << nodeTop->cost
                      << "   "
                      << 100 * (((float) (nodeTop->cost - matrixWeights->getOptimum()))
                                / (float) matrixWeights->getOptimum())
                      << "% \n";
            cost = nodeTop->cost;
        }*/

        ///sprawdzamy, czy nasz węzeł nie jest ostatnim z cyklu
        if (nodeTop->level == matrixWeights->getSize() - 1) {
            /*showPath(nodeTop->path);*/
            break;
        }

        ///pętla odpowiedzialna za liczenie kosztów dla węzłów
        /// wychodzących z węzła ze szczytu kolejki

        for (int i = 0; i < matrixWeights->getSize(); i++) {
            if (nodeTop->matrixReduced[vertexTop][i] != INT_MAX) {
                threadPool->queueJob([this, nodeTop, i] { countCostForOneNode(nodeTop.get(), i); });
            }
        }

        while (true) {

            if (threadPool->isEmpty() && !threadPool->checkIfThreadIsWorking())
                break;

        }

    }
}

void BranchAndBoundThreads::countCostForOneNode(Node *nodeTop, int j) {
    ///utworzenia węzła wychodzącego z naszego węzła ze szczytu kolejki

    Node *child = new Node(j, matrixWeights->getSize());
    child->copyPath(nodeTop->path);

    makeInfinity(nodeTop, child);
    child->level = nodeTop->level + 1;

    ///obliczanie kosztów dla węzła dziecka
    calculateCost(child->matrixReduced, child);

    {
        const std::unique_lock<std::mutex> lockGuard(queueLock);
        priorityQueue.push(child);
    }

}

void BranchAndBoundThreads::branchAndBoundAlgorithm() {
    BranchAndBound::branchAndBoundAlgorithm();
}

int **BranchAndBoundThreads::getMatrix() {
    return BranchAndBound::getMatrix();
}


