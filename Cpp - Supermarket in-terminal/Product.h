#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <vector>
#include "Date.cpp"

using namespace std;

class Product{
    friend ostream& operator <<(ostream& os, const Product p);
    friend istream& operator >>(istream& is, Product& p);
public:
    Product();
    Product(int, string, float, string, Date);
    Product(const Product&);

    int get_id() const;
    string get_name() const;
    float get_price() const;
    string get_brand() const;
    Date get_date() const;

    void set_id(int);
    void set_name(string);
    void set_price(float);
    void set_brand(string);
    void set_date(Date);
    
    void print() const;
    void get();

private:
    int id;
    string name;
    float price;
    string brand;
    Date expire_date;
};

#endif