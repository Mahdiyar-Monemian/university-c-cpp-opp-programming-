#ifndef RECEIPT_H
#define RECEIPT_H

#include <iostream>
#include <utility>
#include <list>
#include <tuple>
#include "Date.cpp"

using namespace std;

class Receipt{
    friend ostream& operator<<(ostream& os, const Receipt r);
    friend istream& operator>>(istream& is, Receipt& r);
public:
    Receipt(){}
    Receipt(const list<tuple<int, int, float>>& s, Date d = Date::today());
    Receipt(const Receipt& other);
    ~Receipt();

    float get_total_price() const;

    Date get_date() const;
    void set_date(Date d);
private:
    Date date;
    int size;
    tuple<int, int, float>* products;
};

#endif