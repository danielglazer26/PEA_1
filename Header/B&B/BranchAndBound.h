
#ifndef ALGORYTMY2_BRANCHANDBOUND_H
#define ALGORYTMY2_BRANCHANDBOUND_H


#include <climits>
#include "../RepresentationOfGraph/Matrix.h"
#include "Node.h"
#include <queue>

class BranchAndBound {

public:

    BranchAndBound() {
        matrixWeights = new Matrix();
        matrix = matrixWeights->getMatrixWeights();
    }

    ~BranchAndBound() {
        matrixWeights->deleteMatrixTable(matrix);
        delete matrixWeights;
    }

    void branchAndBoundAlgorithm();

private:

    int **matrix;

    Matrix *matrixWeights;

    struct compareCost {
        bool operator()(Node *a, Node *b) { return (a->cost > b->cost); }
    };

    std::priority_queue<Node *, std::vector<Node *>, compareCost> priorityQueue;

    void calculateCost(int **matrixReduced, Node *node);

    void reduceRow(int **matrixReduced, Node *node);

    void reduceColumn(int **matrixReduced, Node *node);

    void makeInfinity(Node *parent, Node *child);

    static void showPath(const std::vector<int> &path);

    void solveLevel();
};


#endif //ALGORYTMY2_BRANCHANDBOUND_H
