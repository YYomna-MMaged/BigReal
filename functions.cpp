#include "BigReal.h"
#include <bits/stdc++.h>
//______________________________*Set operators*_______________________________
//______________(Default constructor)_____________________________
BigReal ::BigReal() {
    integer = "0";
    fraction = "0";
    sign = '+';
}
//_____________(Assignment operator)________________
BigReal& BigReal :: operator = (const BigReal& a) { // Assignment the valuse of the object in another object

    sign = a.sign;
    integer = a.integer;
    fraction = a.fraction;
    return *this; // Return a reference to the modified object
}
//_________________(copy constructor)________________
BigReal :: BigReal (const BigReal& other){ // Copy the valuse of the object in another object
    this->fraction = other.fraction;
    this->sign = other.sign;
    this->integer = other.integer;
}
//--------------------------------------------------
BigReal :: BigReal (string k) {
    int l = 0 , zero = 0;
    if(regex_match(k,regex("[+-]?\\d*.?\\d+"))){ //Use rexeg_mach to Mach what is pattern I need .
        if(k[0]=='+'){
            sign='+';
            l=1;
        }
        else if(k[0]=='-') {
            sign='-';
            l=1;
        }
        else {
            sign = '+';
        }
        integer=k.substr(l,k.find('.') - l);
        fraction=k.substr(integer.size()+1+l,k.size()-1);
    }
    //If it not valid make it =0,0
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
//-------------------------------------------
BigReal :: BigReal (double num) {
    string copy_num = to_string(num);

    int l = 0, zero = 0;
    if (regex_match(copy_num, regex("[+-]?\\d*.?\\d+"))) { //Use rexeg_mach to Mach what is pattern I need .
        if (copy_num[0] == '+') {
            sign = '+';
            l = 1;
        } else if (copy_num[0] == '-') {
            sign = '-';
            l = 1;
        }
        else {
            sign = '+';
        }
        integer = copy_num.substr(l, copy_num.find('.') - l);
        fraction = copy_num.substr(integer.size() + 1 + l, copy_num.size() - 1);
    }

    //If it not valid make it =0,0
    if (integer == "") {
        integer = "0";
    }
    if (fraction == "") {
        fraction = "0";
    }
    if (integer != "0") {
        while (integer[zero] == '0') {
            zero++;
        }
        integer = integer.substr(zero, integer.size());
    }
}


//_____________(+ operator)________________
BigReal BigReal :: operator+(BigReal &l) {
    BigReal res;

    if(this->sign == l.sign) { // if their signs are equal

        int carry = 0;
        res.sign = sign; //set sign

    // fraction_________________________________________
        //Deducting the largest part and adding it to the result
        if(this->fraction.size() < l.fraction.size()) {
            res.fraction = l.fraction.substr(this->fraction.size() , l.fraction.size()-1);
            reverse(res.fraction.begin(), res.fraction.end());
        }

        else if(this->fraction.size() > l.fraction.size()) {
            res.fraction = this->fraction.substr(l.fraction.size() , this->fraction.size()-1);
            reverse(res.fraction.begin(), res.fraction.end());
        }

        int common = min(fraction.size() , l.fraction.size()); // take the common length
        for (int i = common-1; i >= 0; --i) { // add fraction part and take care about carry
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

        //Integer________________________________________________
        //Make them the same length
        while (this->integer.size() < l.integer.size()){
            integer = '0' + integer;
        }

        while (l.integer.size() < this->integer.size()){
            l.integer = '0' + l.integer;
        }
        for (int i = integer.size()-1; i >= 0; --i) { // add integer part and take care about carry
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
        while (res.integer[res.integer.size()-1] == '0')
        {
            res.integer.pop_back();
        }

        reverse(integer.begin(), integer.end());
        reverse(l.integer.begin(), l.integer.end());
        while (integer[integer.size()-1] == '0')
        {
            integer.pop_back();
        }
        while (l.integer[l.integer.size()-1] == '0')
        {
            l.integer.pop_back();
        }
        reverse(integer.begin(), integer.end());
        reverse(l.integer.begin(), l.integer.end());
        return res;

    }
    else if(sign != l.sign){ // if their signs are not equal
        BigReal res = subtraction(*this , l);
        return res;
    }


}
//_______________(subtraction)_________________________
BigReal BigReal::subtraction(BigReal &f, BigReal s) {
    BigReal sub_res ;
    bool f_is_bigger = false;
    //Determine the largest number among them and set sign
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
    //Make them the same length
    while (f.fraction.size() < s.fraction.size()){
        f.fraction = f.fraction + '0';
    }
    while (f.fraction.size() > s.fraction.size()) {
        s.fraction = s.fraction + '0';
    }
    while (f.integer.size() < s.integer.size()){
        f.integer = '0' + f.integer;
    }
    while (f.integer.size() > s.integer.size()){
        s.integer = '0' + s.integer;
    }

    if (f_is_bigger) { //If the largest in the first number

        // fraction_________________________________________

        int borrow = 0;
        for (int i = f.fraction.size() - 1; i >= 0; --i) {// subtract fraction part and take care about borrow
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

        //Integer________________________________________________
        if(borrow){
            int z = f.integer.size()-1;
            f.integer[z] = char(f.integer[z] - 1);
            borrow = 0;
        }

        for (int i = f.integer.size() - 1; i >= 0; --i) { // subtract integer part and take care about borrow
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
        while (sub_res.integer[sub_res.integer.size()-1] == '0')
        {
            sub_res.integer.pop_back();
        }
    }

    else if(!f_is_bigger) { //If the largest isn't the first number

        int borrow = 0;
        // fraction_________________________________________
        for (int i = f.fraction.size() - 1; i >= 0; --i) { // subtract fraction part and take care about borrow
            int x;
            if (s.fraction[i] <  f.fraction[i]) {
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

        //Integer________________________________________________
        if(borrow){
            int z = s.integer.size()-1;
            s.integer[z] = char(s.integer[z] - 1);
            borrow = 0;
        }

        for (int i = f.integer.size() - 1; i >= 0; --i) { // subtract integer part and take care about borrow
            int x;
            if (s.integer[i] < f.integer[i]) {
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
        while (sub_res.integer[sub_res.integer.size()-1] == '0')
        {
            sub_res.integer.pop_back();
        }
    }
    reverse(f.integer.begin(), f.integer.end());
    reverse(s.integer.begin(), s.integer.end());
    reverse(f.fraction.begin(), f.fraction.end());
    reverse(s.fraction.begin(), s.fraction.end());

    while (f.integer[f.integer.size()-1] == '0')
    {
        f.integer.pop_back();
    }
    while (s.integer[s.integer.size()-1] == '0')
    {
        s.integer.pop_back();
    }
    while (f.fraction[f.fraction.size()-1] == '0')
    {
        f.fraction.pop_back();
    }while (s.fraction[s.fraction.size()-1] == '0')
    {
        s.fraction.pop_back();
    }
    reverse(f.integer.begin(), f.integer.end());
    reverse(s.integer.begin(), s.integer.end());
    reverse(f.fraction.begin(), f.fraction.end());
    reverse(s.fraction.begin(), s.fraction.end());
    return sub_res;
}
//_____________(- operator)________________
BigReal BigReal :: operator - (BigReal &k) {
    BigReal res;

    //Determine the largest number among them
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
            else if (fraction == k.fraction && sign != k.sign) { //If two numbers are the same was the same sign then the result will be zero
                res.integer = '0';
                res.fraction = '0';
                res.sign = '+';

                return res;
            }
        }
    }

    if (sign == k.sign){ //If they have the same sign

        while (fraction.size() < k.fraction.size()){
            fraction = fraction + '0';
        }
        while (fraction.size() > k.fraction.size()) {
            k.fraction = k.fraction + '0';
        }

        while (integer.size() < k.integer.size()){
            integer = '0' + integer;
        }
        while (integer.size() > k.integer.size()){
            k.integer = '0' + k.integer;
        }

        if(is_big){
            res.sign = sign; //the sign will take the sign of the first

            int borrow = 0;
            //fraction___________________________________________
            for (int i = fraction.size() - 1; i >= 0; --i) { //subtract fractions and take care of borrow
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

            //Integer________________________________________________
            if(borrow){
                int z = integer.size()-1;
                integer[z] = char(integer[z] - 1);
                borrow = 0;
            }

            for (int i = integer.size() - 1; i >= 0; --i) { //subtract integers and take care of borrow
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
            while (res.integer[res.integer.size()-1] == '0')
            {
                res.integer.pop_back();
            }
        }

        if(!is_big){ //If the largest isn't the first number

            res.sign= (sign == '+') ? '-' : '+'; //the sign will reverse the sign of the first number

            int borrow = 0;
            //fraction___________________________________________
            for (int i = fraction.size() - 1; i >= 0; --i) { //subtract the smaller from the larger fraction
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

            //Integer________________________________________________
            if(borrow){
                int z = k.integer.size()-1;
                k.integer[z] = char(k.integer[z] - 1);
                borrow = 0;
            }

            for (int i = k.integer.size() - 1; i >= 0; --i) { //subtract the smaller from the larger integer
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
            while (res.integer[res.integer.size()-1] == '0')
            {
                res.integer.pop_back();
            }
        }

        reverse(integer.begin(), integer.end());
        reverse(k.integer.begin(), k.integer.end());
        reverse(fraction.begin(), fraction.end());
        reverse(k.fraction.begin(), k.fraction.end());

        while (integer[integer.size()-1] == '0')
        {
            integer.pop_back();
        }
        while (k.integer[k.integer.size()-1] == '0')
        {
            k.integer.pop_back();
        }
        while (fraction[fraction.size()-1] == '0')
        {
            fraction.pop_back();
        }
        while (k.fraction[k.fraction.size()-1] == '0')
        {
            k.fraction.pop_back();
        }

        reverse(integer.begin(), integer.end());
        reverse(k.integer.begin(), k.integer.end());
        reverse(fraction.begin(), fraction.end());
        reverse(k.fraction.begin(), k.fraction.end());
        return res;
    }

    else if (sign != k.sign) { //If they haven't the same sign and different values
        res = addition(*this , k , is_big); // Call the addition function
        return res;
    }


}

//_________________(addition)_________________________
BigReal BigReal :: addition(BigReal &f, BigReal s , bool big) {
    BigReal res_add;

    res_add.sign = f.sign; //sige take the sign of the first number

//__________add fractions and integers similar to the (+) operator____________________
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

    //Integer________________________________________________
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
    while (res_add.integer[res_add.integer.size()-1] == '0')
    {
        res_add.integer.pop_back();
    }
    reverse(f.integer.begin(), f.integer.end());
    reverse(s.integer.begin(), s.integer.end());
    while (f.integer[f.integer.size()-1] == '0')
    {
        f.integer.pop_back();
    }
    while (s.integer[s.integer.size()-1] == '0')
    {
        s.integer.pop_back();
    }
    reverse(f.integer.begin(), f.integer.end());
    reverse(s.integer.begin(), s.integer.end());
    return res_add;
}

//_______________________________(Comparison operators)______________________________
//(>) operator-------------------------------------
bool BigReal:: operator > (BigReal& o){
    if ( sign == '+' && o.sign == '-'){ //If the sign of number + and the other is – then return true.
        return true;
    }
    //If the two signs are same and the size of integer part for number is greater/smaller then other and sign is + then return true.
    if (((sign == '-' && o.sign=='-')&& integer.size()<o.integer.size())||((sign=='+'&& o.sign=='+')&& integer.size()>o.integer.size())){
        return true;
    }

    else if (integer.size()==o.integer.size()){ //If the size of Integer part is equal
        if((integer> o.integer && o.sign=='+' )||(integer< o.integer && o.sign=='-')){ // compare the two integer and if integer is bigger and sign is positive or integer is small and sign is negative return true.
            return true;
        }

        if(integer==o.integer) { //If two integer part are equal compare fraction as integer.
            if((fraction > o.fraction && sign=='+' )||(fraction< o.fraction && o.sign=='-')){
                return true;
            }
        }

    }

    return false; //If not all those true return false.
}
//(<) operator------------------------------------------
bool BigReal :: operator < (BigReal& W){
    if ( sign == '-' && W.sign == '+'){ //If the sign of number - and the other is + then return true.
        return true;
    }
    //If the two signs are same and the size of integer part for number is smaller/greater then other and sign is + then return true .
    if (((sign =='-' && W.sign=='-')&& integer.size()>W.integer.size())||((sign=='+'&& W.sign=='+')&& integer.size()<W.integer.size())){
        return true;
    }

    else if (integer.size()==W.integer.size()){ //If the size of Integer part is equal
        if((integer < W.integer && W.sign=='+' )||(integer > W.integer && W.sign=='-')){ //compare the two integer and if integer is bigger and sign is negative or integer is small and sign is positive return true.
            return true;
        }

        if(integer==W.integer) { //If two integer part are equal compare fraction as integer.
            if((fraction < W.fraction && sign =='+' )||(fraction > W.fraction && W.sign=='-')){
                return true;
            }
        }

    }
    return false; //If not all those true return false.

}

//(==) operator--------------------------------------------
bool BigReal:: operator == (BigReal& N){
    if(sign == N.sign && integer == N.integer && fraction == N.fraction){ // check if two numbers are equal
        return true ;
    }
    return false;

}
//____(sign & size methods)_________

int BigReal :: size() { //total size
    return (this->integer.size() + this->fraction.size() + 2);
}

int BigReal :: the_sign() { //value of the sign
    return (sign == '+') ? 1 : 0;
}
// Cout-------------------------------------------
ostream &operator << (ostream &out, const BigReal &big_real){ // Display values
    out << big_real.sign<<big_real.integer <<'.'<<big_real.fraction;
    return out;
}

