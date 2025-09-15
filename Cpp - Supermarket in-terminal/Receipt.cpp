#ifndef RECEIPT_CPP
#define RECEIPT_CPP

#include <iostream>
#include <utility>
#include <list>
#include <tuple>
#include "Date.cpp"
#include "Product.cpp"
#include "Receipt.h"

using namespace std;

Receipt::Receipt(const list<tuple<int, int, float>>& s, Date d){
    size = s.size();
    products = new tuple<int, int, float>[size];
    copy(s.begin(), s.end(), products);
    set_date(d);
}

Receipt::Receipt(const Receipt& other){
    size = other.size;
    products = new tuple<int, int, float>[size];
    copy(other.products, other.products + size, products);
    set_date(other.get_date());
}

Receipt::~Receipt(){
    delete[] products;
}

float Receipt::get_total_price() const{
    float sum = 0;
    for(int i = 0; i < size; i++)
        sum += get<1>(products[i]) * get<2>(products[i]);
    return sum;
}

ostream& operator<<(ostream& os, const Receipt r){
    os << r.date << " " << r.size << " ";
    for(int i = 0; i < r.size; i++)
        os << get<0>(r.products[i]) << " " << get<1>(r.products[i]) << " " << get<2>(r.products[i]) << " ";
    return os;

}

istream& operator>>(istream& is, Receipt& r){
    is >> r.date >> r.size;
    r.products = new tuple<int, int, float>[r.size];
    for(int i = 0; i < r.size; i++){
        int first, second;
        float price;
        is >> first >> second >> price;
        r.products[i] = make_tuple(first, second, price);
    }
}

Date Receipt::get_date() const {return date;}
void Receipt::set_date(Date d) {date = d;}

#endif