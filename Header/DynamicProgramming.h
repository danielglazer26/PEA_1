#ifndef ALGORYTMY2_DYNAMICPROGRAMMING_H
#define ALGORYTMY2_DYNAMICPROGRAMMING_H


#include "RepresentationOfGraph/GraphRepresentation.h"

class DynamicProgramming {

private:
    GraphRepresentation *gr;

    int ** matrix;

public:

    DynamicProgramming(bool directed) {
        gr = new GraphRepresentation(directed);
        matrix = gr->getMatrix()->getMatrixWeights();
    }

    void test();

    ~DynamicProgramming(){
        delete gr;
    }

    void test2();

    int D(std::vector<int> *S, int p);

    void showAnswer(std::vector<int> *S, int p);

    int findingMinimum(std::vector<int> *S, int p);
};


#endif //ALGORYTMY2_DYNAMICPROGRAMMING_H
