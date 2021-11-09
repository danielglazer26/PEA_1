#ifndef ALGORYTMYDOKLADNE_LOADFROMFILE_H
#define ALGORYTMYDOKLADNE_LOADFROMFILE_H


#include <fstream>

class LoadFromFile {
public:
    bool openFile();

    int getDataFromFile();

    ~LoadFromFile() {
        file.close();
    }
private:

    std::fstream file;
};



#endif //ALGORYTMYDOKLADNE_LOADFROMFILE_H
