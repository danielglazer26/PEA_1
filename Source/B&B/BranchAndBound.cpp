#include <vector>
#include <iostream>
#include "../../Header/B&B/BranchAndBound.h"

void BranchAndBound::reduceRow(int **matrixReduced, Node *node) {

    for (int i = 0; i < matrixWeights->getSize(); i++) {

        int min = INT_MAX;
        for (int j = 0; j < matrixWeights->getSize(); j++)
            min = std::min(matrixReduced[i][j], min);

        if (min != INT_MAX && min != 0) {
            node->cost += min;
            for (int j = 0; j < matrixWeights->getSize(); j++) {
                if (matrixReduced[i][j] != INT_MAX)
                    matrixReduced[i][j] -= min;
            }
        }
    }
    reduceColumn(matrixReduced, node);
}

void BranchAndBound::reduceColumn(int **matrixReduced, Node *node) {

    for (int i = 0; i < matrixWeights->getSize(); i++) {

        int min = INT_MAX;
        for (int j = 0; j < matrixWeights->getSize(); j++)
            min = std::min(matrixReduced[j][i], min);

        if (min != INT_MAX && min != 0) {
            node->cost += min;
            for (int j = 0; j < matrixWeights->getSize(); j++) {
                if (matrixReduced[j][i] != INT_MAX)
                    matrixReduced[j][i] -= min;
            }
        }
    }

}

void BranchAndBound::calculateCost(int **matrixReduced, Node *node) {
    reduceRow(matrixReduced, node);
}

void BranchAndBound::makeInfinity(Node *parent, Node *child) {
    child->copyMatrix(parent->matrix_reduced);

    child->cost += child->matrix_reduced[parent->vertex][child->vertex];
    child->matrix_reduced[child->vertex][parent->vertex] = INT_MAX;

    std::fill_n(child->matrix_reduced[parent->vertex], matrixWeights->getSize(), INT_MAX);
    for (int i = 0; i < matrixWeights->getSize(); i++) {
        child->matrix_reduced[i][child->vertex] = INT_MAX;
    }

}

void BranchAndBound::branchAndBoundAlgorithm() {

    Node *node0 = new Node(0, matrixWeights->getSize());
    node0->copyMatrix(matrix);
    calculateCost(node0->matrix_reduced, node0);
    node0->path.push_back(0);
    node0->level = 0;
    priorityQueue.push(node0);

    solveLevel();

}

void BranchAndBound::solveLevel() {

    while (!priorityQueue.empty()) {
        Node *minimumNode = priorityQueue.top();
        std::cout << minimumNode->cost
                  << "   "
                  << 100 * (minimumNode->cost - matrixWeights->getOptimum()) /
                     matrixWeights->getOptimum()
                  << "% \n";
        priorityQueue.pop();

        if (minimumNode->level == matrixWeights->getSize() - 1) {
            showPath(minimumNode->path);
            break;
        }
        int minimumVertex = minimumNode->vertex;
        for (int j = 0; j < matrixWeights->getSize(); j++) {
            if (minimumNode->matrix_reduced[minimumVertex][j] != INT_MAX) {

                Node *child = new Node(j, matrixWeights->getSize());
                child->copyPath(minimumNode->path);
                child->copyMatrix(minimumNode->matrix_reduced);
                makeInfinity(minimumNode, child);
                child->level = minimumNode->level + 1;

                child->cost += minimumNode->cost;
                calculateCost(child->matrix_reduced, child);

                priorityQueue.push(child);
            }
        }

        delete minimumNode;
    }


}


void BranchAndBound::showPath(const std::vector<int>& p) {

    for (int v: p) {
        std::cout << v << "->";
    }
    std::cout << 0;
}

