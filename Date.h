#pragma once
#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

    static bool isLeap(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }
    static int daysInMonth(int m, int y) {
        int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (m == 2 && isLeap(y)) return 29;
        return days[m - 1];
    }

public:
    Date() : day(1), month(1), year(2026) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    Date(const Date& obj) : day(obj.day), month(obj.month), year(obj.year) {}

    int getDay()   const { return day; }
    int getMonth() const { return month; }
    int getYear()  const { return year; }

    Date addDays(int n) const {
        Date result(*this);
        result.day += n;
        while (result.day > daysInMonth(result.month, result.year)) {
            result.day -= daysInMonth(result.month, result.year);
            result.month++;
            if (result.month > 12) { result.month = 1; result.year++; }
        }
        return result;
    }

    Date addMonths(int n) const {
        Date result(*this);
        result.month += n;
        while (result.month > 12) { result.month -= 12; result.year++; }
        int maxDays = daysInMonth(result.month, result.year);
        if (result.day > maxDays) result.day = maxDays;
        return result;
    }

    bool operator<(const Date& o)  const {
        if (year != o.year)  return year < o.year;
        if (month != o.month) return month < o.month;
        return day < o.day;
    }
    bool operator==(const Date& o) const { return day == o.day && month == o.month && year == o.year; }
    bool operator<=(const Date& o) const { return *this < o || *this == o; }
    bool operator>(const Date& o)  const { return !(*this <= o); }
    Date& operator=(const Date& o) {
        if (this != &o) { day = o.day; month = o.month; year = o.year; }
        return *this;
    }

    string toString() const {
        string y = to_string(year);
        string m = (month < 10 ? "0" : "") + to_string(month);
        string d = (day < 10 ? "0" : "") + to_string(day);
        return y + "-" + m + "-" + d;
    }
    void print() const { cout << toString(); }
};

#endif