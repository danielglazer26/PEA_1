//
// Created by elmod on 18.10.2022.
//

#ifndef ALGORYTMY_BRANCHANDBOUNDTHREADS_H
#define ALGORYTMY_BRANCHANDBOUNDTHREADS_H

#include <mutex>
#include "BranchAndBound.h"

class BranchAndBoundThreads : BranchAndBound {

    const int modulo = 5;
    std::mutex queueLock;
    void solveLevel() override;

public:
    BranchAndBoundThreads() : BranchAndBound(){}
    void branchAndBoundAlgorithm() override;

    void countCostForOneNode(Node *nodeTop, int vertexTop,  int j);

    void countReduceRow(int **matrixReduced, Node *node, int i);

    void reduceRow(int **matrixReduced, Node *node) ;

    void reduceColumn(int **matrixReduced, Node *node) ;

    void countReduceColumn(int **matrixReduced, Node *node, int i) const;
};


#endif //ALGORYTMY_BRANCHANDBOUNDTHREADS_H
