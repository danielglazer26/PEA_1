#include "../Header/BruteForce.h"
#include "../Header/DynamicProgramming.h"
#include "../Header/B&B/BranchAndBound.h"
#include <queue>
int main() {

    auto * bAndB = new BranchAndBound();
    bAndB->branchAndBoundAlgorithm();
    auto * bruteForce = new BruteForce();
    bruteForce->bruteForceAlgorithm(0);
    bruteForce->showTheShortestPath();
    delete bruteForce;
    /*DynamicProgramming *dynamicProgramming = new DynamicProgramming(true);
    dynamicProgramming->test2();
    delete dynamicProgramming;*/

    return 0;
}