#ifndef GF_H
#define GF_H

#include <vector>

using namespace std;

class GF
{
private:
   int power;
   vector<bool> GF_element;
   static vector<bool> irreduciblePoly;
public:
    GF(vector<bool> GF_element);
    GF(); // вот с этим могут быть проблемы
    static void setIrreduciblePoly(vector<bool> a);
    void setGF_element(vector<bool> a);
    vector<bool> getGF_element();
    static vector<bool> getIrreduciblePoly(); // static добавил
    int getpower();
    friend GF operator+(GF, GF);
    friend GF operator*(GF, GF);
    //friend GF fast_power(GF,const vector<bool>&);
    friend GF M_power(GF,const int&);
    friend bool operator==(GF, GF);
    friend bool operator==(GF, bool);
    friend GF inverse(GF);
    friend void genIrrPoly(int);
};
void genIrrPoly(int);
GF M_power(GF,const int&);//это для дебага

#endif // GF_H
