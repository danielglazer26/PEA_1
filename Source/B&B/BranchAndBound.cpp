#include <vector>
#include <iostream>
#include "../../Header/B&B/BranchAndBound.h"

///metoda odpowiadająca za odejmowanie najmniejszego elementu z wiersza
void BranchAndBound::reduceRow(int **matrixReduced, Node *node) {

    for (int i = 0; i < matrixWeights->getSize(); i++) {

        ///znajdowanie najmniejszego elementu w wierszu
        int min = INT_MAX;
        for (int j = 0; j < matrixWeights->getSize(); j++)
            min = std::min(matrixReduced[i][j], min);

        if (min != INT_MAX && min != 0) {
            ///zliczanie kosztu węzła
            node->cost += min;

            ///odejmowanie najmniejszego elementu z wiersza
            for (int j = 0; j < matrixWeights->getSize(); j++) {
                if (matrixReduced[i][j] != INT_MAX)
                    matrixReduced[i][j] -= min;
            }
        }
    }
    reduceColumn(matrixReduced, node);
}

///metoda odpowiadająca za odejmowanie najmniejszego elementu z kolumny
void BranchAndBound::reduceColumn(int **matrixReduced, Node *node) {

    for (int i = 0; i < matrixWeights->getSize(); i++) {

        ///znajdowanie najmniejszego elementu w kolumnie
        int min = INT_MAX;
        for (int j = 0; j < matrixWeights->getSize(); j++)
            min = std::min(matrixReduced[j][i], min);

        if (min != INT_MAX && min != 0) {

            ///zliczanie kosztu węzła
            node->cost += min;

            ///odejmowanie najmniejszego elementu z kolumny
            for (int j = 0; j < matrixWeights->getSize(); j++) {
                if (matrixReduced[j][i] != INT_MAX)
                    matrixReduced[j][i] -= min;
            }
        }
    }

}

///obliczanie ograniczenia dolnego dla węzła
void BranchAndBound::calculateCost(int **matrixReduced, Node *node) {
    reduceRow(matrixReduced, node);
}

///wprowadzanie nieskończoności w miejsca
void BranchAndBound::makeInfinity(Node *parent, Node *child) {

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

}

///metoda odpowiadająca za inicjację algorytmu
void BranchAndBound::branchAndBoundAlgorithm() {

    ///utworzenia węzła początkowego i dodanie go do kolejki priorytetowej
    Node *node0 = new Node(0, matrixWeights->getSize());
    node0->copyMatrix(matrix);
    calculateCost(node0->matrixReduced, node0);
    node0->path.push_back(0);
    node0->level = 0;

    ///kolejka priorytetowa z węzłem na szycie o najmniejszym koszcie
    priorityQueue.push(node0);

    solveLevel();

}

///metoda zawierająca pętlę odpowiedzialną za liczenie kosztów dla węzłów ze szczytu kolejki
void BranchAndBound::solveLevel() {

    int cost = INT_MAX;
    while (!priorityQueue.empty()) {

        ///pobieranie węzła ze szczytu kolejki
        Node *nodeTop = priorityQueue.top();

        priorityQueue.pop();

        int vertexTop = nodeTop->vertex;

        /*///wyświetlanie procentowego odchylenia od wartości optymalnej
        if(cost != nodeTop->cost) {
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
        for (int j = 0; j < matrixWeights->getSize(); j++) {
            if (nodeTop->matrixReduced[vertexTop][j] != INT_MAX) {

                ///utworzenia węzła wychodzącego z naszego węzła ze szczytu kolejki
                Node *child = new Node(j, matrixWeights->getSize());
                child->copyPath(nodeTop->path);
                child->copyMatrix(nodeTop->matrixReduced);
                makeInfinity(nodeTop, child);
                child->level = nodeTop->level + 1;

                ///obliczanie kosztów dla węzła dziecka
                child->cost += nodeTop->cost;
                calculateCost(child->matrixReduced, child);

                priorityQueue.push(child);
            }
        }

        delete nodeTop;
    }


}

///wyświetlenie cyklu rozwiązania
void BranchAndBound::showPath(const std::vector<int> &p) {

    for (int v: p) {
        std::cout << v << "->";
    }
    std::cout << 0 << "\n";
}

int **BranchAndBound::getMatrix() const {
    return matrix;
}

