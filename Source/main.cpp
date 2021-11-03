#include "../Header/BruteForce.h"
#include "../Header/DynamicProgramming.h"
int main() {
    /*auto * bruteForce = new BruteForce(true);
    bruteForce->bruteForceAlgorithm(0);
    bruteForce->showTheShortestPath();
    delete bruteForce;*/
    DynamicProgramming *dynamicProgramming = new DynamicProgramming(true);
    dynamicProgramming->test2();
    delete dynamicProgramming;
    return 0;
}