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
    BigReal addition (BigReal &f , BigReal s , bool this_is_bigger);
public:
    BigReal();
    BigReal (string k);
    BigReal (const BigReal& other);
    BigReal operator + (BigReal& l );
    BigReal operator - (BigReal& k) ;
    bool operator > (BigReal& o);
    bool operator < (BigReal& W);
    bool operator == (BigReal& N);
    friend ostream &operator << (ostream &out, const BigReal &big_real);
    BigReal operator >> (BigReal c);
    BigReal& operator = (const BigReal& a);

};

#endif //OOP_ASSIGNMENT2_BIGREAL_H
