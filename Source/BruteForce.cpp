#include "../Header/BruteForce.h"
#include <algorithm>
#include <iostream>

void BruteForce::bruteForceAlgorithm(int sourceVertex) {

    int source = sourceVertex;
    currentPath[0] = sourceVertex;

    for (int i = 0; i < gr->getVerticesNumber(); i++) {
        if (i != source) {
            nodes.push_back(i);
        }
    }

    while (std::next_permutation(nodes.begin(), nodes.end())) {

        int currentWeight = 0;
        int j = source;
        for (int i = 0; i < gr->getVerticesNumber() - 1; i++) {
            currentWeight += matrix[j][nodes[i]];
            j = nodes[i];
            currentPath[i + 1] = j;
        }
        currentWeight += matrix[j][source];

        if (currentWeight < shortest) {
            std::copy(currentPath, &currentPath[gr->getVerticesNumber() - 1], shortestPath);
            shortest = currentWeight;
            std::cout << shortest << "   " << 100 * (shortest - gr->getOptimum())/ gr->getOptimum() << "% \n";
        }

        iteration++;
    }

}

void BruteForce::showTheShortestPath() {
    for (int i = 0; i < gr->getVerticesNumber() - 2; i++) {
        std::cout << shortestPath[i] << "->";
    }
    std::cout << shortestPath[gr->getVerticesNumber() - 2];
}

