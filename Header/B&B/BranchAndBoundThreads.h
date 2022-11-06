#ifndef ALGORYTMY_BRANCHANDBOUNDTHREADS_H
#define ALGORYTMY_BRANCHANDBOUNDTHREADS_H

#include <mutex>
#include "BranchAndBound.h"

class BranchAndBoundThreads : BranchAndBound {

    int numberOfThreads;
    std::mutex queueLock;

    void solveLevel() override;

public:
    explicit BranchAndBoundThreads(int numberOfThreads) {
        this->numberOfThreads = numberOfThreads;
    }

    void branchAndBoundAlgorithm() override;

    void countCostForOneNode(Node *nodeTop, int j);

    void makeInfinity(Node *parent, Node *child) override;

    int ** getMatrix() override;
};


#endif //ALGORYTMY_BRANCHANDBOUNDTHREADS_H
