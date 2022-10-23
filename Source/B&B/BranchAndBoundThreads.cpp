#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include "../../Header/B&B/BranchAndBoundThreads.h"
#include "../../Header/B&B/ThreadPool.h"




/*///metoda odpowiadająca za odejmowanie najmniejszego elementu z wiersza
void BranchAndBoundThreads::reduceRow(int **matrixReduced, Node *node) {

    int numberOfThreads =  matrixWeights->getSize() % modulo == 0 ?  matrixWeights->getSize() / modulo :  matrixWeights->getSize() / modulo + 1;
    std::vector<std::thread> threadList;
    threadList.reserve(numberOfThreads);

    for (int i = 0; i < numberOfThreads; i++) {
        threadList.emplace_back(&BranchAndBoundThreads::countReduceRow, this, matrixReduced, node, i);
    }

    for (auto & j : threadList) {
        j.join();
    }

    reduceColumn(matrixReduced, node);
}

///znajdowanie najmniejszego elementu w wierszu
void BranchAndBoundThreads::countReduceRow(int **matrixReduced, Node *node,
                                           int j) {
    int min = INT_MAX;
    for (int i = modulo * j; i < modulo * (j + 1) && i < matrixWeights->getSize(); i++) {
        const std::lock_guard<std::mutex> lockGuard(queueLock);
        min = std::min(matrixReduced[j][i], min);
    }

    if (min != INT_MAX && min != 0) {
        ///zliczanie kosztu węzła
        node->cost += min;

        ///odejmowanie najmniejszego elementu z wiersza
        for (int i = modulo * j; i < modulo * (j + 1) && i < matrixWeights->getSize(); i++) {
            const std::lock_guard<std::mutex> lockGuard(queueLock);
            if (matrixReduced[j][i] != INT_MAX)
                matrixReduced[j][i] -= min;
        }
    }
}*/

/*///metoda odpowiadająca za odejmowanie najmniejszego elementu z kolumny
void BranchAndBoundThreads::reduceColumn(int **matrixReduced, Node *node) {

    int numberOfThreads =  matrixWeights->getSize() % modulo == 0 ?  matrixWeights->getSize() / modulo :  matrixWeights->getSize() / modulo + 1;
    std::vector<std::thread> threadList;
    threadList.reserve(numberOfThreads);

    for (int i = 0; i < matrixWeights->getSize(); i+=2) {
        threadList.emplace_back(&BranchAndBoundThreads::countReduceColumn, this, matrixReduced, node, i);
    }

    for (auto & j : threadList) {
        j.join();
    }

}

///znajdowanie najmniejszego elementu w kolumnie
void BranchAndBoundThreads::countReduceColumn(int **matrixReduced, Node *node,
                                              int j) {
    int min = INT_MAX;
    for (int i = modulo * j; i < modulo * (j + 1) && i < matrixWeights->getSize(); i++) {
        const std::lock_guard<std::mutex> lockGuard(queueLock);
        min = std::min(matrixReduced[j][i], min);
    }

    if (min != INT_MAX && min != 0) {

        ///zliczanie kosztu węzła
        node->cost += min;

        ///odejmowanie najmniejszego elementu z kolumny
        for (int i = modulo * j; i < modulo * (j + 1) && i < matrixWeights->getSize(); i++) {
            const std::lock_guard<std::mutex> lockGuard(queueLock);
            if (matrixReduced[j][i] != INT_MAX)
                matrixReduced[j][i] -= min;
        }
    }
}*/

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
    threadPool->Start();


    while (!priorityQueue.empty()) {


        ///pobieranie węzła ze szczytu kolejki
        std::shared_ptr<Node> nodeTop(priorityQueue.top());

        priorityQueue.pop();

        int vertexTop = nodeTop->vertex;

        ///wyświetlanie procentowego odchylenia od wartości optymalnej
        if (cost != nodeTop->cost) {
            std::cout << nodeTop->cost
                      << "   "
                      << 100 * (((float) (nodeTop->cost - matrixWeights->getOptimum()))
                                / (float) matrixWeights->getOptimum())
                      << "% \n";
            cost = nodeTop->cost;
        }

        ///sprawdzamy, czy nasz węzeł nie jest ostatnim z cyklu
        if (nodeTop->level == matrixWeights->getSize() - 1) {
            showPath(nodeTop->path);
            break;
        }

        ///pętla odpowiedzialna za liczenie kosztów dla węzłów
        /// wychodzących z węzła ze szczytu kolejki

        for (int i = 0; i < matrixWeights->getSize(); i++) {
            if (nodeTop->matrixReduced[vertexTop][i] != INT_MAX) {
                threadPool->QueueJob([this, nodeTop, i] { countCostForOneNode(nodeTop.get(), i); });
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

    const std::unique_lock<std::mutex> lockGuard(queueLock);
    priorityQueue.push(child);


}

void BranchAndBoundThreads::branchAndBoundAlgorithm() {
    BranchAndBound::branchAndBoundAlgorithm();
}


