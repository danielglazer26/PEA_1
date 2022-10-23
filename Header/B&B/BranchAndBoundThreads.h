//
// Created by elmod on 18.10.2022.
//

#ifndef ALGORYTMY_BRANCHANDBOUNDTHREADS_H
#define ALGORYTMY_BRANCHANDBOUNDTHREADS_H

#include <mutex>
#include "BranchAndBound.h"

class BranchAndBoundThreads : BranchAndBound {

    const int modulo = 10;
    std::mutex queueLock;
    void solveLevel() override;

public:
    BranchAndBoundThreads() : BranchAndBound(){}
    void branchAndBoundAlgorithm() override;

    void countCostForOneNode(Node *nodeTop, int j);

    //void countReduceRow(int **matrixReduced, Node *node, int j);

    //void reduceRow(int **matrixReduced, Node *node) override;

    /*void reduceColumn(int **matrixReduced, Node *node) override;*/

    //void countReduceColumn(int **matrixReduced, Node *node, int j);

    void makeInfinity(Node *parent, Node *child) override;
};


#endif //ALGORYTMY_BRANCHANDBOUNDTHREADS_H
