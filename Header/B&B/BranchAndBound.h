
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
        if (matrixWeights->getMatrixWeights() != nullptr)
            matrix = matrixWeights->getMatrixWeights();
    }

    ~BranchAndBound() {
        if (matrixWeights->getMatrixWeights() != nullptr)
            matrixWeights->deleteMatrixTable(matrix);
        delete matrixWeights;
    }

    int **getMatrix() const;

    virtual void branchAndBoundAlgorithm();

protected:

    int **matrix = nullptr;

    Matrix *matrixWeights;

    struct compareCost {
        bool operator()(Node *a, Node *b) { return (a->cost > b->cost); }
    };

    std::priority_queue<Node *, std::vector<Node *>, compareCost> priorityQueue;

    void calculateCost(int **matrixReduced, Node *node);

     void reduceRow(int **matrixReduced, Node *node);

     void reduceColumn(int **matrixReduced, Node *node);

    virtual void makeInfinity(Node *parent, Node *child);

    static void showPath(const std::vector<int> &path);

    virtual void solveLevel();
};


#endif //ALGORYTMY2_BRANCHANDBOUND_H
