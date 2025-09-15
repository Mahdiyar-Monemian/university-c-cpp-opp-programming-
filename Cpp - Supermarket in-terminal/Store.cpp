#ifndef STORE_CPP
#define STORE_CPP

#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <fstream>
#include "Date.cpp"
#include "Product.cpp"
#include "Stock.cpp"
#include "Customer.cpp"
#include "Store.h"

using namespace std;

Store::Store(){
    fstream store_txt("store.txt", ios::in);
    if(store_txt){
        store_txt >> *this;
        store_txt.close();
        cout << "Successfully loaded from store.txt" << endl;
    }else{
        cout << "store.txt does not exist" << endl;
    }
}

bool receipt_greater_by_date(const Receipt a, const Receipt b){
    if(a.get_date() < b.get_date())
        return true;
    return false;
}

void print_sales(Date d, int money){
    cout << d << ": ";
    for(int i = 0; i < (int)(money / 100); i++)
        cout << "++ ";
    cout << endl;
}

void Store::check_out(Customer& customer){
    // for(auto t : customer.get_cart().get_items()){
    //     if(stock.get_count(get<0>(t)) < get<1>(t)){
    //         cout << "not enough stock" << endl;
    //         cout << "WE GOT TO THIS POINT" << endl;
    //         return;
    //     }
    // }
    
    for(auto t : customer.get_cart().get_items())
        stock.change_count_by(get<0>(t), -(get<1>(t)));
    customer.convert_cart_to_receipt();
    cout << "checked out " << customer.get_name() << "." << endl;
}

void Store::check_out(int customer_id){
    Customer& c = get_customer(customer_id);
    check_out(c);
}

void Store::add_customer(){
    Customer new_customer;
    new_customer.get();
    customers.push_back(new_customer);
    cout << new_customer.get_name() << " was added." << endl;
}

void Store::add_product(){
    Product new_product;
    new_product.get();
    products.push_back(new_product);
    cout << new_product.get_name() << " was added." << endl;
}

void Store::add_stock(int id, int quantity){
    stock.change_count_by(id, quantity);
    cout << get_product(id).get_name() << " now has " << stock.get_count(id) << " stocks" << endl;
}

void Store::view_products(){
    cout << "Products: " << endl;
    for(Product& p : products)
        cout << p << endl;
    cout << endl;
}
void Store::save_to_file(){
    fstream store_txt("store.txt", ios::out);
    store_txt << (*this);
    store_txt.close();
    cout << "file saved" << endl;
}

void Store::sales_report(Date begin, Date end){
    // get all the receipts in the time zone
    vector<Receipt> all_receipts;
    for(Customer c : customers)
        for(Receipt r : c.get_history())
            if(begin <= r.get_date() && r.get_date() <= end)
                all_receipts.push_back(r);

    // check for empty list
    if(all_receipts.empty()){
        cout << "no sales in this time box" << endl;
        return;
    }

    sort(all_receipts.begin(), all_receipts.end(), receipt_greater_by_date);

    Date working_date = all_receipts[0].get_date();
    float total_amount = 0;
    for (Receipt r : all_receipts){
        if(r.get_date() == working_date){
            total_amount += r.get_total_price();
        }else{
            print_sales(working_date, total_amount);
            working_date = r.get_date();
            total_amount = r.get_total_price();
        }
    }
    print_sales(working_date, total_amount);
}

Customer& Store::get_customer(int id){
    for(Customer& c : customers)
        if(c.get_id() == id)
            return c;
    throw invalid_argument("No customer with this id");
}
Product& Store::get_product(int id){
    for(Product& p : products)
        if(p.get_id() == id)
            return p;
    throw invalid_argument("No product with this id");
}

void Store::print_customers() const{
    for(Customer c : customers)
        c.print();
}

void Store::print_products() const{
    for(Product p : products)
        p.print();
}

ostream& operator<<(ostream& os, const Store s){
    os << s.stock << endl << endl;
    os << s.products.size() << endl;
    for(Product p : s.products)
        os << p << endl;
    os << endl;
    os << s.customers.size() << endl;
    for(Customer c : s.customers)
        os << c << endl;

    return os;

}
istream& operator>>(istream& is, Store& s){
    is >> s.stock;
    int size;
    is >> size;
    for(int i = 0; i < size; i++){
        Product p;
        is >> p;
        s.products.push_back(p);
    }
    is >> size;
    for(int i = 0; i < size; i++){
        Customer c;
        is >> c;
        s.customers.push_back(c);
    }

    return is;
}

#endif