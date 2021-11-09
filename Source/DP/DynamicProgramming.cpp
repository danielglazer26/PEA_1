#include <climits>
#include <vector>
#include <iostream>
#include <valarray>
#include "../../Header/DP/DynamicProgramming.h"

///metoda inicjująca zbiór n-elementowy zawierający wszystkie wierzchołki oprócz początkowego
void DynamicProgramming::dynamicProgrammingAlgorithm() {


    std::vector<int> initialization;
    for (int i = 1; i < matrixWeights->getSize(); i++) {
        initialization.push_back(i);

    }
    ///tworzenia węzła początkowego
    NodeDP *node = new NodeDP(initialization, 0);

    ///uruchomienia algorytmu rekurencyjnego
    findingMinimum(node);

    showAnswer(node);

}

///metoda wyświetlająca długość cyklu, PRD i cykl dla algorytmu DP
void DynamicProgramming::showAnswer(NodeDP *node) {

    std::cout << node->value
              << "   "
              << 100 * (((float) (node->value - matrixWeights->getOptimum()))
                        / (float) matrixWeights->getOptimum())
              << "% \n";
    auto n_i = node;
    while (n_i->minNode != nullptr) {
        std::cout << n_i->vertex << "->";
        n_i = n_i->minNode;
    }
    std::cout << n_i->vertex << "->" << node->vertex <<"\n";
}

///metoda odpowiadająca za znajdowanie minimum dla poszczególnych węzłów
void DynamicProgramming::findingMinimum(NodeDP *n) {

    ///pętla odpowiedzialna za tworzenie kolejnych mniejszych zbiorów
    /// i liczenie minimów dla kolejnych węzłów
    for (int i = 0; i < n->S.size(); i++) {

        ///tworzenie wektora z którego usuwamy numer poszczególnego węzła
        std::vector<int> smaller = n->S;
        int a = n->S[i];
        auto j = smaller.begin();
        std::advance(j, i);
        smaller.erase(j);

        ///tworzenie węzła dziecka, który zawiera zmniejszony zbiór
        /// o jeden element względem rodzica
        auto *child = new NodeDP(smaller, a);

        if (!n->S.empty()) {

            ///wywołanie metody dla węzła potomka
            findingMinimum(child);

            ///szukanie minimum dla węzła rodzica na podstawie kosztów uzyskanych przez potomków
            int value = matrix[n->vertex][a] + child->value;
            if (n->value > value) {
                n->value = value;
                delete n->minNode;
                n->minNode = child;
            }
        }

    }
    ///przypadek w którym nasz węzeł prowadzi tylko do wierzchołka startowego
    if (n->S.empty())
        n->value = matrix[n->vertex][0];

}

int **DynamicProgramming::getMatrix() const {
    return matrix;
}


