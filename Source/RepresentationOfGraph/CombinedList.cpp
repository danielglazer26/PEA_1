#include <iostream>
#include "../../Header/RepresentationOfGraph/CombinedList.h"

//tworzenie nieskierowanej listy
void CombinedList::createUndirectedList(int vS, int vE, int w) {

    //tworzenie listy nieskierowanej to tak naprawde stworzenie listy skierowanej
    //z wierzcholkami o zamienionej kolejnosci
    createDirectedList(vS, vE, w);
    createDirectedList(vE, vS, w);
}

//tworzenie skierowanej listy
void CombinedList::createDirectedList(int vS, int vE, int w) {

    edge *pointer = list[vS];

    do {
        if (pointer->vertex == -1) {
            pointer->vertex = vE;
            pointer->weight = w;
            break;
        } else {
            if (pointer->next == nullptr)
                pointer->next = new edge;
            pointer = pointer->next;

        }

    } while (true);
}
//wyswietlanie listy polaczonych sasiadow
void CombinedList::showList() {
    edge *pointer;
    for (int i = 0; i < size; i++) {
        std::cout << i << "  ";
        pointer = list[i];
        while (true) {
            if (pointer->vertex != -1)
                std::cout << pointer->vertex << " " << pointer->weight << "  ";
            if (pointer->next != nullptr)
                pointer = pointer->next;
            else
                break;
        }
        std::cout << "\n";
    }
}
//usuwanie listy
void CombinedList::deleteList() {
    edge *pointer;
    edge *pointer2;

    for (int i = 0; i < size; i++) {
        pointer = list[i];
        while (true) {
            if (pointer->next != nullptr) {
                pointer2 = pointer->next;
                delete pointer;
                pointer = pointer2;
            } else {
                delete pointer;
                break;
            }
        }
    }
    delete list;
}

CombinedList::EdgeList **CombinedList::getList() {
    return list;
}

int CombinedList::getSize() const {
    return size;
}
