#include "BigReal.h"
#include <bits/stdc++.h>
BigReal BigReal :: operator+(BigReal &l) {
//    char f_sign;
    BigReal res;

    if(this->sign == l.sign) {

        int carry = 0;
        res.sign = sign;

    // fraction_________________________________________
        if(this->fraction.size() < l.fraction.size())
        {
            res.fraction = l.fraction.substr(this->fraction.size() , l.fraction.size()-1);
            reverse(res.fraction.begin(), res.fraction.end());
        }

        else if(this->fraction.size() > l.fraction.size())
        {
            res.fraction = this->fraction.substr(l.fraction.size() , this->fraction.size()-1);
            reverse(res.fraction.begin(), res.fraction.end());
//            for (int i = 0; i < (this->fraction.size() - l.fraction.size()); ++i) {
//                l.fraction.push_back('0');
//            }
        }

        int common = min(fraction.size() , l.fraction.size());
        for (int i = common-1; i <= 0; --i) {
            int x = (this->fraction[i] - '0') + (l.fraction[i] - '0') + carry;

            if(x > 9){
                x -= 10;
                carry = 1;
            }
            else{
                carry = 0;
            }

            res.fraction.push_back(char('0' + x));
        }

        reverse(res.fraction.begin(), res.fraction.end());

    // Decimal________________________________________________
        if(this->integer.size() < l.integer.size())
        {
            reverse(integer.begin(), integer.end());

            int i2 = l.integer.size() - integer.size();
            for (int i = 0; i < i2; ++i) {
                this->integer.push_back('0');
            }
            reverse(integer.begin(), integer.end());
//            res.integer = l.integer.substr(this->integer.size() , l.integer.size()-1);
//            reverse(res.fraction.begin(), res.fraction.end());
        }

        else if(this->integer.size() > l.integer.size())
        {
//            res.fraction = this->fraction.substr(l.fraction.size() , this->fraction.size()-1);
//            reverse(res.fraction.begin(), res.fraction.end());
            reverse(l.integer.begin(), l.integer.end());
            int i1 = integer.size() - l.integer.size();

            for (int i = 0; i < i1; ++i) {
                l.fraction.push_back('0');
            }
            reverse(l.integer.begin(), l.integer.end());
        }

//        int common = min(fraction.size() , l.fraction.size());
        for (int i = integer.size()-1; i <= 0; --i) {
            int x = (this->integer[i] - '0') + (l.integer[i] - '0') + carry;

            if(x > 9){
                x -= 10;
                carry = 1;
            }
            else{
                carry = 0;
            }

            res.integer.push_back(char('0' + x));
        }

        if(carry){
            res.integer.push_back(char('0' + carry));
        }
        reverse(res.integer.begin(), res.integer.end());
    }

    else if(sign != l.sign){
        BigReal res = subtraction(*this , l);
    }

}

BigReal BigReal::subtraction(BigReal &f, BigReal s) {
    BigReal sub_res ;
    bool f_is_bigger = false;

    if(f.integer.size() > s.integer.size()){
        sub_res.sign = f.sign;
        f_is_bigger = true;
    }

    else if(f.integer.size() < s.integer.size()){
        sub_res.sign = s.sign;
    }

    else{
        if(f.integer > s.integer){
            sub_res.sign = f.sign;
            f_is_bigger = true;
        }

        else if(f.integer < s.integer){
            sub_res.sign = s.sign;
        }

        else {
            if(f.fraction > s.fraction){
                sub_res.sign = f.sign;
                f_is_bigger = true;
            }

            else if(f.fraction < s.fraction){
                sub_res.sign = s.sign;
            }

            else
            {
                sub_res.fraction = '0';
                sub_res.integer = '0';
                sub_res.sign = '+';

                return sub_res;
            }
        }
    }

    if (f_is_bigger) {

        while (f.fraction.size() < s.fraction.size()){
            f.fraction = f.fraction + '0';
        }
        while (f.fraction.size() > s.fraction.size()) {
            s.fraction = s.fraction + '0';
        }

        int borrow = 0;
        for (int i = f.fraction.size() - 1; i >= 0; --i) {
            int x;
            if (f.fraction[i] < s.fraction[i]) {
                if (borrow) {
                    x = ((f.fraction[i] - '0') + 9) - (s.fraction[i] - '0');
                }
                else {
                    x = ((f.fraction[i] - '0') + 10) - (s.fraction[i] - '0');
                    borrow = 1;
                }
            }
            else if (f.fraction[i] > s.fraction[i]) {
                if(borrow){
                    f.fraction[i] = char(f.fraction[i] - 1);
                    x = (s.fraction[i] - '0') - (s.fraction[i] - '0');
                    borrow = 0;
                }
                else{
                    x = (f.fraction[i] - '0') - (s.fraction[i] - '0');
                }
            }
            else {
                if(borrow){
                    x = ((f.fraction[i] - '0') + 9) - (s.fraction[i] - '0');
                }
                else{
                    x = (f.fraction[i] - '0') - (s.fraction[i] - '0');
                }
            }

            sub_res.fraction.push_back(char('0' + x));
        }
        reverse(sub_res.fraction.begin(), sub_res.fraction.end());

        // Decimal________________________________________________
        if(borrow){
            int z = f.integer.size()-1;
            f.integer[z] = char(f.integer[z] - 1);
            borrow = 0;
        }
        while (f.integer.size() < s.integer.size()){
            f.integer = '0' + f.integer;
        }
        while (f.integer.size() > s.integer.size()){
            s.integer = '0' + s.integer;
        }

        for (int i = f.integer.size() - 1; i >= 0; --i) {
            int x;
            if (f.integer[i] < s.integer[i]) {
                if (borrow) {
                    x = ((f.integer[i] - '0') + 9) - (s.integer[i] - '0');
                }

                else {
                    x = ((f.integer[i] - '0') + 10) - (s.integer[i] - '0');
                    borrow = 1;
                }
            }

            else if (f.integer[i] > s.integer[i])  {
                if(borrow){
                    f.integer[i] = char(f.integer[i] - 1);
                    x = (f.integer[i] - '0') - (s.integer[i] - '0');
                    borrow = 0;
                }
                else{
                    x = (f.integer[i] - '0') - (s.integer[i] - '0');
                }
            }
            else {
                if(borrow){
                    x = ((f.integer[i] - '0') + 9) - (s.integer[i] - '0');
                }
                else{
                    x = 0;
                }
            }

            sub_res.integer.push_back(char('0' + x));
        }

        reverse(sub_res.integer.begin(), sub_res.integer.end());

    }

    else if(!f_is_bigger) {

        while (f.fraction.size() < s.fraction.size()){
            f.fraction = f.fraction + '0';
        }

        while (f.fraction.size() > s.fraction.size()){
            s.fraction = s.fraction + '0';
        }

        int borrow = 0;
        for (int i = f.fraction.size() - 1; i >= 0; --i) {
            int x;
            if (f.fraction[i] < s.fraction[i]) {
                if (borrow) {
                    x = ((s.fraction[i] - '0') + 9) - (f.fraction[i] - '0');
                }
                else {
                    x = ((s.fraction[i] - '0') + 10) - (f.fraction[i] - '0');
                    borrow = 1;
                }
            }
            else if (s.fraction[i] > f.fraction[i]){
                if(borrow){
                    s.fraction[i] = char(s.fraction[i] - 1);
                    x = (s.fraction[i] - '0') - (f.fraction[i] - '0');
                    borrow = 0;
                }
                else{
                    x = (s.fraction[i] - '0') - (f.fraction[i] - '0');
                }
            }
            else {
                if(borrow){
                    x = ((s.fraction[i] - '0') + 9) - (f.fraction[i] - '0');
                }
                else {
                    x = (s.fraction[i] - '0') - (f.fraction[i] - '0');
                }
            }

            sub_res.fraction.push_back(char('0' + x));
        }

        reverse(sub_res.fraction.begin(), sub_res.fraction.end());

        // Decimal________________________________________________
        if(borrow){
            int z = s.integer.size()-1;
            s.integer[z] = char(s.integer[z] - 1);
            borrow = 0;
        }
        while (f.integer.size() < s.integer.size()) {
            f.integer = '0' + f.integer;
        }

        while (s.integer.size() < f.integer.size()) {
            s.integer = '0' + s.integer;
        }

        for (int i = f.integer.size() - 1; i <= 0; --i) {
            int x;
            if (f.integer[i] < s.integer[i]) {
                if (borrow) {
                    x = ((s.integer[i] - '0') + 9) - (f.integer[i] - '0');
                }

                else {
                    x = ((s.integer[i] - '0') + 10) - (f.integer[i] - '0');
                    borrow = 1;
                }
            }

            else if (s.integer[i] > f.integer[i]) {
                if(borrow){
                    s.integer[i] = char(s.integer[i] - 1);
                    x = (s.integer[i] - '0') - (f.integer[i] - '0');
                    borrow = 0;
                }
                else{
                    x = (s.integer[i] - '0') - (f.integer[i] - '0');
                }
            }
            else {
                if(borrow){
                    x = ((s.integer[i] - '0') + 9) - (f.integer[i] - '0');
                }
                else
                {
                    x = 0;
                }
            }


            sub_res.integer.push_back(char('0' + x));
        }

        reverse(sub_res.integer.begin(), sub_res.integer.end());

    }
}