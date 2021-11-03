#include <iostream>
#include <random>

#include "../../Header/RepresentationOfGraph/GraphRepresentation.h"

//wczytywanie danych inicjalizujacych graf
void GraphRepresentation::graphInitialization(bool directed) {

    LoadFromFile *loadFromFile = new LoadFromFile();

    //wczytujemy podstawowe dane z pliku
    if (loadFromFile->openFile()) {
        verticesNumber = loadFromFile->getDataFromFile();
        createList(loadFromFile, directed);
        createMatrix();
        std::cout << "Wczytano dane\n";

    } else {
        std::cout << "Brak pliku\n";
    }
}

//wczytywanie krawedzi z pliku w celu utworzenia listy
void GraphRepresentation::createList(LoadFromFile *loadFromFile, bool directed) {

    combinedList = new CombinedList(verticesNumber);
    for (int i = 0; i < verticesNumber; i++) {
        for (int j = 0; j < verticesNumber; j++) {
            createListForNewGraph(directed, i, j, loadFromFile->getDataFromFile());
        }
    }
    optimum = loadFromFile->getDataFromFile();
    delete loadFromFile;
}

//tworzenie macierzy sąsiedztwa na podstawie listy
void GraphRepresentation::createMatrix() {
    matrix = new Matrix(verticesNumber);
    matrix->createMatrix(combinedList);
}

/*
//tworzenie nowego grafu na podstawie gestoscie i lcizby wierzcholkow
void GraphRepresentation::createNewGraph(bool directed, float graphDensity, int vNumber) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, vNumber - 1);
    std::uniform_int_distribution<> dist2(0, 100000);

    verticesNumber = vNumber;
    optimum = 0;
    endingVertex = vNumber - 1;

    combinedList = new CombinedList(verticesNumber);

    //obliczamy ilosc krawedzi dla grafu
    if (!directed)
        edgesNumber = 0.5 * vNumber * (vNumber - 1) * graphDensity;
    else
        edgesNumber = vNumber * (vNumber - 1) * graphDensity;

    //tworzymy polaczenie pierwszego wierzcholka z pozostalymi,
    //by uniknac wierzcholka o zerowym stopniu
    for (int i = 1; i < vNumber; i++) {
        createListForNewGraph(directed, 0, i, dist2(gen));
    }

    //tworzymy polaczenie pomiedzy wygenerowanymi wierzcholkami
    for (int i = edgesNumber - verticesNumber - 1; i > 0; i--) {

        int x = dist(gen);
        int y = dist(gen);
        if (x != y) {
            if (isNotConnection(x, y))
                createListForNewGraph(directed, x, y, dist2(gen));
            else
                i++;
        }
    }
    createMatrix();

}

//sprawdzamy czy w liscie wystepuje juz taka krawedz
bool GraphRepresentation::isNotConnection(int x, int y) {

    CombinedList::EdgeList *pointer = combinedList->getList()[x];
    while (true) {

        if (pointer->vertex == y)
            return false;

        if (pointer->next != nullptr)
            pointer = pointer->next;
        else
            return true;
    }
}
*/

//tworzymy liste w zaleznosci od rodzaju grafu (skierowany / nieskierowany)
void GraphRepresentation::createListForNewGraph(bool directed, int vS, int vE, int w) {

    if (directed)
        combinedList->createDirectedList(vS, vE, w);
    else
        combinedList->createUndirectedList(vS, vE, w);

}

CombinedList *GraphRepresentation::getCombinedList() {
    return combinedList;
}

Matrix *GraphRepresentation::getMatrix() {
    return matrix;
}

int GraphRepresentation::getEdgesNumber() const {
    return edgesNumber;
}

int GraphRepresentation::getVerticesNumber() const {
    return verticesNumber;
}

int GraphRepresentation::getOptimum() const {
    return optimum;
}

