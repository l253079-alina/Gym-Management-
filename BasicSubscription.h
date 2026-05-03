#pragma once
#ifndef BASICSUBSCRIPTION_H
#define BASICSUBSCRIPTION_H

#include "Subscription.h"
#include <iostream>

class BasicSubscription : public Subscription {
private:
    static double standardFee;
    static int Bcount;

public:
    BasicSubscription(string name, int age, const Date& start)
        : Subscription(name, age, "Basic", standardFee, start, start.addMonths(1)) {
        Bcount++;
    }

    double computeFee() const override {
        return (status == OVERDUE) ? (monthly_fee * (1 + penalty)) : monthly_fee;
    }

    void displayTierInfo() const override {
        std::cout << "| Access: Gym Floor Only (Off-peak hours: 9AM - 5PM)\n";
        std::cout << "| Total Basic Members: " << Bcount << "\n";
    }
    string getAccessRights()const override {
        return "Gym floor only (off-peak 9AM-5PM)";
    }

    ~BasicSubscription() override {
        Bcount--;
    }
};

#endif