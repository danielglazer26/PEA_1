
#ifndef  ALGORYTMYDOKLADNE_MATRIX_H
#define  ALGORYTMYDOKLADNE_MATRIX_H


#include "CombinedList.h"

class Matrix {
public:
    Matrix(int s) {
        size = s;
        createTables();
    }

    ~Matrix() {
        deleteMatrixTable();
    }

    void showMatrixWages();

    void createMatrix(CombinedList *combinedList);

    int getSize() const;

    int **getMatrixWeights() const;

private:
    int size;

    int **matrixWeights;

    void createTables();

    void deleteMatrixTable();
};


#endif //ALGORYTMYDOKLADNE_MATRIX_H
