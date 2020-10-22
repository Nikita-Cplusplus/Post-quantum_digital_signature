#include "checkes.h"
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>

checkES::checkES(myAlgebra Y,myAlgebra Q)
{
    this->Y = Y;
    this->Q = Q;
}

bool checkES::check()
{
    QFile fileName;
    fileName.setFileName("C:/Users/04041/Documents/es.txt");
    fileName.open(QIODevice::ReadWrite | QIODevice::Text);
    QString textE="";
    QString textS="";
    QVector<QString> buf;
    QTextStream stream(&fileName);
    while (!stream.atEnd())
    {
        textE = textS;
        textS = stream.readLine();
        buf.push_back(textS);
    }
    buf.pop_back();
    buf.pop_back();
    fileName.resize(0);
    for (QVector<QString>::iterator i = buf.begin(); i != buf.end(); ++i)
    {
        stream << (*i);
        if (i < buf.end() - 1)
            stream << "\n";
    }
    fileName.close();
    cpp_int eN(textE.toStdString());
    cpp_int sN(textS.toStdString());
    Wx = fastPower(Y,eN)*fastPower(Q,sN);
    fileName.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    stream << "\n" << Wx.getStringCoordinate()[0] << Wx.getStringCoordinate()[1] << Wx.getStringCoordinate()[2] << Wx.getStringCoordinate()[3];
    fileName.close();
    QCryptographicHash calculateSha1(QCryptographicHash::Sha1);
    fileName.open(QIODevice::ReadOnly | QIODevice::Text);
    calculateSha1.addData(fileName.readAll());
    fileName.close();
    QString hash = calculateSha1.result().toHex();
    fileName.open(QIODevice::ReadWrite | QIODevice::Text);
    QVector<QString> buf2;
    while (!stream.atEnd())
    {
        buf2.push_back(stream.readLine());
    }
    buf2.pop_back();
    fileName.resize(0);
    for (QVector<QString>::iterator i = buf2.begin(); i != buf2.end(); ++i)
    {
        stream << (*i);
        if (i < buf2.end() - 1)
            stream << "\n";
    }
    fileName.close();
    cpp_int forhash("0x"+hash.toStdString());
    HASH = forhash;
    if (textE == QString::fromStdString(forhash.str()))
        return true;
    else
        return false;
}

QVector<QString> checkES::getData()
{
    QVector<QString> Data;
    Data.push_back(Wx.getStringCoordinate()[0]);
    Data.push_back(Wx.getStringCoordinate()[1]);
    Data.push_back(Wx.getStringCoordinate()[2]);
    Data.push_back(Wx.getStringCoordinate()[3]);
    Data.push_back(QString::fromStdString(HASH.str()));
    return Data;
}
