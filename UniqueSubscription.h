#pragma once
#ifndef UNIQUESUBSCRIPTION_H
#define UNIQUESUBSCRIPTION_H

#include "Subscription.h"
using namespace std;

class UniqueSubscription : public Subscription {
private:
    static double standardFee;
    static int    maxSlots;
    static int    activeCount;
    static double adminFee;

    string trainerName;
    string lockerNumber;
    int    nutritionSession;

public:
    UniqueSubscription()
        : Subscription("Unknown", 18, "Unique (VIP)", standardFee,
            Date(1, 1, 2026), Date(1, 1, 2026).addMonths(12)) {
        trainerName = "To be assigned";
        lockerNumber = "Unassigned";
        nutritionSession = 2;
        if (activeCount < maxSlots) {
            ++activeCount;
            isActive = true;
        }
        else {
            cout << "Error: No Unique slot available. Max: " << maxSlots << "\n";
            isActive = false;
        }
    }
    UniqueSubscription(const string& name, int age, const Date& start,
        const string& trainer = "To be assigned",
        const string& locker = "VIP-auto",
        int nutrition = 2)
        : Subscription(name, age, "Unique (VIP)", standardFee, start, start.addMonths(12)) {
        trainerName = trainer;
        lockerNumber = locker;
        nutritionSession = nutrition;
        if (activeCount < maxSlots) {
            ++activeCount;
            lockerNumber = (locker == "VIP-auto") ? ("VIP-" + to_string(activeCount)) : locker;
            isActive = true;
        }
        else {
            cout << "Error: No Unique slot available. Max: " << maxSlots << "\n";
            trainerName = "N/A";
            lockerNumber = "None";
            isActive = false;
        }
    }

    UniqueSubscription(const UniqueSubscription& obj) : Subscription(obj) {
        trainerName = obj.trainerName;
        lockerNumber = obj.lockerNumber;
        nutritionSession = obj.nutritionSession;
        if (activeCount < maxSlots) {
            ++activeCount;
        }
        else {
            cout << "Error: No Unique slot available. Max: " << maxSlots << "\n";
        }
    }
    ~UniqueSubscription() override {
        if (isActive && activeCount > 0) {
            --activeCount;
        }
    }

    double computeFee() const override {
        double fee = monthly_fee * 12;
        if (status == OVERDUE)
            fee += (monthly_fee * penalty) + adminFee;
        return fee;
    }

    string getAccessRights() const override {
        return "All facilities 24/7, VIP lounge, Sauna, Private training room, "
            "Nutrition consultations (" + to_string(nutritionSession) + "/month)";
    }

    void displayTierInfo() const override {
        cout << "| Trainer     : " << trainerName << " (dedicated)\n";
        cout << "| Locker      : " << lockerNumber << " (private)\n";
        cout << "| Nutrition   : " << nutritionSession << " session(s)/month\n";
        cout << "| VIP Slots   : " << activeCount << " / " << maxSlots << " used\n";
        cout << "| Late Policy : 10% penalty + PKR 500 admin fee\n";
    }

    void setTrainerName(const string& t) { trainerName = t; }
    void setLockerNumber(const string& l) { lockerNumber = l; }
    void setNutritionSessions(int n) {
        if (n < 0) cout << "[ERROR] Sessions cannot be negative.\n";
        else nutritionSession = n;
    }

    string getTrainerName()      const { return trainerName; }
    string getLockerNumber()     const { return lockerNumber; }
    int    getNutritionSessions()const { return nutritionSession; }

    static int    getActiveCount() { return activeCount; }
    static int    getMaxSlots() { return maxSlots; }
    static int    getAvailableSlots() { return maxSlots - activeCount; }
    static void   setMaxSlots(int n) { if (n > 0) maxSlots = n; }
    static double getStandardFee() { return standardFee; }
};

#endif