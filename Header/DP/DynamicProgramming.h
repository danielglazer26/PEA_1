#ifndef ALGORYTMY2_DYNAMICPROGRAMMING_H
#define ALGORYTMY2_DYNAMICPROGRAMMING_H


#include <map>
#include "../RepresentationOfGraph/Matrix.h"
#include "NodeDP.h"
class DynamicProgramming {

private:

    int ** matrix;
    Matrix *matrixWeights;

    static void showAnswer(NodeDP *node);

    void findingMinimum(NodeDP *n);

public:

    DynamicProgramming() {
        matrixWeights = new Matrix();
        matrix = matrixWeights->getMatrixWeights();
    }

    ~DynamicProgramming(){
        matrixWeights->deleteMatrixTable(matrix);
        delete matrixWeights;
    }

    void dynamicProgrammingAlgorithm();

};


#endif //ALGORYTMY2_DYNAMICPROGRAMMING_H
