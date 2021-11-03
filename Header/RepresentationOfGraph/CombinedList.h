
#ifndef  ALGORYTMYDOKLADNE_EDGESSORTEDLIST_H

class CombinedList {


public:

    CombinedList(int size) {
        this->size = size;
        list = new EdgeList *[size];
        for (int i = 0; i < size; ++i) {
            list[i] = new edge();
        }
    }

    typedef struct edge {
        int vertex = -1;
        int weight;
        edge *next = nullptr;
    } EdgeList;

    ~CombinedList() { deleteList(); }

    void createUndirectedList(int vS, int vE, int w);

    void createDirectedList(int vS, int vE, int w);

    void showList();

    void deleteList();

    int getSize() const;

    EdgeList **getList();

private:

    EdgeList **list;

    int size;
};


#define  ALGORYTMYDOKLADNE_EDGESSORTEDLIST_H


#endif // ALGORYTMYDOKLADNE_EDGESSORTEDLIST_H
