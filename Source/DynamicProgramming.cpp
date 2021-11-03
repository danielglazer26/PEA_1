#include <climits>
#include <vector>
#include <ntdef.h>
#include <iostream>
#include <valarray>
#include "../Header/DynamicProgramming.h"

// initialize the DP table
// best[visited][last] = the cheapest way to reach the state where:
// - "visited" encodes the set of visited vertices other than N-1
// - "last" is the number of the vertex visited last

void DynamicProgramming::test() {

    std::vector<std::vector<int> > best(1 << (gr->getVerticesNumber() - 1),
                                        std::vector<int>(gr->getVerticesNumber(), INT_MAX));

// use DP to solve all states
// note that whenever we solve a particular state,
// the smaller states we need have already been solved

    for (int visited = 0; visited < (1 << (gr->getVerticesNumber() - 1)); ++visited) {
        for (int last = 0; last < (gr->getVerticesNumber() - 1); ++last) {

// last visited vertex must be one of the visited vertices
            if (!(visited & 1 << last)) continue;

// try all possibilities for the previous vertex,
// pick the best among them
            if (visited == 1 << last) {
// previous vertex must have been N-1
                best[visited][last] = matrix[last][gr->getVerticesNumber() - 1];
            } else {
// previous vertex was one of the other ones in "visited"
                int prev_visited = visited ^ 1 << last;
                for (int prev = 0; prev < gr->getVerticesNumber() - 1; ++prev) {
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
    for (int last = 0; last < gr->getVerticesNumber() - 1; ++last) {
        answer = std::min(
                answer,
                matrix[gr->getVerticesNumber() - 1][last] + best[(1 << (gr->getVerticesNumber() - 1)) - 1][last]
        );
    }
    std::cout << answer;
}

void DynamicProgramming::test2() {

    std::vector<int> initialization;
    for (int i = 1; i < gr->getVerticesNumber(); i++) {
        initialization.push_back(i);
    }
    showAnswer(&initialization, 0);


}

void DynamicProgramming::showAnswer(std::vector<int> *S, int p) {
    int answer = INT_MAX;

    answer = findingMinimum(S, p);

    std::cout << answer;
}

int DynamicProgramming::D(std::vector<int> *S, int p) {
    int answer = INT_MAX;

    if(!S->empty())
        answer = findingMinimum(S, p);
    else
        answer = matrix[p][0];

    return answer;
}
int  DynamicProgramming::findingMinimum(std::vector<int> *S, int p){
    int answer = INT_MAX;

    for (int i = 0; i < S->size(); i++) {
        std::vector<int> smaller = *S;
        int a  = (*S)[i];
        auto j = smaller.begin();
        std::advance(j, i);
        smaller.erase(j);

        answer = std::min(matrix[p][a] + D(&smaller, a), answer);
    }
    return  answer;
}

