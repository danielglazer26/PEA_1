
#ifndef  ALGORYTMYDOKLADNE_GRAPHREPRESENTATION_H
#define  ALGORYTMYDOKLADNE_GRAPHREPRESENTATION_H

#include "CombinedList.h"
#include "Matrix.h"
#include "../LoadFromFile.h"

class GraphRepresentation {
public:

    GraphRepresentation(bool directed) { graphInitialization(directed); }

    GraphRepresentation(bool directed, float graphDensity, int vNumber) {
        createNewGraph(directed, graphDensity, vNumber);
    }

    ~GraphRepresentation() {
        if (combinedList != nullptr) {
            delete matrix;
            delete combinedList;
        }
    }


    CombinedList *getCombinedList();

    Matrix *getMatrix();

    int getEdgesNumber() const;

    int getVerticesNumber() const;

    int getOptimum() const;

private:
    CombinedList *combinedList = nullptr;
    Matrix *matrix;

    int edgesNumber;
    int verticesNumber;
    int optimum;

    void graphInitialization(bool directed);

    void createList(LoadFromFile *loadFromFile, bool directed);

    void createMatrix();

    void createNewGraph(bool directed, float graphDensity, int vNumber);

    void createListForNewGraph(bool directed, int vS, int vE, int w);

    bool isNotConnection(int x, int y);

};


#endif // ALGORYTMYDOKLADNE_GRAPHREPRESENTATION_H
