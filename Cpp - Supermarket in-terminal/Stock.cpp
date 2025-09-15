#ifndef STOCK_CPP
#define STOCK_CPP

#include <iostream>
#include <utility>
#include <vector>
#include "Stock.h"

using namespace std;

Stock::Stock(){
    
}

Stock::Stock(vector<pair<int, int>> s){
    stock = s;
}

pair<int, int>* Stock::operator [](int id){
    for(auto& p : stock)
        if(p.first == id)
            return &p;
    return nullptr;
}


int Stock::get_count(int id){
    return (*this)[id]->second;
}
void Stock::change_count_by(int id, int value){
    auto p = (*this)[id];
    if(p)
        p->second += value;
    else
        stock.push_back(pair<int, int>(id, value));
}

ostream& operator<<(ostream& os, const Stock s){
    os << s.stock.size() << " ";
    for(auto p : s.stock)
        os << p.first << " " << p.second << " ";

    return os;
}

istream& operator>>(istream& is, Stock& s){
    int size;
    is >> size;
    for(int i = 0; i < size; i++){
        int first, second;
        is >> first >> second;
        s.stock.push_back(make_pair(first, second));
    }

    return is;
}

#endif