#ifndef CONTEST
#include "babyratio.hpp"
#endif

#include <iostream>
#include <stdlib.h>

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

rational rational::add (rational r) {

    int den_mult = den * r.den;
    int self_nom = den_mult / den * nom;
    int r_nom = den_mult / r.den * r.nom;


    int nom_return = self_nom + r_nom;
    int den_return = den_mult;

    return rational(nom_return, den_return);
}

rational rational::sub (rational r) {
    int den_mult = den * r.den;
    int self_nom = den_mult / den * nom;
    int r_nom = den_mult / r.den * r.nom;

    int nom_return = self_nom - r_nom;
    int den_return = den_mult;

    return rational(nom_return, den_return);
}

rational rational::mul (rational r) {
    int nom_return = nom * r.nom;
    int den_return = den * r.den;

    return rational(nom_return, den_return);
}

rational rational::div (rational r) {
    int nom_return = nom * r.den;
    int den_return = den * r.nom;

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

void rational::print(){
    cout << nom << "/" << den;
}
