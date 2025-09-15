#ifndef BIGNUM_CPP
#define BIGNUM_CPP

#include "Bignum.h"
#include <iostream>
#include <string>
#include <climits>

using namespace std;

//------------------------- Neccessery Functions ---------------------------
int max(int, int);
string strReverse(string);
Bignum abs(const Bignum);
string RemoveJunks(string);
Bignum AddBignums(const Bignum, const Bignum);
Bignum SubBignums(const Bignum, const Bignum);
Bignum MultiplyWithInt(const long long, const Bignum);
Bignum Devide(const Bignum, const Bignum, bool returnRemains = false);

//------------------------------ Constructors ------------------------------
Bignum::Bignum(const std::string V){
    SetValue(V);
}

Bignum::Bignum(const long long V){
    SetValue(V);
}

Bignum::Bignum(const long l){
    SetValue(l);
}

Bignum::Bignum(const int i){
    SetValue(i);
}

Bignum::Bignum(const Bignum& B){
    SetValue(B.GetValue());
    SetPositive(B.isPositive());
}

Bignum::Bignum(const char* c){
    SetValue(static_cast<string>(c));
}

//----------------------------- Setters and Getters ------------------------
void Bignum::SetValue(const string V){
    if(V[0] == '+' || V[0] == '-')
        SetPositive(V[0] == '+');
    else
        SetPositive(true);

    value = RemoveJunks(V);
    digits = value.size();
}

void Bignum::SetValue(const long long V){
    value = to_string(V);
    SetPositive(V >= 0);
    digits = value.size();
}

std::string Bignum::GetValue() const{
    return value;
}

bool Bignum::isPositive() const{
    return positive;
}

void Bignum::SetPositive(const bool p){
    positive = p;
}

int Bignum::size() const{
    return digits;
}

//-------------------------------- Operators -------------------------------
ostream& operator<<(ostream& os, Bignum B){
    if(!B.isPositive() && B.GetValue() != "0") // not cout "-0"
        os << "-";
    os << B.GetValue();
    return os;
}

istream& operator>>(istream& is, Bignum& B){
    string value;
    is >> value;
    B.SetValue(value);
    return is;
}

int Bignum::operator [](int index) const{
    if(index < 0)
        return 0; // There are infinite zeros before a number
    if(index > size())
        throw invalid_argument("out of range.");
    return GetValue().at(index) - '0';
}

Bignum Bignum::operator-() const{
    Bignum temp = *this;
    temp.SetPositive(!this->isPositive());
    return temp;
}

bool Bignum::operator ==(const Bignum other) const{
    return Compare(other) == 0;
}

bool Bignum::operator !=(const Bignum other) const{
    return Compare(other) != 0;
}

bool Bignum::operator >(const Bignum other) const{
    return Compare(other) == -1;
}

bool Bignum::operator <(const Bignum other) const{
    return Compare(other) == 1;
}

bool Bignum::operator >=(const Bignum other) const{
    int comp_result = Compare(other);
    if(comp_result == -1 || comp_result == 0)
        return true;
    return false;
}

bool Bignum::operator <=(const Bignum other) const{
    int comp_result = Compare(other);
    if(comp_result == 1 || comp_result == 0)
        return true;
    return false;
}

Bignum operator+(const Bignum a, const Bignum b){
    Bignum res;
    if(a.isPositive() == b.isPositive()){
        res = AddBignums(a,b);
        res.SetPositive(a.isPositive()); // or b.is_positive() doesn't matter
        return res;
    
    }else if(abs(a) == abs(b)){
        return 0;

    }else if(abs(a) > abs(b)){
        res = SubBignums(a,b);
        res.SetPositive(a.isPositive());
        return res;
    
    }else{
        res = SubBignums(b,a);
        res.SetPositive(b.isPositive());
        return res;
    }
}

Bignum operator-(const Bignum a, const Bignum b){
    Bignum new_b = Bignum(b);
    new_b.SetPositive(!new_b.isPositive());
    return a + new_b;
}

Bignum operator*(const Bignum a, const Bignum b){
    string res = "";
    Bignum remains = 0;
    for(int i = 0; i < a.size() + b.size(); i++){
        Bignum sum = MultiplyWithInt(a[a.size() - i - 1], b) + remains;
        res += to_string(sum[sum.size() - 1]);
        remains = sum.Range(0, sum.size() - 2);// equilivent to : remains = sum / 10
    }
    Bignum result = Bignum(strReverse(res));
    result.SetPositive(a.isPositive() == b.isPositive());
    return result;
}

Bignum operator/(const Bignum a, const Bignum b){
    return Devide(a,b);
}

Bignum operator%(const Bignum a, const Bignum b){
    return Devide(a,b, true);
}

Bignum& Bignum::operator+=(const Bignum other){
    *this = *this + other;
    return *this;
}

Bignum& Bignum::operator-=(const Bignum other){
    *this = *this - other;
    return *this;
}

Bignum& Bignum::operator*=(const Bignum other){
    *this = *this * other;
    return *this;
}

Bignum& Bignum::operator/=(const Bignum other){
    *this = *this / other;
    return *this;
}

Bignum& Bignum::operator%=(const Bignum other){
    *this = *this % other;
    return *this;
}

Bignum& Bignum::operator++(){
    *this += 1;
    return *this;
}
Bignum Bignum::operator++(int i){
    Bignum temp = *this;
    *this += 1;
    return temp;
}

Bignum& Bignum::operator--(){
    *this -= 1;
    return *this;
}
Bignum Bignum::operator--(int i){
    Bignum temp = *this;
    *this -= 1;
    return temp;
}

//---------------------------- Extra Functions ----------------------------
int max(int a, int b){
    // Return bigger number between two
    if(a > b)
        return a;
    return b;
}

string strReverse(string str){
    // reverses a string
    string res = "";
    for(int i = str.size() - 1; i >= 0; i--)
        res += str[i];
    return res;
}

Bignum abs(const Bignum B){
    // returns the absolute value of a Bignum( |Bignum| )
    Bignum res(B);
    res.SetPositive(true);
    return res;
}

string RemoveJunks(string number){
    // removes + or - before number
    // removes zeros before number
    // removes numbers after . (123.12 = 123)

    string result = "";
    bool reachedNums = false;
    for(int i = 0; i < number.size(); i++){
        if(number[i] == '.')
            break;
        if('0' <= number[i] && number[i] <= '9'){
            if(reachedNums)
                result += number[i];
            else if(number[i] != '0'){
                result += number[i];
                reachedNums = true;
            }
        }
    }

    if(result == "")
        return "0";
    return result;
}

Bignum Bignum::Range(int a, int b) const{
    // returns range of number from two index (like sub_str())
    string res = "";
    for(int i = a; i <= b; i++)
        res += to_string((*this)[i]);
    return res;
}

int Bignum::CompareValue(const Bignum& other) const{
    // Compares the absolute value of two Bignums
    // -1 means left side is bigger
    //  0 means they are equel
    //  1 means right side is bigger
    // ( like str_compare() )

    if(size() > other.size())
        return -1;
    else if(size() < other.size())
        return 1;

    for(int i = 0; i < size(); i++){
        if((*this)[i] > other[i])
            return -1;
        else if((*this)[i] < other[i])
            return 1;
    }
    return 0;
}

int Bignum::Compare(const Bignum& other) const{
    // Compares two Bignums
    // -1 means left side is bigger
    //  0 means they are equel
    //  1 means right side is bigger
    // ( like str_compare() )

    if(isPositive() == other.isPositive()){
        int comp_result = CompareValue(other);
        if(isPositive())
            return comp_result;
        else
            return -comp_result;

    }else if(isPositive()){
        return -1;
    }else{
        return 1;
    }    
}

Bignum AddBignums(const Bignum a, const Bignum b){
    // Adds two positive Bignums
    string result = "";
    int remains = 0;
    for(int i = 0; i < max(a.size(), b.size()) + 1; i++){
        int sum = a[a.size()-i -1] + b[b.size()-i -1] + remains;
        result += to_string((sum % 10));
        remains = sum/10;
    }
    return Bignum(strReverse(result));
}

Bignum SubBignums(const Bignum a, const Bignum b){
    // Subtracts a positive Bignum from another positive Bignum
    string result = "";
    int remains = 0;
    for(int i = 0; i < max(a.size(), b.size()) + 1; i++){
        int sum = a[a.size()-i -1] - b[b.size()-i -1] + remains;
        remains = 0;
        if(sum < 0){
            sum += 10;
            remains = -1;
        }
        result += to_string((sum % 10));
    }
    return Bignum(strReverse(result));
}

Bignum MultiplyWithInt(const long long a, const Bignum b){
    // Multyplys a Bignum with an long long
    string res = "";
    long long remains = 0;
    for(int i = 0; i < b.size() + 1; i++){
        long long sum = a * b[b.size()-i -1] + remains;
        res += to_string(sum % 10);
        remains = sum / 10;
    }
    return Bignum(strReverse(res));
}

Bignum Devide(const Bignum a, const Bignum b, bool returnRemains){
    // devides a from b
    // returns a/b or a%b according to the boolean "returnRemains"

    if(b == 0)
        throw invalid_argument("The second arguement of / can't be 0");

    bool pos = a.isPositive() == b.isPositive();
    Bignum absA = abs(a);
    Bignum absB = abs(b);

    if(absB == 1){
        if(returnRemains)
            return 0; // x%1 = 0
        if(b.isPositive())
            return a; // x/1 = x
        return -a;    // x/-1 = -x
    }

    if(absA < absB){
        if(returnRemains)
            return a; // 3%5 = 3
        return 0;     // 3/5 = 0
    }

    string res = "0";
    int i, q;
    Bignum seperated("0");
    for(i = 0; seperated < absB; i++)
        seperated = a.Range(0,i);

    Bignum remains;
    for(i--; i < a.size(); i++){
        remains = seperated;
        for(q = 1; remains >= absB; q++)
            remains = seperated - (q * absB);
        
        res += to_string(q-1);
        seperated = remains.GetValue() + to_string(a[i]);
    }

    Bignum result = res;
    result.SetPositive(pos);
    remains.SetPositive(a.isPositive());

    if(returnRemains)
        return remains;
    return result;
}

void Bignum::Print(){
    // Prints the number with "," every three digits from the right
    int firstFewDigits = size() % 3;

    for(int i = 0; i < firstFewDigits; i++)
        cout << (*this)[i];    
    
    for(int i = 0; i < size() / 3; i++){
        int i0 = i*3 + firstFewDigits;

        if(i || firstFewDigits)
            cout.put(',');

        cout << (*this)[i0] << (*this)[i0 + 1] << (*this)[i0 + 2];   
    }
    cout << endl;
}


//--------------------------------------------------------------------------
// Support for 
// int += Bigint and other functions like that

bool CheckLongLong(Bignum b){
    if(b > LLONG_MAX)
        throw overflow_error("Over the limit of long long int.");
    return true;
}
bool CheckLong(Bignum b){
    if(b > LONG_MAX)
        throw overflow_error("Over the limit of long int.");
    return true;
}
bool CheckInt(Bignum b){
    if(b > INT_MAX)
        throw overflow_error("Over the limit of int.");
    return true;
}

//..................... += .......................
long long& operator +=(long long& i, Bignum b){
    if(CheckLongLong(b + i)){
        i += stoi(b.GetValue());
        return i;
    }
}

long& operator +=(long& i, Bignum b){
    if(CheckLong(b + i)){
        i += stoi(b.GetValue());
        return i;
    }
}

int& operator +=(int& i, Bignum b){
    if(CheckInt(b + i)){
        i += stoi(b.GetValue());
        return i;
    }
}

//..................... -= .......................
long long& operator -=(long long& i, Bignum b){
    if(CheckLongLong(i - b)){
        i -= stoi(b.GetValue());
        return i;
    }
}

long& operator -=(long& i, Bignum b){
    if(CheckLong(i - b)){
        i -= stoi(b.GetValue());
        return i;
    }
}

int& operator -=(int& i, Bignum b){
    if(CheckInt(i - b)){
        i -= stoi(b.GetValue());
        return i;
    }
}

//..................... *= .......................
long long& operator *=(long long& i, Bignum b){
    if(CheckLongLong(b * i)){
        i *= stoi(b.GetValue());
        return i;
    }
}

long& operator *=(long& i, Bignum b){
    if(CheckLong(b * i)){
        i *= stoi(b.GetValue());
        return i;
    }
}

int& operator *=(int& i, Bignum b){
    if(CheckInt(b * i)){
        i *= stoi(b.GetValue());
        return i;
    }
}

//..................... /= .......................
long long& operator /=(long long& i, Bignum b){
    if(CheckLongLong(i / b)){
        i /= stoi(b.GetValue());
        return i;
    }
}

long& operator /=(long& i, Bignum b){
    if(CheckLong(i / b)){
        i /= stoi(b.GetValue());
        return i;
    }
}

int& operator /=(int& i, Bignum b){
    if(CheckInt(i / b)){
        i /= stoi(b.GetValue());
        return i;
    }
}

//..................... %= .......................
long long& operator %=(long long& i, Bignum b){
    if(CheckLongLong(i % b)){
        i %= stoi(b.GetValue());
        return i;
    }
}

long& operator %=(long& i, Bignum b){
    if(CheckLong(i % b)){
        i %= stoi(b.GetValue());
        return i;
    }
}

int& operator %=(int& i, Bignum b){
    if(CheckInt(i % b)){
        i %= stoi(b.GetValue());
        return i;
    }
}

#endif