#include "es.h"
#include <QFile>
#include <QCryptographicHash>
#include <QTextStream>
//#include <iostream>

GF genGF()
{
    vector<bool> n(GF::getIrreduciblePoly().size()-1);
    for(int i = 0; i <int(n.size()); ++i)
        n[i] = rand()%2;
    return GF(n);
}

ES::ES()
{

}

void ES::genKeys()
{
    GF lam;
    GF mu;
    do
    {
        lam = genGF();
        mu = genGF();
    } while (lam == mu);
    myAlgebra::set_structure_coef(lam, mu);
    GF a1 = genGF();
    GF b1 = genGF();
    GF c1 = genGF();
    GF d1 = a1*b1*inverse(c1);
    N = myAlgebra(a1,b1,c1,d1);
    myAlgebra E1;
    do
    {
        E1 = Edual(N);
    }while (E1.get_coordinate()[0]*E1.get_coordinate()[1] == E1.get_coordinate()[2]*E1.get_coordinate()[3]);
    myAlgebra E2;
    do
    {
        E2 = Edual(N);
    }while (E1.get_coordinate()[0]*E1.get_coordinate()[1] == E1.get_coordinate()[2]*E1.get_coordinate()[3]);
    myAlgebra E3 = EdualIrr(N);
    GF a2, b2, c2, d2;
    do
    {
        a2 = genGF();
        b2 = genGF();
        c2 = genGF();
        d2 = genGF();
        G = myAlgebra(a2,b2,c2,d2);
    }while ((a2*b2 == d2*c2)&&(G*N == N*G));
    myAlgebra U = E1*inverse(G);
    myAlgebra H = inverse(U)*E2;
    T = E3*inverse(H);
    for (int i = 0 ; i < int(GF::getIrreduciblePoly().size())-2 ; ++i)//реализуй подругому -2 глаза режет
    {
        cpp_int sth=rand()%2;
        x += sth<<i;
    }
    Y = G*fastPower(N,x)*U;
    Q = H*N*T;
}

void ES::genES()
{
    cpp_int k;
    for (int i = 0 ; i < int(GF::getIrreduciblePoly().size())-2 ; ++i)//реализуй подругому -2 глаза режет
    {
        cpp_int sth=rand()%2;
        k += sth<<i;
    }
    W = G*fastPower(N,k)*T;
    QFile fileName;
    fileName.setFileName("C:/Users/04041/Documents/es.txt");
    fileName.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QTextStream stream(&fileName);
    stream << "\n" << W.getStringCoordinate()[0] << W.getStringCoordinate()[1] << W.getStringCoordinate()[2] << W.getStringCoordinate()[3];
    fileName.close();
    QCryptographicHash calculateSha1(QCryptographicHash::Sha1);
    fileName.open(QIODevice::ReadOnly | QIODevice::Text);
    calculateSha1.addData(fileName.readAll());
    fileName.close();
    QString hash = calculateSha1.result().toHex();
    fileName.open(QIODevice::ReadWrite | QIODevice::Text);
    QVector<QString> buf;
    while (!stream.atEnd())
    {
        buf.push_back(stream.readLine());
    }
    buf.pop_back();
    fileName.resize(0);
    for (QVector<QString>::iterator i = buf.begin(); i != buf.end(); ++i)
    {
        stream << (*i);
        if (i < buf.end() - 1)
            stream << "\n";
    }
    fileName.close();
    cpp_int HASH("0x"+hash.toStdString());
    e = HASH;
    cpp_int one = 1;
    cpp_int modul = (one<<(GF::getIrreduciblePoly().size()-1))-1;
    s = (k - e*x)%modul;
    if (s<0)
        s+=modul;
    QString textE = QString::fromStdString(e.str());
    QString textS = QString::fromStdString(s.str());
    fileName.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
    stream << "\n" << textE << "\n" << textS;
    fileName.close();
}

myAlgebra ES::getQ()
{
    return Q;
}

myAlgebra ES::getY()
{
    return Y;
}

QVector<QString> ES::getData()
{
    QVector<QString> Data;
    Data.push_back(N.getStringCoordinate()[0]);
    Data.push_back(N.getStringCoordinate()[1]);
    Data.push_back(N.getStringCoordinate()[2]);
    Data.push_back(N.getStringCoordinate()[3]);
    Data.push_back(G.getStringCoordinate()[0]);
    Data.push_back(G.getStringCoordinate()[1]);
    Data.push_back(G.getStringCoordinate()[2]);
    Data.push_back(G.getStringCoordinate()[3]);
    Data.push_back(T.getStringCoordinate()[0]);
    Data.push_back(T.getStringCoordinate()[1]);
    Data.push_back(T.getStringCoordinate()[2]);
    Data.push_back(T.getStringCoordinate()[3]);
    Data.push_back(QString::fromStdString(x.str()));
    Data.push_back(Y.getStringCoordinate()[0]);
    Data.push_back(Y.getStringCoordinate()[1]);
    Data.push_back(Y.getStringCoordinate()[2]);
    Data.push_back(Y.getStringCoordinate()[3]);
    Data.push_back(Q.getStringCoordinate()[0]);
    Data.push_back(Q.getStringCoordinate()[1]);
    Data.push_back(Q.getStringCoordinate()[2]);
    Data.push_back(Q.getStringCoordinate()[3]);
    Data.push_back(QString::fromStdString(e.str()));
    Data.push_back(QString::fromStdString(s.str()));
    Data.push_back(W.getStringCoordinate()[0]);
    Data.push_back(W.getStringCoordinate()[1]);
    Data.push_back(W.getStringCoordinate()[2]);
    Data.push_back(W.getStringCoordinate()[3]);
    return Data;
}
