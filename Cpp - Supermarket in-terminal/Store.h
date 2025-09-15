#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <utility>
#include <vector>
#include "Product.h"
#include "Date.cpp"
#include "Stock.cpp"
#include "Customer.cpp"

using namespace std;

class Store{
    friend ostream& operator<<(ostream& os, const Store s);
    friend istream& operator>>(istream& is, Store& s);
public:
    Store();

    void check_out(int customer_id);
    void check_out(Customer& customer);
    void add_customer();
    void add_product();
    void add_stock(int id, int quantity);
    void view_products();
    void save_to_file();
    void sales_report(Date begin, Date end);
    void print_customers() const;
    void print_products() const;

    Customer& get_customer(int id);
    Product& get_product(int id);
private:
    Stock stock;
    vector<Product> products;
    vector<Customer> customers;
};

#endif