#include "../Header/BruteForce.h"
#include <algorithm>
#include <iostream>

void BruteForce::bruteForceAlgorithm(int sourceVertex) {

    int source = sourceVertex;
    currentPath[0] = sourceVertex;

    for (int i = 0; i < matrixWeights->getSize(); i++) {
        if (i != source) {
            nodes.push_back(i);
        }
    }

    while (std::next_permutation(nodes.begin(), nodes.end())) {

        int currentWeight = 0;
        int j = source;
        for (int i = 0; i < matrixWeights->getSize() - 1; i++) {
            currentWeight += matrix[j][nodes[i]];
            j = nodes[i];
            currentPath[i + 1] = j;
        }
        currentWeight += matrix[j][source];

        if (currentWeight < shortest) {
            std::copy(currentPath, &currentPath[matrixWeights->getSize()], shortestPath);
            shortest = currentWeight;
            std::cout << shortest
            << "   "
            << 100 * (shortest - matrixWeights->getOptimum())/ matrixWeights->getOptimum()
            << "% \n";
        }

        iteration++;
    }

}

void BruteForce::showTheShortestPath() {
    for (int i = 0; i < matrixWeights->getSize(); i++) {
        std::cout << shortestPath[i] << "->";
    }
    std::cout << 0 << "\n";
}

