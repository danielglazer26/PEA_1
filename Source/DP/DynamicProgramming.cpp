#include <climits>
#include <vector>
#include <iostream>
#include <valarray>
#include "../../Header/DP/DynamicProgramming.h"


void DynamicProgramming::dynamicProgrammingAlgorithm() {


    std::vector<int> initialization;
    for (int i = 1; i < matrixWeights->getSize(); i++) {
        initialization.push_back(i);

    }
    NodeDP *node = new NodeDP(initialization, 0);
    findingMinimum(node);
    showAnswer(node);

}

void DynamicProgramming::showAnswer(NodeDP *node) {

    std::cout << node->value << "\n";
    auto n_i = node;
    while (n_i->minNode != nullptr) {
        std::cout << n_i->vertex << "->";
        n_i = n_i->minNode;
    }
    std::cout << n_i->vertex;
}


void DynamicProgramming::findingMinimum(NodeDP *n) {


    for (int i = 0; i < n->S.size(); i++) {
        std::vector<int> smaller = n->S;
        int a = n->S[i];
        auto j = smaller.begin();
        std::advance(j, i);
        smaller.erase(j);
        auto *child = new NodeDP(smaller, a);

        if (!n->S.empty()) {

            findingMinimum(child);

            int value = matrix[n->vertex][a] + child->value;
            if (n->value > value) {
                n->value = value;
                delete n->minNode;
                n->minNode = child;
            }
        }

    }
    if (n->S.empty())
        n->value = matrix[n->vertex][0];

}


