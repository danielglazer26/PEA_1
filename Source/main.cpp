#include <iostream>
#include <chrono>
#include "../Header/B&B/BranchAndBound.h"
#include "../Header/B&B/BranchAndBoundThreads.h"


///główne menu
void menu() {
    int a;
    do {
        BranchAndBound *branchAndBound;
        std::cout << "\n1. Algorytm podziału i ograniczeń \n"
                  << "2.   Algorytm podziału i ograniczeń na wątkach\n"
                  << "3. Wyjście \n"
                  << "Opcja:";
        std::cin >> a;
        switch (a - 1) {
            case 0:
                branchAndBound = new BranchAndBound();
                if (branchAndBound->getMatrix() != nullptr)
                    branchAndBound->branchAndBoundAlgorithm();
                delete branchAndBound;
                break;
            case 1:
                break;
        }

    } while (a != 3);

}

int main() {
    //menu();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
   auto *branchAndBound = new BranchAndBound();
    branchAndBound->branchAndBoundAlgorithm();
    delete branchAndBound;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "[s]" << std::endl;

    begin = std::chrono::steady_clock::now();
    auto * branchAndBoundThreads = new BranchAndBoundThreads();
    branchAndBoundThreads->branchAndBoundAlgorithm();
    delete branchAndBoundThreads;

    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "[s]" << std::endl;
    return 0;
}
