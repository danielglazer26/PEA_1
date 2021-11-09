#include "../../Header/BF/BruteForce.h"
#include <algorithm>
#include <iostream>

///główna metoda realizująca algorytm BF
void BruteForce::bruteForceAlgorithm(int sourceVertex) {

    int source = sourceVertex;
    currentPath[0] = sourceVertex;

    ///tworzymy wektor zawierający wszystkie wierzchołki oprócz startowego
    for (int i = 0; i < matrixWeights->getSize(); i++) {
        if (i != source) {
            nodes.push_back(i);
        }
    }

    ///Pętla sprawdzająca kolejne permutacje {1,2,3,4,5}, {1,2,3,5,4} ..
    ///permutacje zawierają się w nodes
    while (std::next_permutation(nodes.begin(), nodes.end())) {

        ///obecna waga dla permutacji
        int currentWeight = 0;
        ///ustawianie wierzchołka startowego
        int j = source;

        ///obliczanie kosztu ścieżki dla permutacji
        for (int i = 0; i < matrixWeights->getSize() - 1; i++) {
            currentWeight += matrix[j][nodes[i]];
            j = nodes[i];
            currentPath[i + 1] = j;
        }
        ///dodawanie kosztu pomiędzy ostatnim wierzchołkiem a źródłem
        currentWeight += matrix[j][source];

        ///sprawdzanie, czy obecny koszt ścieżki jest mniejszy od obecnie najmniejszego
        if (currentWeight < shortest) {

            ///kopiowanie obecnej ścieżki do najkrótszej ścieżki
            std::copy(currentPath, &currentPath[matrixWeights->getSize()], shortestPath);
            shortest = currentWeight;

            ///wyświetlanie procentowego odchylenia od wartości optymalnej
            std::cout << shortest
                      << "   "
                      << 100 *
                         (((float) (shortest - matrixWeights->getOptimum()))
                          / (float) matrixWeights->getOptimum())
                      << "% \n";
        }

    }

}

///wyświetlanie najkrótszej ścieżki
void BruteForce::showTheShortestPath() {
    for (int i = 0; i < matrixWeights->getSize(); i++) {
        std::cout << shortestPath[i] << "->";
    }
    std::cout << 0 << "\n";
}

int **BruteForce::getMatrix() const {
    return matrix;
}

