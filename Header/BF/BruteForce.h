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
    int **matrix = nullptr;
public:

    BruteForce() {
        matrixWeights = new Matrix();
        if (matrixWeights->getMatrixWeights() != nullptr) {
            matrix = matrixWeights->getMatrixWeights();
            currentPath = new int[matrixWeights->getSize() + 1];
            shortestPath = new int[matrixWeights->getSize() + 1];
        }
    }

    ~BruteForce() {
        if (matrixWeights->getMatrixWeights() != nullptr) {
            matrixWeights->deleteMatrixTable(matrix);
            delete currentPath;
            delete shortestPath;
        }
        delete matrixWeights;
    }

    void bruteForceAlgorithm(int sourceVertex);

    void showTheShortestPath();

    int **getMatrix() const;
};


#endif //ALGORYTMYDOKLADNE_BRUTEFORCE_H
