#include "gf.h"
//#include <chrono>

GF u(GF a, GF b)
{
    if (a.getGF_element().size()<b.getGF_element().size()) // почему строго меньше?
    {
        vector<bool> nolik(0);
        return GF(nolik);
    }
    vector<bool> chastnoe;
    vector<bool> rez = a.getGF_element();
    for (int i = int(a.getGF_element().size() -1) ; i >= int(b.getGF_element().size()) - 1 ; --i)
    {
        if(rez[i] == 1)
        {
            chastnoe.push_back(1);
            for (int j = int(b.getGF_element().size()) - 1, k = 0; j >= 0; --j,++k)
            {
                rez[i-k] = rez[i-k] ^ b.getGF_element()[j];
            }
        }
        else
            chastnoe.push_back(0);
    }
    reverse(chastnoe.begin(),chastnoe.end());
    return GF(chastnoe);
}

GF r(GF a, GF b)
{
    if (a.getGF_element().size()<b.getGF_element().size())
    {
        return a;
    }
    vector<bool> rez = a.getGF_element();
    for (int i = int(a.getGF_element().size() -1) ; i >= int(b.getGF_element().size()) - 1 ; --i)
    {
        if(rez[i] == 1)
        {
            for (int j = int(b.getGF_element().size()) - 1, k = 0; j >= 0; --j,++k)
            {
                rez[i-k] = rez[i-k] ^ b.getGF_element()[j];
            }
        }
    }
    rez.resize(int(b.getGF_element().size()) - 1);
    return GF(rez);
}

GF gcd (GF a, GF b, GF & x, GF & y) {
    if (a == 0)
    {
        vector<bool> xvec(1);
        vector<bool> yvec(1, 1);
        x.setGF_element(xvec);
        y.setGF_element(yvec);
        return b;
    }
    GF x1, y1;
    GF d = gcd (r(b,a), a, x1, y1);
    x = y1 + u(b,a) * x1;
    y = x1;
    return d;
}

vector<bool> GF::irreduciblePoly;

GF::GF(vector<bool> element)
{
    power = int(element.size());
    for (int i = int(element.size())-1; i>0; --i)
    {
        if (element[i] == 0)
            element.pop_back();
        else
            break;
    }
    GF_element = element;
}

GF::GF() // вот с этим могут быть проблемы
{
    power = -1;
}

void GF::setIrreduciblePoly(vector<bool> a)
{
    irreduciblePoly = a;
}

void GF::setGF_element(vector<bool> a)
{
    GF_element = a;
}

vector<bool> GF::getGF_element()
{
    return GF_element;
}

vector<bool> GF::getIrreduciblePoly() //используется только в обратном inverse ХЗ зачем, надо бы удалить
{
    return irreduciblePoly;
}

//int GF::getpower()
//{
//    return power;
//}

//GF inverse(GF el)
//{
//    vector<bool> inverVector(el.getpower());
//    vector<bool> etalon(el.getpower());
//    inverVector[0] = 1;
//    etalon[0] = 1;
//    GF inver(inverVector);
//    vector<bool> unit = inverVector;
//    for(int i = 0 ; i < el.getpower()*el.getpower() ; ++i)
//    {
//        if((el*inver).getGF_element() == unit)
//        {
//            break;
//        }
//        for (int j = 0; j < el.getpower(); ++j)
//        {
//            if(inverVector[j] == 1 && inverVector != etalon)
//                inverVector[j] = 0;
//            else
//            {
//                inverVector[j] = 1;
//                inver.setGF_element(inverVector);
//            }
//        }
//    }
//    return inver;
//}

GF inverse(GF el)
{
    vector<bool> rez = el.getGF_element();
    for (int i = int(rez.size())-1; i >= int(el.getIrreduciblePoly().size())-1; --i)
    {
        if(rez[i] == 1)
        {
            for (int j = int(el.getIrreduciblePoly().size()) - 1, k = 0; j >= 0; --j,++k)
            {
                rez[i-k] = rez[i-k] ^ el.getIrreduciblePoly()[j];
            }
        }

    }
    rez.resize(int(el.getIrreduciblePoly().size()) - 1);
    for (int i = int(rez.size())-1; i>0; --i)
    {
        if (rez[i] == 0)
            rez.pop_back();
        else
            break;
    }
    GF normalEL(rez);
    GF x;
    GF y;
    gcd(normalEL.getGF_element(), el.getIrreduciblePoly(),x,y);
    return x;
}

GF operator+(GF left, GF right)
{
    vector<bool>a;
    if(left.GF_element.size()<right.GF_element.size())
    {
        a.resize(right.getGF_element().size());
        left.GF_element.resize(right.GF_element.size());
    }
    else
    {
        a.resize(left.getGF_element().size());
        right.GF_element.resize(left.GF_element.size());
    }
    for (int i = 0; i < int(left.GF_element.size()) ; ++i)
    {
        a[i] = left.GF_element[i] ^ right.GF_element[i];
    }
    for (int i = int(a.size())-1 ; i >= int(left.getIrreduciblePoly().size()) - 1 ; --i) // остаток от деления большого многочлена на неприводимый
    {
        if(a[i] == 1)
        {
            for (int j = int(left.getIrreduciblePoly().size()) - 1, k = 0; j >= 0; --j,++k)
            {
                a[i-k] = a[i-k] ^ left.getIrreduciblePoly()[j];
            }
        }
    }
    a.resize(int(left.getIrreduciblePoly().size()) - 1);
    for (int i = int(a.size())-1; i>0; --i)
    {
        if (a[i] == 0)
            a.pop_back();
        else
            break;
    }
    return GF(a);
}

//GF operator*(GF left, GF right) // старое умножение, тут полиномы строго меньшей степени, чем приводимый
//{
//    vector<bool>rez(left.getpower()*2 - 1);
//    for (int i = 0 ; i < right.getpower() ; ++i) // умножение многочленов
//    {
//        if(right.getGF_element()[i] == 1)
//        {
//            for (int j = i; j < i + left.getpower(); ++j)
//            {
//                rez[j] = rez[j] ^ left.getGF_element()[j-i];
//            }
//        }
//    }
//    for (int i = left.getpower()*2 - 2 ; i > left.getpower() - 1 ; --i) // остаток от деления большого многочлена на неприводимый
//    {
//        if(rez[i] == 1)
//        {
//            for (int j = left.getpower(), k = 0; j >= 0; --j,++k)
//            {
//                rez[i-k] = rez[i-k] ^ left.getIrreduciblePoly()[j];
//            }
//        }
//    }
//    rez.resize(left.getpower());
//    return GF(rez);
//}

GF operator*(GF left, GF right)
{
    vector<bool>rez(left.getGF_element().size()+right.getGF_element().size()-1);
    for (int i = 0 ; i < int(right.getGF_element().size()) ; ++i) // умножение многочленов
    {
        if(right.getGF_element()[i] == 1)
        {
            for (int j = i; j < i + int(left.getGF_element().size()); ++j)
            {
                rez[j] = rez[j] ^ left.getGF_element()[j-i];
            }
        }
    }
    for (int i = int(left.getGF_element().size()+right.getGF_element().size())-2 ; i >= int(left.getIrreduciblePoly().size()) - 1 ; --i) // остаток от деления большого многочлена на неприводимый
    {
        if(rez[i] == 1)
        {
            for (int j = int(left.getIrreduciblePoly().size()) - 1, k = 0; j >= 0; --j,++k)
            {
                rez[i-k] = rez[i-k] ^ left.getIrreduciblePoly()[j];
            }
        }
    }
    rez.resize(int(left.getIrreduciblePoly().size()) - 1);
    for (int i = int(rez.size())-1; i>0; --i)
    {
        if (rez[i] == 0)
            rez.pop_back();
        else
            break;
    }
    return GF(rez);
}

//GF fast_power(GF el, const vector<bool> &n)
//{
//    GF pow = el;
//    vector<bool> edin(1,1);
//    GF result(edin);
//    for (vector<bool>::const_iterator i = n.begin(); i < n.end(); ++i)
//    {
//        if (*i == 1)
//        {
//            result =result * pow;
//            pow = pow*pow;
//            //cout << "power"<<endl;
//        }
//        else
//        {
//            pow = pow*pow;
//            //cout << "power"<<endl;
//        }
//    }
//    return result;
//}

GF M_power(GF el, const int &n)
{
    GF pow = el;
    vector<bool> edin(1,1);
    GF result(edin);
    for (int g = n ; g > 0 ; g--)
    {
        result =result * pow;
        pow = pow*pow;
    }
    return result;
}

bool operator==(GF left, GF right)
{
    if(left.getGF_element() == right.getGF_element())
        return true;
    else
        return false;
}

bool operator==(GF left, bool right)
{
    if (right == 0)
    {
        bool flag = 1;
        for (int i = int(left.GF_element.size())-1; i >= 0 ; --i)
        {
            if(left.GF_element[i] == 1)
            {
                flag = 0;
                break;
            }
        }
        return flag;
    }
    else
    {
        bool flag = 1;
        for (int i = int(left.GF_element.size())-1; i > 0 ; --i)
        {
            if(left.GF_element[i] == 1)
            {
                flag = 0;
                break;
            }
        }
        if ((left.GF_element[0] == 0) && (flag == 1))
            flag = 0;
        return flag;
    }
}

void genIrrPoly(int n)
{
   // cout << "go"<<endl;
    //vector<bool> stepen(n,1);
    vector<bool> neprivodim(n+1);
    neprivodim[n] = 1;
    bool flag = 0;
    while(flag == 0)
    {
        for (int i = 1 ; i < int(neprivodim.size()) -1 ; ++i)
        {
            neprivodim[i] = rand()%2;
        }
        neprivodim[0] = 1;
        GF::irreduciblePoly = neprivodim;
        int c = 1;
        while (c < 20)
        {
            vector<bool> ro(n);
            for (int i = 0 ; i < int(ro.size()) ; ++i)//но можно же просто прибавлять 1
            {
                ro[i] = rand()%2;
            }
            for (int i = int(ro.size())-1; i>0; --i)
            {
                if (ro[i] == 0)
                    ro.pop_back();
                else
                    break;
            }
            GF gf_ro(ro);
            if((M_power(gf_ro, n) == 1) && !(gf_ro == 1))
            {
                flag = 1;
                break;
            }
            else
            {
                if (c<20)
                    c += 1;
                else
                    break;
            }
        }
    }
}
