#ifndef CART_CPP
#define CART_CPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>
#include "Product.cpp"
#include "Receipt.cpp"
#include "Cart.h"

using namespace std;

Cart::Cart(){

}

Cart::~Cart(){
    items.clear();
}

float Cart::get_total_price(){
    float sum = 0;
    for(tuple<int, int, float>& p : items)
        sum += get<1>(p) * get<2>(p);
    return sum;
}

void Cart::add_product(int id, int quantity, float price){
    items.push_back(make_tuple(id, quantity, price));
}

void Cart::add_product(Product p, int quantity){
    items.push_back(make_tuple(p.get_id(), quantity, p.get_price()));
}

void Cart::remove_item(int id){
    for(auto i : items)
        if(get<0>(i) == id)
            items.remove(i);
}

list<tuple<int,int,float>> Cart::get_items() const{
    return items;
}

// void Cart::print() const{
//     cout << "Cart:" << endl;
//     for(auto i : items){
//         Product& p = store.get_product(i.first);
//         cout << setw(15) << p.get_name()
//              << setw(8) << to_string(p.get_price()) + "$"
//              << "x" << i.second << endl;
//     }
//     cout << endl;
// }

void Cart::print() const{
    cout << "Cart:" << endl;
    for(auto i : items){
        cout << setw(5) << get<0>(i)
             << setw(5) << "x" + to_string(get<1>(i))
             << setw(6) << get<2>(i) << "$" << endl;
    }
}

Receipt Cart::make_receipt(){
    return items;
}

void Cart::check_out(){

}

void Cart::reset(){
    items.clear();
}

ostream& operator<<(ostream& os, const Cart c){
    os << c.items.size() << " ";
    for(auto t : c.items)
        os << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << " ";
    return os;

}

istream& operator>>(istream& is, Cart& c){
    int size;
    is >> size;
    for(int i = 0; i < size; i++){
        int first, second;
        float price;
        is >> first >> second >> price;
        c.items.push_back(make_tuple(first, second, price));
    }
}

#endif