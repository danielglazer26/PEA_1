#include "../../Header/RepresentationOfGraph/LoadFromFile.h"
#include <iostream>

///załadowanie pliku grafu
bool LoadFromFile::openFile(){
    std::string nameOfFile = "gr17.tsp";

    /*std::cout << "Podaj nazwe pliku" << std::endl;
    std::cin >> nameOfFile;
    std::cout << "\n";*/
    file.open(nameOfFile);
    if(!file.is_open()) {
        std::cout << "Nie ma takiego pliku\n";
        return false;
    }
    else {
        std:: string fileName;
        file >> fileName;
        std::cout << "Otworzono plik " << fileName <<"\n";
        return true;
    }
}
///pobieranie liczb z plików
int LoadFromFile::getDataFromFile() {

    int number;

    file >> number;

    return number;

}