#include <iostream>
using namespace std;
class BigReal {
     string real_number;
     char sign ;
     string fraction , integer ;
public:
    BigReal (string k);
    BigReal operator + (string l );
    BigReal operator - (string k) ;
    BigReal operator > (string o);
    BigReal operator < (string W);
    BigReal operator == (string N);
    BigReal operator << (string j);
    BigReal operator >> (string c);
    BigReal operator = (string a);

};
int main() {

    return 0;
}
