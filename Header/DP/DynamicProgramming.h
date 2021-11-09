#ifndef ALGORYTMY2_DYNAMICPROGRAMMING_H
#define ALGORYTMY2_DYNAMICPROGRAMMING_H


#include <map>
#include "../RepresentationOfGraph/Matrix.h"
#include "NodeDP.h"

class DynamicProgramming {

private:

    int **matrix = nullptr;
    Matrix *matrixWeights;

    void showAnswer(NodeDP *node);

    void findingMinimum(NodeDP *n);

public:

    DynamicProgramming() {
        matrixWeights = new Matrix();
        if (matrixWeights->getMatrixWeights() != nullptr)
            matrix = matrixWeights->getMatrixWeights();
    }

    ~DynamicProgramming() {
        if (matrixWeights->getMatrixWeights() != nullptr)
            matrixWeights->deleteMatrixTable(matrix);
        delete matrixWeights;

    }

    int **getMatrix() const;

    void dynamicProgrammingAlgorithm();

};


#endif //ALGORYTMY2_DYNAMICPROGRAMMING_H
