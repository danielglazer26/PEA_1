#include <iostream>
#include <thread>
#include <future>
#include "../../Header/B&B/BranchAndBoundThreads.h"




/////metoda odpowiadająca za odejmowanie najmniejszego elementu z wiersza
//void BranchAndBoundThreads::reduceRow(int **matrixReduced, Node *node) {
//
//    std::vector<std::thread> threadList{};
//
//    for (int i = 0; i < matrixWeights->getSize(); i+=2) {
//        threadList.emplace_back(&BranchAndBoundThreads::countReduceRow, this, matrixReduced, node, i);
//    }
//
//    for (auto & j : threadList) {
//        j.join();
//    }
//
//    reduceColumn(matrixReduced, node);
//}
//
//void BranchAndBoundThreads::countReduceRow(int **matrixReduced, Node *node,
//                                           int i) {///znajdowanie najmniejszego elementu w wierszu
//    int min = INT_MAX;
//    for (int j = 0; j < matrixWeights->getSize(); j++)
//        min = std::min(matrixReduced[i][j], min);
//
//    if (min != INT_MAX && min != 0) {
//        ///zliczanie kosztu węzła
//        node->cost += min;
//
//        ///odejmowanie najmniejszego elementu z wiersza
//        for (int j = 0; j < matrixWeights->getSize(); j++) {
//            if (matrixReduced[i][j] != INT_MAX)
//                matrixReduced[i][j] -= min;
//        }
//    }
//}
//
/////metoda odpowiadająca za odejmowanie najmniejszego elementu z kolumny
//void BranchAndBoundThreads::reduceColumn(int **matrixReduced, Node *node) {
//
//    std::vector<std::thread> threadList{};
//
//    for (int i = 0; i < matrixWeights->getSize(); i+=2) {
//        threadList.emplace_back(&BranchAndBoundThreads::countReduceColumn, this, matrixReduced, node, i);
//    }
//
//    for (auto & j : threadList) {
//        j.join();
//    }
//
//}
//
//void BranchAndBoundThreads::countReduceColumn(int **matrixReduced, Node *node,
//                                              int i) const {///znajdowanie najmniejszego elementu w kolumnie
//    int min = INT_MAX;
//    for (int j = 0; j < matrixWeights->getSize(); j++)
//        min = std::min(matrixReduced[j][i], min);
//
//    if (min != INT_MAX && min != 0) {
//
//        ///zliczanie kosztu węzła
//        node->cost += min;
//
//        ///odejmowanie najmniejszego elementu z kolumny
//        for (int j = 0; j < matrixWeights->getSize(); j++) {
//            if (matrixReduced[j][i] != INT_MAX)
//                matrixReduced[j][i] -= min;
//        }
//    }
//}


void BranchAndBoundThreads::solveLevel() {

    int numberOfThreads =  matrixWeights->getSize() % modulo == 0 ?  matrixWeights->getSize() / modulo :  matrixWeights->getSize() / modulo + 1;
    int cost = INT_MAX;
    while (!priorityQueue.empty()) {

        ///pobieranie węzła ze szczytu kolejki
        Node *nodeTop = priorityQueue.top();

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
            showPath(nodeTop->path);
            break;
        }

        ///pętla odpowiedzialna za liczenie kosztów dla węzłów
        /// wychodzących z węzła ze szczytu kolejki

        std::vector<std::thread> threadList;



        threadList.reserve(numberOfThreads);

        for (int i = 0; i < numberOfThreads; i++) {
            threadList.emplace_back(&BranchAndBoundThreads::countCostForOneNode, this, nodeTop, vertexTop, i);

        }

        for (auto &j: threadList) {
            j.join();
        }

        threadList.clear();

        delete nodeTop;
    }
}

void BranchAndBoundThreads::countCostForOneNode(Node *nodeTop, int vertexTop, int j) {
    ///utworzenia węzła wychodzącego z naszego węzła ze szczytu kolejki


    for (int i = modulo * j; i < modulo * (j + 1) && i < matrixWeights->getSize(); i++) {
        if (nodeTop->matrixReduced[vertexTop][i] != INT_MAX) {

            Node *child = new Node(i, matrixWeights->getSize());
            child->copyPath(nodeTop->path);

            makeInfinity(nodeTop, child);
            child->level = nodeTop->level + 1;

            ///obliczanie kosztów dla węzła dziecka

            child->cost += nodeTop->cost;
            calculateCost(child->matrixReduced, child);

            const std::lock_guard<std::mutex> lockGuard(queueLock);
            priorityQueue.push(child);
        }
    }


}

void BranchAndBoundThreads::branchAndBoundAlgorithm() {
    BranchAndBound::branchAndBoundAlgorithm();
}

