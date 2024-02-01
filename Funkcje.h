#ifndef FUNKCJE_H
#define FUNKCJE_H
#include<string>
#include<vector>

typedef std::vector<std::vector<double>> Matrix; ///macierz double, w niej trzymane są dane
typedef std::vector<double> Vector; ///wektor double
typedef std::vector<std::string> Vector1; ///wektor string
typedef std::vector<std::vector<std::string>> String_Matrix; ///macierz wektorów string


/// struktura węzła drzewa

struct node {
    double numer;  ///numer węzła drzewa
    std::string argument; ///nazwa danej, którą chcemy porównać
    std::string znak;  ///odpowiednio znak operacji, którą chcemy wykonać ">" lub "<"
    double wartosc;     ///wartość, do której porównujemy argument
    std::string tak;    ///numer kolejnego węzła lub nazwa liścia drzewa, jeśli warunek jest spełniony
    std::string nie;    //////numer kolejnego węzła lub nazwa liścia drzewa, jeśli warunek nie jest spełniony
};

Matrix LoadMatrix(const std::string& fileName);
std::vector<std::string> LoadList(const std::string& fileName);
void SaveToFile(const std::string& fileName, const String_Matrix& sm);
std::vector<node> LoadTree(const std::string& fileName);
void funkcja_srodkowa(double numer, std::vector<double> rzad, std::vector<std::string> list,
    std::vector<node> v, String_Matrix& etykiety);
String_Matrix wywolanie_drzewa(std::vector<node> v, Matrix m, std::vector<std::string> list);






#endif
