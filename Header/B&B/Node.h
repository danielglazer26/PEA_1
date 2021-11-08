#ifndef ALGORYTMY2_NODE_H
#define ALGORYTMY2_NODE_H


#include <utility>
#include <vector>

class Node {
private:
    int numberOfVertexes;
public:
    std::vector<int> path;
    int level;
    int **matrix_reduced;
    int cost = 0;
    int vertex;

    Node(int vertex, int numberOfVertexes) {
        this->vertex = vertex;
        this->numberOfVertexes = numberOfVertexes;
        matrix_reduced = new int *[numberOfVertexes];
        for (int i = 0; i < numberOfVertexes; i++) {
            matrix_reduced[i] = new int[numberOfVertexes];
        }
    }

    void copyMatrix(int **m) const {
        for (int i = 0; i < numberOfVertexes; i++) {
            for (int j = 0; j < numberOfVertexes; ++j) {
                this->matrix_reduced[i][j] = m[i][j];
            }
        }
    }

    void copyPath(std::vector<int> p) {
        this->path = std::move(p);
        this->path.push_back(vertex);
    }

    ~Node() {
        for (int i = 0; i < numberOfVertexes; i++) {
            delete[] matrix_reduced[i];
        }
        delete[]matrix_reduced;
    }
};


#endif //ALGORYTMY2_NODEDP_H
