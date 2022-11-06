
#ifndef  ALGORYTMYDOKLADNE_MATRIX_H
#define  ALGORYTMYDOKLADNE_MATRIX_H


#include "LoadFromFile.h"

class Matrix {
public:
    Matrix() {
        loadData();
    }

    void showMatrixWages();

    int getSize() const;

    int getOptimum() const;

    int **getMatrixWeights() const;

    void deleteMatrixTable(int **matrixW) const;

private:
    int size;

    int optimum;

    int **matrixWeights = nullptr;

    void createTables();

    void createMatrix(LoadFromFile *loadFromFile);

    void loadData();
};


#endif //ALGORYTMYDOKLADNE_MATRIX_H
