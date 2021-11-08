
#ifndef ALGORYTMY2_NODEDP_H
#define ALGORYTMY2_NODEDP_H


class NodeDP {
public:
    int value = INT_MAX;
    int vertex;
    std::vector<int> S;
    NodeDP * minNode = nullptr;
    NodeDP(std::vector<int> S, int vertex){
        this->S = std::move(S);
        this->vertex = vertex;
    }
};


#endif //ALGORYTMY2_NODEDP_H
