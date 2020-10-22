#ifndef ES_H
#define ES_H

#include "myalgebra.h"

class ES
{
private:
    myAlgebra N;
    myAlgebra G;
    myAlgebra T;
    cpp_int x;
    myAlgebra Y;
    myAlgebra Q;
    cpp_int e;
    cpp_int s;
    myAlgebra W;
public:
    ES();
    void genKeys();
    void genES();
    myAlgebra getQ();
    myAlgebra getY();
    QVector<QString> getData();
};

#endif // ES_H
