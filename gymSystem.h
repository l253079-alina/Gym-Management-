#ifndef GYMSYSTEM_H
#define GYMSYSTEM_H

#include <string>
#include <iostream>
using namespace std;

class AttendanceLog {
private:
    int    memberID;
    string date;
    string inTime;
    string outTime;
    bool   feePaid;
    int    visits;

public:
    AttendanceLog();

    void input();
    bool access();
    void display();
    int  getDays();

    ~AttendanceLog();
};

class ProgressAnalytics {
private:
    float  weight;
    float  target;
    float  height;
    float* history;

public:
    ProgressAnalytics();
    ProgressAnalytics(const ProgressAnalytics& other);
    ProgressAnalytics& operator=(const ProgressAnalytics& other);
    ~ProgressAnalytics();

    void        input();
    float       bmi();
    const char* category();
    float       change();
    float       average();
    void        report();
    float       consistency(int days);
};

#endif
#pragma once
