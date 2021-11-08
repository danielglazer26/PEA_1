
#include "../Header/B&B/BranchAndBound.h"
#include "../Header/DP/DynamicProgramming.h"
#include "../Header/BF/BruteForce.h"
#include <queue>
int main() {

   /* auto * bAndB = new BranchAndBound();
    bAndB->branchAndBoundAlgorithm();*/
    auto * bruteForce = new BruteForce();
    bruteForce->bruteForceAlgorithm(0);
    bruteForce->showTheShortestPath();
    delete bruteForce;
   /* DynamicProgramming *dynamicProgramming = new DynamicProgramming();
    dynamicProgramming->dynamicProgrammingAlgorithm();
    delete dynamicProgramming;*/

    return 0;
}