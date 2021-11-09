
#ifndef ALGORYTMY2_NODEDP_H
#define ALGORYTMY2_NODEDP_H


class NodeDP {
public:
    ///koszt uzyskania zbioru
    int value = INT_MAX;
    ///numer wierzchołka
    int vertex;
    ///wektor zawierający obecny zbiór dla węzła
    std::vector<int> S;
    ///wskaźnik na wierzchołek potomka z najmniejszym kosztem
    NodeDP * minNode = nullptr;
    NodeDP(std::vector<int> S, int vertex){
        this->S = std::move(S);
        this->vertex = vertex;
    }
};


#endif //ALGORYTMY2_NODEDP_H
