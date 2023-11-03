#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class BigReal {
     string real_number;
     char sign='+' ;
     string fraction , integer;
    BigReal subtraction (BigReal &f , BigReal s);
public:

//    BigReal();
//    BigReal (string k);
    BigReal operator + (BigReal &l);
//    BigReal operator - (string k) ;
    bool operator > (BigReal& o);
    bool operator < (BigReal& W);
//    bool operator == (BigReal& N);
//    BigReal operator << (string j);
//    BigReal operator >> (string c);
//    BigReal operator = (string a);

};
//------------------------------------------------
bool BigReal:: operator > (BigReal& o){
    if ( sign == '+' && o.sign == '-'){
        return true;
    }
    if (((sign == '-' && o.sign=='-')&& integer.size()<o.integer.size())||((sign=='+'&& o.sign=='+')&& integer.size()>o.integer.size())){
        return true;
    }

    else if (integer.size()==o.integer.size()){
        if((integer> o.integer && o.sign=='+' )||(integer< o.integer && o.sign=='-')){
            return true;
        }

        if(integer==o.integer) {
            if((fraction > o.fraction && sign=='+' )||(fraction< o.fraction && o.sign=='-')){
                return true;
            }
        }

    }
    else {
        return false;
    }
}
//------------------------------------------
bool BigReal:: operator < (BigReal& W){
    if ( sign == '-' && W.sign == '+'){
        return true;
    }
    if (((sign =='-' && W.sign=='-')&& integer.size()>W.integer.size())||((sign=='+'&& W.sign=='+')&& integer.size()<W.integer.size())){
        return true;
    }

    else if (integer.size()==W.integer.size()){
        if((integer < W.integer && W.sign=='+' )||(integer > W.integer && W.sign=='-')){
            return true;
        }

        if(integer==W.integer) {
            if((fraction < W.fraction && sign =='+' )||(fraction > W.fraction && W.sign=='-')){
                return true;
            }
        }

    }
    else {
        return false;
    }
}
//------------------------------------------
//BigReal BigReal :: operator + (BigReal &l) {
////    char f_sign;
//    BigReal res;
//
//    if(this->sign == l.sign) {
//
//        int carry = 0;
//        res.sign = sign;
//
//        // fraction_________________________________________
//        if(this->fraction.size() < l.fraction.size())
//        {
//            res.fraction = l.fraction.substr(this->fraction.size() , l.fraction.size()-1);
//            reverse(res.fraction.begin(), res.fraction.end());
//        }
//
//        else if(this->fraction.size() > l.fraction.size())
//        {
//            res.fraction = this->fraction.substr(l.fraction.size() , this->fraction.size()-1);
//            reverse(res.fraction.begin(), res.fraction.end());
////            for (int i = 0; i < (this->fraction.size() - l.fraction.size()); ++i) {
////                l.fraction.push_back('0');
////            }
//        }
//
//        int common = min(fraction.size() , l.fraction.size());
//        for (int i = common-1; i <= 0; --i) {
//            int x = (this->fraction[i] - '0') + (l.fraction[i] - '0') + carry;
//
//            if(x > 9){
//                x -= 10;
//                carry = 1;
//            }
//            else{
//                carry = 0;
//            }
//
//            res.fraction.push_back(char('0' + x));
//        }
//
//        reverse(res.fraction.begin(), res.fraction.end());
//
//        // Decimal________________________________________________
//        if(this->integer.size() < l.integer.size())
//        {
//            reverse(integer.begin(), integer.end());
//
//            int i2 = l.integer.size() - integer.size();
//            for (int i = 0; i < i2; ++i) {
//                this->integer.push_back('0');
//            }
//            reverse(integer.begin(), integer.end());
////            res.integer = l.integer.substr(this->integer.size() , l.integer.size()-1);
////            reverse(res.fraction.begin(), res.fraction.end());
//        }
//
//        else if(this->integer.size() > l.integer.size())
//        {
////            res.fraction = this->fraction.substr(l.fraction.size() , this->fraction.size()-1);
////            reverse(res.fraction.begin(), res.fraction.end());
//            reverse(l.integer.begin(), l.integer.end());
//            int i1 = integer.size() - l.integer.size();
//
//            for (int i = 0; i < i1; ++i) {
//                l.fraction.push_back('0');
//            }
//            reverse(l.integer.begin(), l.integer.end());
//        }
//
////        int common = min(fraction.size() , l.fraction.size());
//        for (int i = integer.size()-1; i <= 0; --i) {
//            int x = (this->integer[i] - '0') + (l.integer[i] - '0') + carry;
//
//            if(x > 9){
//                x -= 10;
//                carry = 1;
//            }
//            else{
//                carry = 0;
//            }
//
//            res.integer.push_back(char('0' + x));
//        }
//
//        if(carry){
//            res.integer.push_back(char('0' + carry));
//        }
//        reverse(res.integer.begin(), res.integer.end());
//    }
//
//    else if(sign != l.sign){
//        BigReal res = subtraction(*this , l);
//    }
//
//}
int main() {

    return 0;
}
