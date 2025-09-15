#ifndef STOCK_H
#define STOCK_H

#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;

class Stock{
    friend ostream& operator<<(ostream& os, const Stock s);
    friend istream& operator>>(istream& is, Stock& s);

public:
    Stock();
    Stock(vector<pair<int, int>> s);

    int get_count(int id);
    void change_count_by(int id, int value);

    pair<int, int>* operator [](int id);
private:
    vector<pair<int, int>> stock;
};

#endif