
#include <iostream>
#include "../../Header/RepresentationOfGraph/Matrix.h"

//tworzenie tablicy wag
void Matrix::createTables() {

    matrixWeights = new int *[size];

    for (int i = 0; i < size; i++) {
        matrixWeights[i] = new int [size];
        for (int j = 0; j < size; j++) {
            matrixWeights[i][j] = INT32_MAX;
        }
    }
}

//tworzenie macierzy wag na podstawie listy polaczonych sasiadow
void Matrix::createMatrix(CombinedList *combinedList) {

    for (int i = 0; i < combinedList->getSize(); i++) {

        CombinedList::edge *pointer = combinedList->getList()[i];
        while (true) {
            int vE = pointer->vertex;
            int w = pointer->weight;

            matrixWeights[i][vE] = w;

            if (pointer->next != nullptr)
                pointer = pointer->next;
            else
                break;
        }
    }
}

//wyswietlanie macierz wag
void Matrix::showMatrixWages() {

    std::cout << "  ";
    for (int i = 0; i < size + 1; i++) {

        for (int j = 0; j < size; j++) {
            if (i == 0)
                std::cout << j << " ";
            else {
                if (matrixWeights[i - 1][j] != INT32_MAX)
                    std::cout << matrixWeights[i - 1][j];
                else
                    std::cout << "-";

                std::cout << " ";
            }
        }

        if (i != size)
            std::cout << std::endl << i << " ";

    }
    std::cout << std::endl;
    std::cout << std::endl;

}

//usuwanie macierzy wag
void Matrix::deleteMatrixTable() {
    for (int i = 0; i < size; i++) {
        delete[] matrixWeights[i];
    }
    delete []matrixWeights;
}

int Matrix::getSize() const {
    return size;
}

int **Matrix::getMatrixWeights() const {
    return matrixWeights;
}
