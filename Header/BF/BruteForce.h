#include <vector>
#include "../RepresentationOfGraph/Matrix.h"

#ifndef ALGORYTMYDOKLADNE_BRUTEFORCE_H
#define ALGORYTMYDOKLADNE_BRUTEFORCE_H


class BruteForce {

private:
    Matrix *matrixWeights;
    int shortest = INT_MAX;
    int *currentPath;
    int *shortestPath;
    std::vector<int> nodes;
    int **matrix;
public:

    BruteForce() {
        matrixWeights = new Matrix();
        matrix = matrixWeights->getMatrixWeights();
        currentPath = new int[matrixWeights->getSize() + 1];
        shortestPath = new int[matrixWeights->getSize() + 1];
    }

    void bruteForceAlgorithm(int sourceVertex);

    void showTheShortestPath();

    ~BruteForce() {
        matrixWeights->deleteMatrixTable(matrix);
        delete matrixWeights;
        delete currentPath;
        delete shortestPath;
    }
};


#endif //ALGORYTMYDOKLADNE_BRUTEFORCE_H
