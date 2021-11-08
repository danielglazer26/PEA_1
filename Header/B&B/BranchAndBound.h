
#ifndef ALGORYTMY2_BRANCHANDBOUND_H
#define ALGORYTMY2_BRANCHANDBOUND_H


#include <climits>
#include "../RepresentationOfGraph/Matrix.h"
#include "Node.h"
#include <queue>

class BranchAndBound {
private:

    struct compareCost{
        bool operator()(Node* a, Node *b) {
            return (a->cost > b->cost);
        }
    };

    Matrix * matrixWeights;
    int ** matrix;
    std::priority_queue <Node* ,std::vector<Node*>, compareCost> priorityQueue;

public:

    BranchAndBound() {
        matrixWeights = new Matrix();
        matrix = matrixWeights->getMatrixWeights();
    }

    ~BranchAndBound(){
        matrixWeights->deleteMatrixTable(matrix);
        delete matrixWeights;
    }

    void reduceRow(int **matrixReduced, Node *node);

    void branchAndBoundAlgorithm();

    void reduceColumn(int **matrixReduced, Node *node);

    void makeInfinity(Node *parent, Node *child);

    void solveLevel();

    static void showPath(const std::vector<int>& path);

    void calculateCost(int **matrixReduced, Node *node);
};


#endif //ALGORYTMY2_BRANCHANDBOUND_H
