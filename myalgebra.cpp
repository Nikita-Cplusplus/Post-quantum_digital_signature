#include "myalgebra.h"

#define X1 el1.vec[0]
#define X2 el1.vec[1]
#define X3 el1.vec[2]
#define X4 el1.vec[3]
#define Y1 el2.vec[0]
#define Y2 el2.vec[1]
#define Y3 el2.vec[2]
#define Y4 el2.vec[3]
#define LAMBDA myAlgebra::structure_coef[0]
#define MU myAlgebra::structure_coef[1]

vector<GF> myAlgebra::structure_coef;

myAlgebra::myAlgebra(GF a, GF b, GF c, GF d)
{
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    vec.push_back(d);
}

myAlgebra::myAlgebra()
{

}

vector<GF> myAlgebra::get_coordinate()
{
//    switch(a)
//    {
//    case 'a':
//        return vec[0];
//        break;
//    case 'b':
//        return vec[1];
//        break;
//    case 'c':
//        return vec[2];
//        break;
//    case 'd':
//        return vec[3];
//        break;
//    default:
//        return GF();
//    }
    return vec;
}

QVector<QString> myAlgebra::getStringCoordinate()
{
    QVector<QString> result(4);
    for (int i = 0 ; i <= 3 ; ++i)
    {
        vector<bool> buf = vec[i].getGF_element();
        for(vector<bool>::reverse_iterator j = buf.rbegin(); j != buf.rend(); ++j)
        {
            if (*j == 1)
                result[i].append('1');
            else
                result[i].append('0');
        }
    }
    return result;
}

//vector<GF> myAlgebra::get_structure_coef()
//{
//    return structure_coef;
//}

void myAlgebra::set_structure_coef(GF lambda, GF mu)
{
    structure_coef.push_back(lambda);
    structure_coef.push_back(mu);
}

myAlgebra Eglobal(myAlgebra el1)
{
    GF deb = inverse(LAMBDA + MU);
    return myAlgebra(LAMBDA*inverse(LAMBDA + MU),inverse(LAMBDA + MU),inverse(LAMBDA + MU),MU*inverse(LAMBDA + MU));
}

myAlgebra Eleft(myAlgebra el1)
{
    vector<bool> i_forGF(el1.vec[0].getIrreduciblePoly().size()-1);
    vector<bool> j_forGF(el1.vec[0].getIrreduciblePoly().size()-1);
    for(int i = 0; i <int(i_forGF.size()); ++i)//совместить эти две шляпы в один!!!
        i_forGF[i] = rand()%2;
    for(int i = 0; i <int(j_forGF.size()); ++i)//совместить эти две шляпы в один!!!
        j_forGF[i] = rand()%2;
    GF i_gf(i_forGF);
    GF j_gf(j_forGF);
    return myAlgebra(i_gf,
                     X3*inverse(X1+LAMBDA*X3) + (X1+MU*X3)*inverse(X1+LAMBDA*X3)*j_gf,
                     j_gf,
                     X1*inverse(X1+LAMBDA*X3) + (X1+MU*X3)*inverse(X1+LAMBDA*X3)*i_gf);
}

myAlgebra EleftIrr(myAlgebra el1)
{
    vector<bool> i_forGF(el1.vec[0].getIrreduciblePoly().size()-1);
    for(int i = 0; i <int(i_forGF.size()); ++i)
        i_forGF[i] = rand()%2;
    GF i_gf(i_forGF);
    return myAlgebra(i_gf,
                     X3*inverse(X1+LAMBDA*X3) + (X1+MU*X3)*inverse(X1+LAMBDA*X3)*X3*inverse(X1)*i_gf,//можно оптимальней
                     X3*inverse(X1)*i_gf,//можно оптимальней
                     X1*inverse(X1+LAMBDA*X3) + (X1+MU*X3)*inverse(X1+LAMBDA*X3)*i_gf);
}

myAlgebra Eright(myAlgebra el1)
{
    vector<bool> k_forGF(el1.vec[0].getIrreduciblePoly().size()-1);
    vector<bool> h_forGF(el1.vec[0].getIrreduciblePoly().size()-1);
    for(int i = 0; i < int(k_forGF.size()); ++i)//совместить эти две шляпы в один!!!
        k_forGF[i] = rand()%2;
    for(int i = 0; i < int(h_forGF.size()); ++i)//совместить эти две шляпы в один!!!
        h_forGF[i] = rand()%2;
    GF k_gf(k_forGF);
    GF h_gf(h_forGF);
    return myAlgebra(X3*inverse(X2+X3) + (LAMBDA*X2+MU*X3)*inverse(X2+X3)*k_gf,
                     h_gf,
                     k_gf,
                     X2*inverse(X2+X3) + (LAMBDA*X2+MU*X3)*inverse(X2+X3)*h_gf);
}

myAlgebra ErightIrr(myAlgebra el1)
{
    vector<bool> h_forGF(el1.vec[0].getIrreduciblePoly().size()-1);
    for(int i = 0; i < int(h_forGF.size()); ++i)
        h_forGF[i] = rand()%2;
    GF h_gf(h_forGF);
    return myAlgebra(X3*inverse(X2+X3) + (LAMBDA*X2+MU*X3)*inverse(X2+X3)*X3*inverse(X2)*h_gf,//можно оптимальней
                     h_gf,
                     X3*inverse(X2)*h_gf,//можно оптимальней
                     X2*inverse(X2+X3) + (LAMBDA*X2+MU*X3)*inverse(X2+X3)*h_gf);
}

myAlgebra Edual(myAlgebra el1)
{
    vector<bool> k_forGF(el1.vec[0].getIrreduciblePoly().size()-1);
    for(int i = 0; i < int(k_forGF.size()); ++i)
        k_forGF[i] = rand()%2;
    GF k_gf(k_forGF);
    return myAlgebra(X3*inverse(X2+X3) + (LAMBDA*X2 + MU*X3)*inverse(X2+X3)*k_gf,
                     X3*inverse(X1+LAMBDA*X3) + (X1 + MU*X3)*inverse(X1 + LAMBDA*X3)*k_gf,
                     k_gf,
                     (X1*X2 + MU*X3*X3)*inverse((X2+X3)*(X1+LAMBDA*X3)) + (X1+MU*X3)*(LAMBDA*X2 + MU*X3)*inverse((X2+X3)*(X1+LAMBDA*X3))*k_gf);
}

myAlgebra EdualIrr(myAlgebra el1)
{
    return myAlgebra(X3*inverse(X2+X3) + (LAMBDA*X2 + MU*X3)*inverse(X2+X3)*X3*inverse(X4+X1+MU*X3+LAMBDA*X2),
                     X3*inverse(X1+LAMBDA*X3) + (X1 + MU*X3)*inverse(X1 + LAMBDA*X3)*X3*inverse(X4+X1+MU*X3+LAMBDA*X2),
                     X3*inverse(X4+X1+MU*X3+LAMBDA*X2),
                     (X1*X2 + MU*X3*X3)*inverse((X2+X3)*(X1+LAMBDA*X3)) + (X1+MU*X3)*(LAMBDA*X2 + MU*X3)*inverse((X2+X3)*(X1+LAMBDA*X3))*X3*inverse(X4+X1+MU*X3+LAMBDA*X2));
}

myAlgebra fastPower(myAlgebra el, vector<bool> n)
{
    myAlgebra powered = el;
    myAlgebra result = el; // костыль =)
    vector<bool>::reverse_iterator sec;
    for (vector<bool>::reverse_iterator i = n.rbegin(); i != n.rend(); ++i)
    {
        if (*i == 1)
        {
            result = powered;
            powered = powered*powered;
            sec = i;
            break;
        }
        else
        {
            powered = powered*powered;
        }
    }
    for (;sec!= n.rend(); ++sec)
    {
        if (*sec == 1)
        {
            result =result * powered;
            powered = powered*powered;
        }
        else
        {
            powered = powered*powered;
        }
    }
    return result;
}

myAlgebra fastPower(myAlgebra el, cpp_int n)
{
    myAlgebra powered = el;
    myAlgebra result = el;
    while (n>0)
    {
        if (n%2 == 1)
        {
            result = powered;
            powered = powered*powered;
            n = (n-1)/2;
            break;
        }
        else
        {
            powered = powered*powered;
            n /=2;
        }
    }
    while (n>0)
    {
        if (n%2 == 1)
        {
            result = result*powered;
            powered = powered*powered;
            n = (n-1)/2;
        }
        else
        {
            powered = powered*powered;
            n /=2;
        }
    }
    return result;
}

myAlgebra inverse(myAlgebra el1)
{
    GF a, b, c, d;
    a = (LAMBDA*LAMBDA*X2+LAMBDA*MU*X3+MU*X1+LAMBDA*X4)*inverse((LAMBDA+MU)*(LAMBDA+MU)*(X1*X2+X3*X4));
    b = (X1+X4+MU*X2+MU*X3)*inverse((LAMBDA+MU)*(LAMBDA+MU)*(X1*X2+X3*X4));
    c = (X1+X4+LAMBDA*X2+LAMBDA*X3)*inverse((LAMBDA+MU)*(LAMBDA+MU)*(X1*X2+X3*X4));
    d = (MU*MU*X3+MU*LAMBDA*X2+MU*X1+LAMBDA*X4)*inverse((LAMBDA+MU)*(LAMBDA+MU)*(X1*X2+X3*X4));
    return (myAlgebra(a,b,c,d));
}

myAlgebra operator+(myAlgebra el1, myAlgebra el2)
{
    return myAlgebra(X1+Y1, X2+Y2, X3+Y3, X4+Y4);
}

myAlgebra operator*(myAlgebra el1, myAlgebra el2)
{
    GF a, b, c, d;
    a = X1*Y1 + MU*X1*Y3 + X4*Y1 + LAMBDA*X4*Y3;
    b = LAMBDA*X2*Y2 + X2*Y4 + MU*X3*Y2 + X3*Y4;
    c = X2*Y1 + LAMBDA*X2*Y3 + X3*Y1 + MU*X3*Y3;
    d = MU*X1*Y2 + X1*Y4 + LAMBDA*X4*Y2 + X4*Y4;
    return myAlgebra(a, b, c, d);
}

bool operator==(myAlgebra el1, myAlgebra el2)
{
    if((el1.vec[0] == el2.vec[0])&&(el1.vec[1] == el2.vec[1])&&(el1.vec[2] == el2.vec[2])&&(el1.vec[3] == el2.vec[3]))
        return true;
    else
        return false;
}
