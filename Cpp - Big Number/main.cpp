#include "Bignum.cpp"
#include <iostream>
#include <iomanip>

using namespace std;

string is(bool b){
    //It's just a function to cout ("True" or "False") instead of (1 or 0)
    if(b)
        return "True";
    return "False";
}

int main(){
    // Setting values
    Bignum a, b;
    long long lli;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "long long int: ";
    cin >> lli;
    cout << endl;

    // Prints with "," every three digits
    cout << "a: ";
    a.Print();
    cout << "b: ";
    b.Print();
    cout << endl;

    // Comparison with (long long)
    cout << "a == " << lli << ": " << is(a == lli) << endl;
    cout << " a < " << lli << ": " << is(a < lli) << endl;
    cout << " a > " << lli << ": " << is(a > lli) << endl;
    cout << endl;

    // Operators with (long long)
    cout << "a + "<< lli <<": " << a + lli << endl; 
    cout << "a - "<< lli <<": " << a - lli << endl; 
    cout << "a * "<< lli <<": " << a * lli << endl;
    cout << endl;

    // Comparison with another Bignum
    cout << "a == b: " << is(a == b) << endl;
    cout << " a > b: " << is(a > b) << endl;
    cout << " a < b: " << is(a < b) << endl;
    cout << "a >= b: " << is(a >= b) << endl;
    cout << "a <= b: " << is(a <= b) << endl;
    cout << endl;

    // Operators with other Bignums
    cout << "a + b: " << a + b << endl;
    cout << "a - b: " << a - b << endl;
    cout << "b - a: " << b - a << endl;
    cout << "a * b: " << a * b << endl;
    cout << "a / b: " << a / b << endl;
    cout << "a % b: " << a % b << endl;
    cout << endl;

    // Post-fix and Pre-fix operators
    cout << "a++: " << a++ << endl;
    cout << "++a: " << ++a << endl;
    cout << "b--: " << b-- << endl;
    cout << "--b: " << --b << endl;
    cout << endl;

    // Support for converting between (long long), (long), (int), (Bignum) 
    cout << "(Bigint) += (Bigint)" << endl;
    a += b;
    cout << "a: " << a << endl;

    cout << "(Bigint) -= (long long)" << endl;
    b -= lli;
    cout << "b: " << b << endl;

    cout << "(long long) *= (Bigint)" << endl;
    try{
        lli *= a;
        cout << "lli: " << lli << endl;
    }catch(overflow_error& e){
        cout << e.what() << endl;
    }
    cout << endl;

    return 0;
}