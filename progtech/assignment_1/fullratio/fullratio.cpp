#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

int rational::gcd(int a, int b){
    while(a > 0 && b > 0){
        if(a >= b){
            a = a % b;
        }
        else if(b > a){
            b = b % a;
        }
    }
    return a + b;
}

rational::rational (int n, int d){
    if((n < 0 && d > 0) || (n > 0 && d < 0)){
        n = abs(n) * (-1);
        d = abs(d);
    }
    else if(n < 0 && d < 0){
        n = abs(n);
        d = abs(d);
    }
    else if(n == 0){
        d = 1;
    }


    int current_gcd = gcd(abs(n), abs(d));


    nom = n / current_gcd;
    den = d / current_gcd;
}

rational operator + (const rational &x, const rational &y) {
    int den_mult = x.den * y.den;
    int self_nom = den_mult / x.den * x.nom;
    int r_nom = den_mult / y.den * y.nom;


    int nom_return = self_nom + r_nom;
    int den_return = den_mult;

    return rational(nom_return, den_return);
}

rational operator - (const rational &x, const rational &y) {
    int den_mult = x.den * y.den;
    int self_nom = den_mult / x.den * x.nom;
    int r_nom = den_mult / y.den * y.nom;

    int nom_return = self_nom - r_nom;
    int den_return = den_mult;

    return rational(nom_return, den_return);
}

rational operator * (const rational &x, const rational &y) {
    int nom_return = x.nom * y.nom;
    int den_return = x.den * y.den;

    return rational(nom_return, den_return);
}

rational operator / (const rational &x, const rational &y) {
    int nom_return = x.nom * y.den;
    int den_return = x.den * y.nom;

    if((nom_return < 0 && den_return > 0) || (nom_return > 0 && den_return < 0)){
        nom_return = abs(nom_return) * (-1);
        den_return = abs(den_return);
    }
    else if(nom_return < 0 && den_return < 0){
        nom_return = abs(nom_return);
        den_return = abs(den_return);
    }
    else if(nom_return == 0){
        den_return = 1;
    }

    return rational(nom_return, den_return);
}

std::ostream & operator << (std::ostream &out, const rational &x){
    out << x.nom << "/" << x.den;
    return out;
}
