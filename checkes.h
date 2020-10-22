#ifndef CHECKES_H
#define CHECKES_H

#include "myalgebra.h"

class checkES
{
private:
    myAlgebra Y;
    myAlgebra Q;
    myAlgebra Wx;
    cpp_int HASH;
public:
    checkES(myAlgebra Y,myAlgebra Q);
    bool check();
    QVector<QString> getData();
};

#endif // CHECKES_H
