#ifndef BIGNUM_H
#define BIGNUM_H

#include <iostream>

class Bignum{
    friend std::ostream& operator<<(std::ostream&, Bignum);
    friend std::istream& operator>>(std::istream&, Bignum&);

    friend Bignum operator+(const Bignum, const Bignum);
    friend Bignum operator-(const Bignum, const Bignum);
    friend Bignum operator*(const Bignum, const Bignum);
    friend Bignum operator/(const Bignum, const Bignum);
    friend Bignum operator%(const Bignum, const Bignum);

public:
    Bignum(const std::string V = "");
    Bignum(const long long);
    Bignum(const long);
    Bignum(const int);
    Bignum(const Bignum&);
    Bignum(const char*);

    void SetValue(const std::string);
    void SetValue(const long long);
    std::string GetValue() const;

    void SetPositive(const bool);
    bool isPositive() const;

    int size() const;

    int operator [](int index) const;
    Bignum operator-() const;

    bool operator ==(const Bignum) const;
    bool operator !=(const Bignum) const;
    bool operator  >(const Bignum) const;
    bool operator  <(const Bignum) const;
    bool operator >=(const Bignum) const;
    bool operator <=(const Bignum) const;

    Bignum Range(int, int) const;

    Bignum& operator+=(const Bignum);
    Bignum& operator-=(const Bignum);
    Bignum& operator*=(const Bignum);
    Bignum& operator/=(const Bignum);
    Bignum& operator%=(const Bignum);

    Bignum& operator++();
    Bignum  operator++(int i);
    Bignum& operator--();
    Bignum  operator--(int i);

    void Print();

    int Compare(const Bignum&) const;
    int CompareValue(const Bignum&) const;

private:
    std::string value;
    bool positive;
    int digits;
};


#include "Bignum.cpp"
#endif