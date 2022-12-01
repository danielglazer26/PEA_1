#include <iostream>
#include <chrono>
#include "../Header/B&B/BranchAndBound.h"
#include "../Header/B&B/BranchAndBoundThreads.h"


///główne menu
void menu() {
    int a;
    do {
        BranchAndBound *branchAndBound;
        BranchAndBoundThreads *branchAndBoundThreads;
        int numberOfThreads;
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;
        std::cout << "\n1. Algorytm podziału i ograniczeń \n"
                  << "2. Algorytm podziału i ograniczeń na wątkach\n"
                  << "3. Porównanie czasowe\n"
                  << "4. Wyjście \n"
                  << "Opcja:";
        std::cin >> a;
        switch (a - 1) {
            case 0:
                branchAndBound = new BranchAndBound();
                if (branchAndBound->getMatrix() != nullptr) {
                    begin = std::chrono::steady_clock::now();
                    branchAndBound->branchAndBoundAlgorithm();
                    end = std::chrono::steady_clock::now();
                    std::cout << "Time difference = "
                              << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]"
                              << std::endl;
                    std::cout << "Time difference = "
                              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[qs]"
                              << std::endl;
                }
                delete branchAndBound;
                break;
            case 1:
                std::cout << "Podaj liczbę wątków : ";
                std::cin >> numberOfThreads;
                branchAndBoundThreads = new BranchAndBoundThreads(numberOfThreads);
                if (branchAndBoundThreads->getMatrix() != nullptr) {
                    begin = std::chrono::steady_clock::now();
                    branchAndBoundThreads->branchAndBoundAlgorithm();
                    end = std::chrono::steady_clock::now();
                    std::cout << "Time difference = "
                              << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]"
                              << std::endl;
                    std::cout << "Time difference = "
                              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[qs]"
                              << std::endl;
                }
                delete branchAndBoundThreads;
                break;
            case 2:
                std::cout << "Podaj liczbę wątków : ";
                std::cin >> numberOfThreads;
                branchAndBound = new BranchAndBound();

                begin = std::chrono::steady_clock::now();
                if (branchAndBound->getMatrix() != nullptr)
                    branchAndBound->branchAndBoundAlgorithm();
                end = std::chrono::steady_clock::now();

                std::cout << "Time difference = "
                          << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]"
                          << std::endl;
                std::cout << "Time difference = "
                          << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[qs]"
                          << std::endl;
                delete branchAndBound;

                branchAndBoundThreads = new BranchAndBoundThreads(numberOfThreads);

                std::cout<< "Wielowątkowo" <<std::endl;
                begin = std::chrono::steady_clock::now();
                if (branchAndBoundThreads->getMatrix() != nullptr)
                    branchAndBoundThreads->branchAndBoundAlgorithm();
                end = std::chrono::steady_clock::now();

                std::cout << "Time difference = "
                          << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]"
                          << std::endl;
                std::cout << "Time difference = "
                          << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[qs]"
                          << std::endl;

                delete branchAndBoundThreads;
                break;
        }

    } while (a != 4);

}

int main() {
    std::string zmienna;

    std::cin >> zmienna;
    menu();
    return 0;
}
