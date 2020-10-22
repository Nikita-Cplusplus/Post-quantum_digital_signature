#ifndef MYALGEBRA_H
#define MYALGEBRA_H

#include "gf.h"
#include <QVector>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class myAlgebra
{
private:
    vector<GF> vec;
    static vector<GF> structure_coef; //можно по умолчанию иницииализировать два элемента 1, перегрузив конструктор GF булевыми значениями (0 и 1)
public:
    myAlgebra(GF a, GF b, GF c, GF d);
    myAlgebra();
    vector<GF> get_coordinate();
    vector<GF> get_structure_coef();
    QVector<QString> getStringCoordinate();
    static void set_structure_coef(GF lambda, GF mu);
    friend myAlgebra Eglobal(myAlgebra);//******************************************
    friend myAlgebra Eright(myAlgebra);//***
    friend myAlgebra Eleft(myAlgebra);//***
    friend myAlgebra Edual(myAlgebra);//*** ПОДУМАТЬ НАД ЦЕЛЕСООБРАЗНОСТЬЮ ЭТИХ FRIEND ФУНКЦИЙ ***
    friend myAlgebra ErightIrr(myAlgebra);//***
    friend myAlgebra EleftIrr(myAlgebra);//***
    friend myAlgebra EdualIrr(myAlgebra);//*****************************************
    friend myAlgebra fastPower(myAlgebra, vector<bool>);
    friend myAlgebra fastPower(myAlgebra, cpp_int);
    friend myAlgebra operator+(myAlgebra, myAlgebra);
    friend myAlgebra operator*(myAlgebra, myAlgebra);
    friend bool operator==(myAlgebra, myAlgebra);
    friend myAlgebra inverse(myAlgebra);
};

#endif // MYALGEBRA_H
