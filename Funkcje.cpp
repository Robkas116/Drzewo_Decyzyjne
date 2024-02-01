#include<iostream>
#include <string>
#include <set>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include<string.h>

#include "funkcje.h"

/**@brief
* LoadMatrix to funkcja wczytująca dane do macierzy
* @note Funkcja wczytuje dane do macierzy z pominięciem pierwszej linijki, w której zawiera się opis kolumn
* @param fileName: Nazwa pliku, z którego pobieramy dane do programu
* @return LoadMatrix zwraca macierz double
**/

Matrix LoadMatrix(const std::string& fileName) {
    Matrix m;
    std::ifstream in(fileName);
    if (in) {
        std::string line;
        std::string zapasowe;
        std::getline(in, zapasowe);   //pozbycie sie linijki z opisem danych
        while (std::getline(in, line)) {
            m.push_back(Vector());
            std::stringstream ss(line);
            std::string x;
            while (std::getline(ss, x, ' ')) {
                m.back().push_back(std::stod(x));   //wrzucenie danych do macierzy
            }
        }
        in.close();
    }
    return m;
}

/**@brief
* Funkcja LoadList pobiera pierwszą linijkę z pliku z danymi, gdzie są nazwy kolumn danych
* @param fileName: Nazwa pliku, z którego pobieramy dane do programu
* @return Funkcja LoadList zwraca wektor
* */
std::vector<std::string> LoadList(const std::string& fileName) {
    std::vector<std::string> v;
    std::ifstream in(fileName);
    if (in) {
        std::string line;
        std::string nazwa;
        std::getline(in, line);
        std::stringstream ss(line);
        while (ss >> nazwa) {
            v.push_back(nazwa);     //wrzucenie opisu kolumn danych do wektora
        }
    }
    in.close();
    return v;

}
/**@brief
* Funkcja SaveToFile zapisuje macierz string do pliku
* @note Nadpisuje plik do którego ma zapisać wynik lub tworzy, jęsli takiego nie ma
* @param fileName: Nazwa pliku, do którego program zapisuje macierz
* @param sm: Macierz string, w któej znajdują się poprzydzielane dane do odpowiednich etykiet
* */
void SaveToFile(const std::string& fileName, const String_Matrix& sm) {
    std::ofstream out(fileName);
    if (out) {
        for (const auto& row : sm) {
            for (const auto el : row) {
                out << el << std::endl; //zapisanie macierzy string do pliku
            }
            out << std::endl;
        }
        out.close();
    }
}

/**@brief
* Funkcja LoadTree wczytuje z pliku model drzewa decyzyjnego
* @param fileName: Nazwa pliku, w którym znajduje się struktura drzewa decyzyjnego
* @return LoadTree zwraca wektor node (struktura), w którym jeden element to jeden węzeł drzewa binarnego
* */
std::vector<node> LoadTree(const std::string& fileName) {
    std::vector<node> v;
    std::ifstream in(fileName);
    if (in) {
        std::string line;
        node wezel;
        std::getline(in, line);
        while (std::getline(in, line)) {
            std::stringstream ss(line);
            ss >> wezel.numer >> wezel.argument >> wezel.znak >>
                wezel.wartosc >> wezel.tak >> wezel.nie;
            v.push_back(wezel);
        }
        in.close();
    }
    return v;
}

/**@brief
* Funkcja funkcja_srodkowa przydziela danemu podmiotowi etykietę, w zależności od jego parametrów, przepuszczając jego dane przez drzewo decyzyjne
* @note funkcja_srodkowa wywołuje się rekurencyjnie, kiedy musi przejść do kolejnego węzła
* @param numer: Numer węzła, w którym jest sprawdzany warunek (początkowy węzeł zawsze ma numer 0, ponieważ jest to korzeń drzewa
* @param rzad: Podmiot, którego parametry są sprawdzane przez drzewo i którego się dodaje na koniec do etykiety w liściu drzewa
* @param list: Nazwy kolumn macierzy danych, dzięki temu wiadomo, które dane trzeba porównać z wartością w węźle drzewa
* @param v: Wektor przechowujący model drzewa
* @param etykiety: Referencyjna macierz string, w której poprzydzielane są podmioty do swoich etykiet
* */

void funkcja_srodkowa(double numer, std::vector<double> rzad, std::vector<std::string> list,
    std::vector<node> v, String_Matrix& etykiety) {  //funkcja wrzucająca każdą osobę przez drzewo i zapisanie do macierzy string
    double dana;

    std::string znak;
    for (int i = 0; i < rzad.size(); i++) {
        if (list[i] == v[numer].argument) {  //przypisanie danej w zależności od argumentu węzła drzewa
            dana = rzad[i];
        }
    }
    znak = v[numer].znak; //przypisanie znaku w zależności od numeru węzła drzewa
    double wartosc = v[numer].wartosc;  //przypisanie wartości do której się porównuje w zależności od numeru węzła drzewa
    if (znak == "<") { //sprawdzenie pierwszego przypadku znaku drzewa
        if (dana < wartosc) { //porównanie danej z wartością
            if (size(v[numer].tak) == 1 || size(v[numer].tak) == 2) { //sprawdzenie czy następny jest węzeł czy liść drzewa
                double numer_tak = stod(v[numer].tak);
                funkcja_srodkowa(numer_tak, rzad, list, v, etykiety); //rekurencyjne przejście do kolejnego węzła
            }
            else { //jest liść drzewa
                std::string element;
                for (int j = 0; j < rzad.size(); j++) {
                    std::ostringstream s;
                    s << rzad[j];
                    std::string str = s.str();
                    element += str + " ";       //zapis wszystkich danych osoby do jednego stringa
                }
                for (int j = 0; j < etykiety.size(); j++) {
                    if (v[numer].tak == etykiety[j][0]) //wybór rzędy macierzy do zapisu osoby
                        etykiety[j].push_back(element); //zapisanie przypadku do macierzy
                }
            }
        }
        else {
            if (size(v[numer].nie) == 1 || size(v[numer].nie) == 2) { //sprawdzenie czy następny jest węzeł
                double numer_nie = stod(v[numer].nie);
                funkcja_srodkowa(numer_nie, rzad, list, v, etykiety); //wywołanie rekurencyjne dla kolejnego węzła
            }
            else {
                std::string element;
                for (int j = 0; j < rzad.size(); j++) {
                    std::ostringstream s;
                    s << rzad[j];
                    std::string str = s.str();
                    element += str + " "; //zapisanie danych osoby do jednego stringa
                }
                for (int j = 0; j < etykiety.size(); j++) {
                    if (v[numer].nie == etykiety[j][0]) //znalezienie odpowiadającego rzedu w macierzy
                        etykiety[j].push_back(element); //wrzucenie przypadku do macierzy
                }
            }

        }
    }
    else if (znak == ">") { //analogicznie jak dla znak=="<"
        if (dana > wartosc) {
            if (size(v[numer].tak) == 1 || size(v[numer].tak) == 2) {
                double numer_tak = stod(v[numer].tak);
                funkcja_srodkowa(numer_tak, rzad, list, v, etykiety);
            }
            else {
                std::string element;
                for (int j = 0; j < rzad.size(); j++) {
                    std::ostringstream s;
                    s << rzad[j];
                    std::string str = s.str();
                    element += str + " ";
                }
                for (int j = 0; j < etykiety.size(); j++) {
                    if (v[numer].tak == etykiety[j][0])
                        etykiety[j].push_back(element);
                }
            }
        }
        else {
            if (size(v[numer].nie) == 1 || size(v[numer].nie) == 2) {
                double numer_nie = stod(v[numer].nie);
                funkcja_srodkowa(numer_nie, rzad, list, v, etykiety);
            }
            else {
                std::string element;
                for (int j = 0; j < rzad.size(); j++) {
                    std::ostringstream s;
                    s << rzad[j];
                    std::string str = s.str();
                    element += str + " ";
                }
                for (int j = 0; j < etykiety.size(); j++) {
                    if (v[numer].nie == etykiety[j][0])
                        etykiety[j].push_back(element);
                }
            }
        }
    }

}
/**@brief
* wywolanie_drzewa to główna funkcja wywoływana w funkcji main
* @note W tej funkcji wywoływana jest funkcja_srodkowa
* @param v: Wektor przechowujący model drzewa
* @param m: Macierz zaimplementowanych danych
* @param list: Wektor nazw kolumn macierzy danych
* @return Zwraca macierz string z poprzydzielanymi podmiotami do odpowiednich etykiet - tą macierz program wypisuje do pliku wyjściowego
* */
String_Matrix wywolanie_drzewa(std::vector<node> v, Matrix m, std::vector<std::string> list) {

    String_Matrix etykiety; //tworzenie macierzy etykiet, do których będą przypisywane dane
    for (int i = 0; i < v.size(); i++) {
        if (size(v[i].tak) > 2) { //sprawdzenie czy dla prawdziwego warunku jest liść
            bool if_break = 0;
            for (const auto& row : etykiety) {
                if (v[i].tak == row[0]) {   //sprawdzenie czy etykieta już jest w macierzy
                    if_break = 1;
                    break;
                }
            }
            if (!if_break) {    //wykona się jeśli etykiety nie było w macierzy jeszcze
                std::vector<std::string> etykieta;
                etykieta.push_back(v[i].tak);   //wsadzenie liścia do nowego rzędu
                etykiety.push_back(etykieta);   //wsadzenie nowego rzędu do macierzy
            }
        }
        for (int i = 0; i < v.size(); i++) {
            if (size(v[i].nie) > 2) {   //to samo co dla if ^^^
                bool if_break = 0;
                for (const auto& row : etykiety) {
                    if (v[i].nie == row[0]) {
                        if_break = 1;
                        break;
                    }
                }
                if (!if_break) {
                    std::vector<std::string> etykieta;
                    etykieta.push_back(v[i].nie);
                    etykiety.push_back(etykieta);
                }
            }
        }
    }

    for (int i = 0; i < m.size(); i++) { //pętla przechodząca przez wszystkie wierwsze macierzy danych
        funkcja_srodkowa(v[0].numer, m[i], list, v, etykiety);  //wywołanie funkcji dla jednego wiersza macierzy danych (osoby)
    }
    return etykiety;

}
