#include <climits>
#include <vector>
#include <ntdef.h>
#include <iostream>
#include <valarray>
#include <map>
#include "../Header/DynamicProgramming.h"

// initialize the DP table
// best[visited][last] = the cheapest way to reach the state where:
// - "visited" encodes the set of visited vertices other than N-1
// - "last" is the number of the vertex visited last

void DynamicProgramming::test() {

    std::vector<std::vector<int> > best(1 << (matrixWeights->getSize() - 1),
                                        std::vector<int>(matrixWeights->getSize(), INT_MAX));

// use DP to solve all states
// note that whenever we solve a particular state,
// the smaller states we need have already been solved

    for (int visited = 0; visited < (1 << (matrixWeights->getSize() - 1)); ++visited) {
        for (int last = 0; last < (matrixWeights->getSize() - 1); ++last) {

// last visited vertex must be one of the visited vertices
            if (!(visited & 1 << last)) continue;

// try all possibilities for the previous vertex,
// pick the best among them
            if (visited == 1 << last) {
// previous vertex must have been N-1
                best[visited][last] = matrix[last][matrixWeights->getSize() - 1];
            } else {
// previous vertex was one of the other ones in "visited"
                int prev_visited = visited ^ 1 << last;
                for (int prev = 0; prev < matrixWeights->getSize() - 1; ++prev) {
                    if (!(prev_visited & 1 << prev)) continue;
                    best[visited][last] = std::min(
                            best[visited][last],
                            matrix[last][prev] + best[prev_visited][prev]
                    );
                }
            }
        }
    }

// use the precomputed path lengths to choose the cheapest cycle
    int answer = INT_MAX;
    for (int last = 0; last < matrixWeights->getSize() - 1; ++last) {
        answer = std::min(
                answer,
                matrix[matrixWeights->getSize() - 1][last] + best[(1 << (matrixWeights->getSize() - 1)) - 1][last]
        );
    }
    std::cout << answer;
}

void DynamicProgramming::test2() {


    std::vector<int> initialization;
    for (int i = 1; i < matrixWeights->getSize(); i++) {
        initialization.push_back(i);

    }
    showAnswer(&initialization, 0);


}

void DynamicProgramming::showAnswer(std::vector<int> *S, int p) {

    std::cout << findingMinimum(S, p) << "\n";

}


int DynamicProgramming::findingMinimum(std::vector<int> *S, int p) {
    int answer = INT_MAX;
    int answer2 = INT_MAX;

    for (int i = 0; i < S->size(); i++) {
        std::vector<int> smaller = *S;
        int a = (*S)[i];
        auto j = smaller.begin();
        std::advance(j, i);
        smaller.erase(j);

        if (S->size() != 1)
            answer = std::min(matrix[p][a] + findingMinimum(&smaller, a), answer);
         else
            answer = (matrix[p][a] + matrix[a][0]);

    }
    return answer;
}

/*void DynamicProgramming::test3() {

    std::vector<int> a;
    generate_subsets(a, matrixWeights->getSize() - 1, 1);
    print_map(map);
    *//*compareSize comparer;
    std::sort(best.begin(), best.end(), comparer);
    best.erase(best.begin());
    auto it = best.begin();

    while (it != best.end()) {
        it->push_back(D2(&it.operator*(), 0));
        it++;
    }
    showVector();*//*
    auto it = map.begin();

    while (it != best.end()) {
        it->push_back(D2(&it.operator*(), 0));
        it++;
    }
}

int DynamicProgramming::D2(std::vector<int> *S, int p) {
    *//*  int answer = INT_MAX;

      if (S->size() == 1)
          return matrix[0][S->begin().operator*()];
      else{
          auto it = S->begin();
          for (int i = 0; i < S->size(); i++) {
              answer
          }
      }*//*

    return 0;
}

void DynamicProgramming::generate_subsets(std::vector<int> vector, int n, int k) {

    if (k > n) {
        map.insert(std::pair<std::vector<int>, int>(vector, -1));
    } else {
        vector.push_back(k);
        generate_subsets(vector, n, k + 1);
        vector.pop_back();
        generate_subsets(vector, n, k + 1);
    }
}

void DynamicProgramming::showVector() {
    for (std::vector<int> v: best) {
        for (int b: v) {
            std::cout << b << " ";
        }
        std::cout << "\n";
    }
}

void DynamicProgramming::print_map(const std::map<std::vector<int>, int> &m) {
    for (const auto&[key, value]: m) {
        for (int b: key) {
            std::cout << b << " ";
        }
        std::cout << value << ";\n ";
    }
    std::cout << "\n";
}*/

