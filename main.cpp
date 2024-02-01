#include<iostream>
#include<map>


#include "funkcje.h"

/**@brief
* Główna funkcja wywołująca program
* */

int main(int argv, char* argc[]) {
    std::map<std::string, std::string> mapa;
    for (int i = 1; i < argv; i = i + 2) {
        mapa[argc[i]] = argc[i + 1];
    }
    std::vector<node> zaimplementowane_drzewo = LoadTree(mapa["-t"]);
    Matrix dane = LoadMatrix(mapa["-i"]);
    std::vector<std::string> naglowki = LoadList(mapa["-i"]);
    SaveToFile(mapa["-o"], wywolanie_drzewa(zaimplementowane_drzewo, dane, naglowki));
}