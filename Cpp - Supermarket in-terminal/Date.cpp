#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

class Date{
    friend ostream& operator <<(ostream& os, const Date d);
    friend istream& operator >>(istream& is, Date& d);
public:
    // format : yyyy/mm/dd
    Date(): year(2000), month(1), day(1){}
    Date(int y, int m, int d): year(y), month(m), day(d){}
    Date(const Date& d):year(d.year), month(d.month), day(d.day){};

    static Date today(){
        time_t t = time(0);
        tm* now = localtime(&t);
        return {now->tm_year - 100 + 2000, now->tm_mon + 1, now->tm_mday};
    }

    string date()const{
        return to_string(year) + "/" + to_string(month) + "/" + to_string(day);
    }

    bool operator <(Date other){
        if(year != other.year){
            return year < other.year;
        }else if(month != other.month){
            return month < other.month;
        }else{
            return day < other.day;
        }
    }

    bool operator ==(Date other){
        return year == other.year && month == other.month && day == other.day;
    }

    bool operator >(Date other){return !(*this < other);}
    bool operator <=(Date other){return *this == other || *this < other;}
    bool operator >=(Date other){return *this == other || *this > other;}

private:
    int year, month, day;
};

ostream& operator <<(ostream& os, const Date d){
    os << d.year << "/" << d.month << "/" << d.day;
    return os;
}

istream& operator >>(istream& is, Date& d){
    is >> d.year;
    is.ignore();
    is >> d.month;
    is.ignore();
    is >> d.day;
    return is;
}

#endif