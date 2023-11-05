#include "BigReal.h"
#include <bits/stdc++.h>

//_____________(+ operator)________________
BigReal BigReal :: operator+(BigReal &l) {
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
        }
        int common = min(fraction.size() , l.fraction.size());
        for (int i = common-1; i >= 0; --i) {
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
        while (this->integer.size() < l.integer.size()){
            integer = '0' + l.integer;
        }

        while (l.integer.size() < this->integer.size()){
            l.integer = '0' + l.integer;
        }
        for (int i = integer.size()-1; i >= 0; --i) {
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
    return res;

}
//_______________(subtraction)_________________________
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

        // fraction_________________________________________
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
                    x = 0;
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
                }
                x = (f.integer[i] - '0') - (s.integer[i] - '0');
                borrow = 0;
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
        // fraction_________________________________________
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
                }
                x = (s.fraction[i] - '0') - (f.fraction[i] - '0');
                borrow = 0;
            }
            else {
                if(borrow){
                    x = ((s.fraction[i] - '0') + 9) - (f.fraction[i] - '0');
                }
                else {
                    x = 0;
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
                }
                x = (s.integer[i] - '0') - (f.integer[i] - '0');
                borrow = 0;
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

    return sub_res;
}
//_____________(- operator)________________
BigReal BigReal :: operator - (BigReal &k) {
    BigReal res;

    bool is_big = false;
    if (integer.size() > k.integer.size()){
        is_big = true;
    }
    else if (integer.size() == k.integer.size()){

        if(integer > k.integer){
            is_big = true;
        }
        else if (integer == k.integer) {

            if(fraction > k.fraction){
                is_big = true;
            }
            else if (fraction == k.fraction) {
                res.integer = '0';
                res.fraction = '0';
                res.sign = '+';
            }
        }
    }

    if (sign == k.sign){
        if(is_big){
            res.sign = sign;
        }
        else{
            res.sign= (sign == '+') ? '-' : '+';
        }

        if(is_big){
            while (fraction.size() < k.fraction.size()){
                fraction = fraction + '0';
            }
            while (fraction.size() > k.fraction.size()) {
                k.fraction = k.fraction + '0';
            }

            int borrow = 0;
            //fraction___________________________________________
            for (int i = fraction.size() - 1; i >= 0; --i) {
                int x;
                if (fraction[i] < k.fraction[i]) {
                    if (borrow) {
                        x = ((fraction[i] - '0') + 9) - (k.fraction[i] - '0');
                    }
                    else {
                        x = ((fraction[i] - '0') + 10) - (k.fraction[i] - '0');
                        borrow = 1;
                    }
                }
                else if (fraction[i] > k.fraction[i]) {
                    if(borrow) {
                        fraction[i] = char(fraction[i] - 1);
                    }
                    x = (k.fraction[i] - '0') - (k.fraction[i] - '0');
                    borrow = 0;
                }
                else {
                    if(borrow){
                        x = ((fraction[i] - '0') + 9) - (k.fraction[i] - '0');
                    }
                    else{
                        x = 0;
                    }
                }
                res.fraction.push_back(char('0' + x));
            }
            reverse(res.fraction.begin(), res.fraction.end());

            // Decimal________________________________________________
            if(borrow){
                int z = integer.size()-1;
                integer[z] = char(integer[z] - 1);
                borrow = 0;
            }
            while (integer.size() < k.integer.size()){
                integer = '0' + integer;
            }
            while (integer.size() > k.integer.size()){
                k.integer = '0' + k.integer;
            }

            for (int i = integer.size() - 1; i >= 0; --i) {
                int x;
                if (integer[i] < k.integer[i]) {
                    if (borrow) {
                        x = ((integer[i] - '0') + 9) - (k.integer[i] - '0');
                    }

                    else {
                        x = ((integer[i] - '0') + 10) - (k.integer[i] - '0');
                        borrow = 1;
                    }
                }

                else if (integer[i] > k.integer[i])  {
                    if(borrow) {
                        integer[i] = char(integer[i] - 1);
                    }
                    x = (integer[i] - '0') - (k.integer[i] - '0');
                    borrow = 0;
                }
                else {
                    if(borrow){
                        x = ((integer[i] - '0') + 9) - (k.integer[i] - '0');
                    }
                    else{
                        x = 0;
                    }
                }

                res.integer.push_back(char('0' + x));
            }

            reverse(res.integer.begin(), res.integer.end());

        }

        if(!is_big){
            while (k.fraction.size() < fraction.size()){
                k.fraction = k.fraction + '0';
            }
            while (k.fraction.size() > fraction.size()) {
                fraction = fraction + '0';
            }

            int borrow = 0;
            //fraction___________________________________________
            for (int i = fraction.size() - 1; i >= 0; --i) {
                int x;
                if (k.fraction[i] < fraction[i]) {
                    if (borrow) {
                        x = ((k.fraction[i] - '0') + 9) - (fraction[i] - '0');
                    }
                    else {
                        x = ((k.fraction[i] - '0') + 10) - (fraction[i] - '0');
                        borrow = 1;
                    }
                }
                else if (k.fraction[i] > fraction[i]) {
                    if(borrow) {
                        k.fraction[i] = char(k.fraction[i] - 1);
                    }
                    x = (k.fraction[i] - '0') - (fraction[i] - '0');
                    borrow = 0;
                }
                else {
                    if(borrow){
                        x = ((k.fraction[i] - '0') + 9) - (fraction[i] - '0');
                    }
                    else{
                        x = 0;
                    }
                }

                res.fraction.push_back(char('0' + x));
            }
            reverse(res.fraction.begin(), res.fraction.end());

            // Decimal________________________________________________
            if(borrow){
                int z = k.integer.size()-1;
                k.integer[z] = char(k.integer[z] - 1);
                borrow = 0;
            }
            while (k.integer.size() < integer.size()){
                k.integer = '0' + k.integer;
            }
            while (k.integer.size() > integer.size()){
                integer = '0' + integer;
            }

            for (int i = k.integer.size() - 1; i >= 0; --i) {
                int x;
                if (k.integer[i] < integer[i]) {
                    if (borrow) {
                        x = ((k.integer[i] - '0') + 9) - (integer[i] - '0');
                    }

                    else {
                        x = ((k.integer[i] - '0') + 10) - (integer[i] - '0');
                        borrow = 1;
                    }
                }

                else if (k.integer[i] > integer[i])  {
                    if(borrow) {
                        k.integer[i] = char(k.integer[i] - 1);
                    }
                    x = (k.integer[i] - '0') - (integer[i] - '0');
                    borrow = 0;
                }
                else {
                    if(borrow){
                        x = ((k.integer[i] - '0') + 9) - (integer[i] - '0');
                    }
                    else{
                        x = 0;
                    }
                }
                res.integer.push_back(char('0' + x));
            }
            reverse(res.integer.begin(), res.integer.end());
        }
    }

    else if (sign != k.sign)
    {
        res = addition(*this , k , is_big);
    }

    return res;
}

//_________________(addition)_________________________
BigReal BigReal :: addition(BigReal &f, BigReal s , bool big) {
    BigReal res_add;

    res_add.sign = f.sign;

    int carry = 0;
    // fraction_________________________________________
    if(f.fraction.size() < s.fraction.size())
    {
        res_add.fraction = s.fraction.substr(f.fraction.size() , s.fraction.size()-1);
        reverse(res_add.fraction.begin(), res_add.fraction.end());
    }

    else if(f.fraction.size() > s.fraction.size())
    {
        res_add.fraction = this->fraction.substr(s.fraction.size() , f.fraction.size()-1);
        reverse(res_add.fraction.begin(), res_add.fraction.end());
    }

    int common = min(f.fraction.size() , s.fraction.size());
    for (int i = common-1; i >= 0; --i) {
        int x = (f.fraction[i] - '0') + (s.fraction[i] - '0') + carry;

        if(x > 9){
            x -= 10;
            carry = 1;
        }
        else{
            carry = 0;
        }

        res_add.fraction.push_back(char('0' + x));
    }

    reverse(res_add.fraction.begin(), res_add.fraction.end());

    // Decimal________________________________________________
    while(f.integer.size() < s.integer.size())
    {
        f.integer = '0' + s.integer;
    }

    while (f.integer.size() > s.integer.size())
    {
        s.integer = '0' + s.integer;
    }

    for (int i = f.integer.size()-1; i >= 0; --i) {
        int x = (f.integer[i] - '0') + (s.integer[i] - '0') + carry;

        if(x > 9){
            x -= 10;
            carry = 1;
        }
        else{
            carry = 0;
        }

        res_add.integer.push_back(char('0' + x));
    }

    if(carry){
        res_add.integer.push_back(char('0' + carry));
    }
    reverse(res_add.integer.begin(), res_add.integer.end());

    return res_add;
}

//_____________(Assignment operator)________________
BigReal& BigReal :: operator = (const BigReal& a) {

    sign = a.sign;
    integer = a.integer;
    fraction = a.fraction;
    return *this; // Return a reference to the modified object
}
//_________________(copy constructor)________________
BigReal :: BigReal (const BigReal& other){
    this->fraction = other.fraction;
    this->sign = other.sign;
    this->integer = other.integer;
}
//----------------------------------
BigReal :: BigReal (string k) {
    int l=0;
    if(regex_match(k,regex("[+-]?\\d*.?\\d+"))){
        if(k[0]=='+'){
            sign='+';
            l=1;
        }
        else if(k[0]=='-') {
            sign='-';
            l=1;
        }
        integer=k.substr(l,k.find('.'));
        fraction=k.substr(integer.size()+1,k.size()-1);
    }
    if(integer==""){
        integer="0";
    }
    if(fraction==""){
        fraction="0";
    }
    if(integer!="0"){
        while(integer[zero]=='0'){
            zero++;
        }
        integer = integer.substr(zero, integer.size());
    }
}
//-------------------------------------
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

    return false;
}
//------------------------------------------
bool BigReal :: operator < (BigReal& W){
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
    return false;

}

//--------------------------------------------
bool BigReal:: operator == (BigReal& N){
    if(sign == N.sign && integer == N.integer && fraction == N.fraction){
        return true ;
    }
    return false;

}
//-------------------------------------------
ostream &operator << (ostream &out, const BigReal &big_real){
    out << big_real.sign<<big_real.integer <<'.'<<big_real.fraction;
    return out;
}
