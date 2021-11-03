#include <vector>
#include "RepresentationOfGraph/GraphRepresentation.h"

#ifndef ALGORYTMYDOKLADNE_BRUTEFORCE_H
#define ALGORYTMYDOKLADNE_BRUTEFORCE_H


class BruteForce {

private:
    GraphRepresentation *gr;
    int shortest = INT_MAX;
    int * currentPath;
    int * shortestPath;
    std::vector <int> nodes;
    int ** matrix;
    int iteration = 0;
public:

    BruteForce(bool directed) {
        gr = new GraphRepresentation(directed);
        matrix = gr->getMatrix()->getMatrixWeights();
        currentPath = new int [gr->getVerticesNumber()];
        shortestPath = new int [gr->getVerticesNumber()];
    }

    void bruteForceAlgorithm(int sourceVertex);

    void showTheShortestPath();

    ~BruteForce() {
        delete gr;
        delete currentPath;
        delete shortestPath;
    }
};


#endif //ALGORYTMYDOKLADNE_BRUTEFORCE_H
