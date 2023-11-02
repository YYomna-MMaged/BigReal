//
// Created by COMPU LAND on 11/2/2023.
//

#ifndef OOP_ASSIGNMENT2_BIGREAL_H
#define OOP_ASSIGNMENT2_BIGREAL_H
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class BigReal {
    string real_number;
    char sign ;
    string fraction , integer ;
    BigReal subtraction (BigReal &f , BigReal s);
public:
    BigReal();
    BigReal (string k);
    BigReal operator + (BigReal &l );
    BigReal operator - (string k) ;
    BigReal operator > (string o);
    BigReal operator < (string W);
    BigReal operator == (string N);
    BigReal operator << (string j);
    BigReal operator >> (string c);
    BigReal operator = (string a);

};

#endif //OOP_ASSIGNMENT2_BIGREAL_H
