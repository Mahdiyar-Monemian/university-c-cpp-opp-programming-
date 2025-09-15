#ifndef CART_H
#define CART_H

#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
#include <list>
#include "Product.cpp"
#include "Receipt.cpp"

using namespace std;

class Cart{
    friend ostream& operator<<(ostream& os, const Cart r);
    friend istream& operator>>(istream& is, Cart& r);
public:
    Cart();
    ~Cart();

    float get_total_price();
    void add_product(int id, int quantity, float price);
    void add_product(Product p, int quantity);
    void remove_item(int id);
    void print() const;
    void check_out();
    void reset();
    list<tuple<int,int,float>> get_items() const;

    Receipt make_receipt();
private:
    list<tuple<int,int,float>> items;
};

#endif