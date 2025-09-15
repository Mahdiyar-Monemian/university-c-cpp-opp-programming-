#ifndef CUSTOMER_CPP
#define CUSTOMER_CPP

#include <iostream>
#include <utility>
#include <vector>
#include <exception>
#include "Receipt.cpp"
#include "Cart.cpp"
#include "Customer.h"

using namespace std;

Customer::Customer(){

}

Customer::Customer(int i, string n, string p_n, string a, float b){
    set_id(i);
    set_name(n);
    set_phone_number(p_n);
    set_address(a);
    set_balance(b);
}

void Customer::convert_cart_to_receipt(){
    // check for enough money
    float price = cart.get_total_price();
    if(price > balance){
        cout << "not enough balance" << endl;
        return;
    }

    history.push_back(cart.make_receipt());
    cart.reset();
    balance -= price;
}

float Customer::get_total_purchase_amount(){
    float total = 0;
    for(Receipt r : history)
        total += r.get_total_price();
    return total;
}

void Customer::add_purchase(int i, int quantity, float price){
    cart.add_product(i, quantity, price);
}

void Customer::add_purchase(Product p, int quantity){
    cart.add_product(p, quantity);
}

void Customer::cancel_purchase(int i){
    cart.remove_item(i);
}

// getters
int Customer::get_id() const {return id;}
string Customer::get_name() const {return name;}
string Customer::get_phone_number() const {return phone_number;}
string Customer::get_address() const {return address;}
float Customer::get_balance() const {return balance;}
vector<Receipt> Customer::get_history() const{return history;}

// setters
void Customer::set_id(int i) {id = i;}
void Customer::set_name(string n) {name = n;}
void Customer::set_phone_number(string p_n) {phone_number = p_n;}
void Customer::set_address(string a) {address = a;}
void Customer::set_balance(float b) {balance = b;}

ostream& operator<<(ostream& os, const Customer c){
    os << c.id << " " << c.name << " " << c.phone_number << " " 
       << c.address << " " << c.balance << endl;
    os << c.cart << endl;
    os << c.history.size() << endl;
    for(Receipt r : c.history)
        os << r << endl;
    
    return os;
}

istream& operator>>(istream& is, Customer& c){
    is >> c.id >> c.name >> c.phone_number >> c.address >> c.balance;
    is >> c.cart;
    int size;
    is >> size;
    for(int i = 0; i < size; i++){
        Receipt r;
        is >> r;
        c.history.push_back(r);
    }
    return is;
}

void Customer::get(){
    cout << "id: ";
    cin >> id;
    cout << "name: ";
    cin >> name;
    cout << "phone number: ";
    cin >> phone_number;
    cout << "address: ";
    cin >> address;
    cout << "balance: ";
    cin >> balance;
}

void Customer::print() const{
    cout << setw(4) << id << setw(10) << name << setw(6) << balance << "$" << endl;
}

#endif