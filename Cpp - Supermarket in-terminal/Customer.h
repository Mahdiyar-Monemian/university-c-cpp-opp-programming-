#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <utility>
#include <vector>
#include "Receipt.h"
#include "Cart.h"

using namespace std;

class Customer{
    friend ostream& operator<<(ostream& os, const Customer c);
    friend istream& operator>>(istream& is, Customer& c);
public:
    Customer();
    Customer(int i, string n, string p_n, string a, float b);

    void convert_cart_to_receipt();
    float get_total_purchase_amount();

    void add_purchase(int i, int quantity, float price);
    void add_purchase(Product p, int quantity);
    void cancel_purchase(int id);

    // getters
    int get_id() const;
    string get_name() const;
    string get_phone_number() const;
    string get_address() const;
    float get_balance() const;
    vector<Receipt> get_history() const;

    //setters
    void set_id(int i);
    void set_name(string n);
    void set_phone_number(string p_n);
    void set_address(string a);
    void set_balance(float b);

    void get();
    void print() const;
    Cart get_cart() const {return cart;}
private:
    int id;
    string name;
    string phone_number;
    string address;
    float balance;    
    Cart cart;
    vector<Receipt> history;
};

#endif