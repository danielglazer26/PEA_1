#include <iostream>
#include "../Header/B&B/BranchAndBound.h"
#include "../Header/DP/DynamicProgramming.h"
#include "../Header/BF/BruteForce.h"


///główne menu
void menu() {
    int a;
    do {
        DynamicProgramming *dynamicProgramming;
        BruteForce *bruteForce;
        BranchAndBound *branchAndBound;
        std::cout << "\n1. Przegląd zupełny \n"
                  << "2. Algorytm podziału i ograniczeń  \n"
                  << "3. Dynamiczne programowanie\n"
                  << "4. Wyjście \n"
                  << "Opcja:";
        std::cin >> a;
        switch (a - 1) {
            case 0:
                bruteForce = new BruteForce();
                if (bruteForce->getMatrix() != nullptr) {
                    bruteForce->bruteForceAlgorithm(0);
                    bruteForce->showTheShortestPath();
                }
                delete bruteForce;
                break;
            case 1:
                branchAndBound = new BranchAndBound();
                if (branchAndBound->getMatrix() != nullptr)
                    branchAndBound->branchAndBoundAlgorithm();
                delete branchAndBound;
                break;
            case 2:
                dynamicProgramming = new DynamicProgramming();
                if (dynamicProgramming->getMatrix() != nullptr)
                    dynamicProgramming->dynamicProgrammingAlgorithm();
                delete dynamicProgramming;
                break;
        }

    } while (a != 4);

}

int main() {
    menu();

    return 0;
}
