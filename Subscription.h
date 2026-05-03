#pragma once
#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include"Date.h"
#include <string>
#include <iostream>

enum feestatus { PAID, OVERDUE, PENDING };

class Subscription {
protected:
    static int    total_members;
    static double total_revenue;
    static double penalty;

    int         subID;
    std::string memberName;
    int         age;
    std::string planType;
    double      monthly_fee;
    feestatus   status;
    Date        startDate;
    Date        expiryDate;
    bool        isActive;

public:
    Subscription(std::string name, int age, std::string plan, double fee,
        const Date& start, const Date& expiry);
    Subscription(const Subscription& other);

    virtual double      computeFee()      const = 0;
    virtual void        displayTierInfo() const = 0;
    virtual std::string getAccessRights() const = 0;

    void payFee(const Date& today);
    void trackstatus(const Date& today);
    void renew(int months, const Date& today);
    void display()  const;
    bool Active()   const { return isActive; }

    int         getId()          const { return subID; }
    std::string getMemberName()  const { return memberName; }
    std::string getPlan()        const { return planType; }
    feestatus   getFeeStatus()   const { return status; }
    void        setActive(bool active) { isActive = active; }

    virtual ~Subscription() { total_members--; }

    static double getTotalRevenue() { return total_revenue; }
};

#endif