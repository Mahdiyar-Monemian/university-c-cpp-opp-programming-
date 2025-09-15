#ifndef PRODUCT_CPP
#define PRODUCT_CPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <exception>
#include "Product.h"

using namespace std;

Product::Product(){
    
}

Product::Product(int i, string n, float p, string b, Date e){
    set_id(i);
    set_name(n);
    set_price(p);
    set_brand(b);
    set_date(e);
}

Product::Product(const Product& other){
    set_id(other.id);
    set_name(other.name);
    set_price(other.price);
    set_brand(other.brand);
    set_date(other.expire_date);
}

int Product::get_id() const { return id; }
string Product::get_name() const { return name; }
float Product::get_price() const { return price; }
string Product::get_brand() const { return brand; }
Date Product::get_date() const { return expire_date; }

void Product::set_id(int i) { id = i; }
void Product::set_name(string n) { name = n; }
void Product::set_price(float p) { price = p; }
void Product::set_brand(string b) { brand = b; }
void Product::set_date(Date e) { expire_date = e; }

istream& operator >>(istream& is, Product& p){
    is >> p.id >> p.name >> p.price >> p.brand >> p.expire_date;
}

ostream& operator <<(ostream& os, const Product p){
    os << p.id << " " << p.name << " "<< p.price << " " << p.brand << " " << p.expire_date;
}

void Product::print() const{
    cout << setw(4) << id << setw(10) << name << setw(10) << brand << setw(10) << expire_date << endl;
}


void Product::get(){
    cout << "id: ";
    cin >> id;
    cout << "name: ";
    cin >> name;
    cout << "price: ";
    cin >> price;
    cout << "brand: ";
    cin >> brand;
    cout << "expire date: ";
    cin >> expire_date;
}

#endif