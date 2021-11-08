#ifndef ALGORYTMY2_DYNAMICPROGRAMMING_H
#define ALGORYTMY2_DYNAMICPROGRAMMING_H


#include <map>
#include "RepresentationOfGraph/Matrix.h"

class DynamicProgramming {

private:
    struct compareSize{
        bool operator()(std::vector<int> a, std::vector<int> b) {
            return (a.size() < b.size());
        }
    };
    struct compareSizeMap{
        bool operator()(std::pair<std::vector<int>, int> a, std::pair<std::vector<int>, int> b) {
            return (a.first.size() < b.first.size());
        }
    };

    Matrix *matrixWeights;
    int ** matrix;

public:

    DynamicProgramming(bool directed) {
        matrixWeights = new Matrix();
        matrix = matrixWeights->getMatrixWeights();
    }

    void test();

    ~DynamicProgramming(){
        matrixWeights->deleteMatrixTable(matrix);
        delete matrixWeights;
    }

    void test2();

    int D(std::vector<int> *S, int p);

    void showAnswer(std::vector<int> *S, int p);

    int findingMinimum(std::vector<int> *S, int p);

    void algorithmHeldKarp();

    void generate_subsets(std::vector<int> vector, int n, int k);

    void test3();

    void showVector();

    int D2(std::vector<int> *S, int p);

    void print_map(const std::map<std::vector<int>, int> &m);
};


#endif //ALGORYTMY2_DYNAMICPROGRAMMING_H
