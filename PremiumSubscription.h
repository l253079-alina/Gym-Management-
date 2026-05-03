#pragma once
#ifndef PREMIUMSUBSCRIPTION_H
#define PREMIUMSUBSCRIPTION_H
#include "Subscription.h"
using namespace std;

class PremiumSubscription : public Subscription {
private:
    static double standardFee;
    static int    Pcount;
    int  trainersSession;
    bool poolAccess;
    bool groupClassAccess;

public:
    PremiumSubscription()
        : Subscription("Unknown", 18, "Premium", standardFee,
            Date(1, 1, 2026), Date(1, 1, 2026).addMonths(1)) {
        trainersSession = 0;
        poolAccess = true;
        groupClassAccess = true;
        ++Pcount;
    }

    PremiumSubscription(const string& name, int age, const Date& start,
        int sessions = 0, bool pool = false, bool group = false)
        : Subscription(name, age, "Premium", standardFee, start, start.addMonths(1)) {
        trainersSession = sessions;
        poolAccess = pool;
        groupClassAccess = group;
        ++Pcount;
    }

    PremiumSubscription(const PremiumSubscription& obj) : Subscription(obj) {
        trainersSession = obj.trainersSession;
        poolAccess = obj.poolAccess;
        groupClassAccess = obj.groupClassAccess;
        ++Pcount;
    }

    ~PremiumSubscription() override {}

    double computeFee() const override {
        return (status == OVERDUE) ? (monthly_fee * (1 + penalty)) : monthly_fee;
    }
    string getAccessRights() const override {
        string access = "Full gym floor (5 AM - 11 PM)";
        if (poolAccess)        access += ", swimming pool";
        if (groupClassAccess)  access += ", group classes";
        if (trainersSession > 0)
            access += ", Personal trainer (" + to_string(trainersSession) + " sessions/week)";
        return access;
    }

    void displayTierInfo() const override {
        cout << "| Trainer     : "
            << (trainersSession > 0 ? to_string(trainersSession) + " session(s)/week" : "Not booked") << "\n";
        cout << "| Pool Access : " << (poolAccess ? "Yes" : "No") << "\n";
        cout << "| Group Class : " << (groupClassAccess ? "Yes" : "No") << "\n";
        cout << "| Late Policy : 10% penalty on base fee if overdue\n";
    }

    void setTrainerSession(int n) {
        if (n < 0 || n > 7) cout << "[ERROR] Trainer sessions must be 0–7/week.\n";
        else trainersSession = n;
    }
    void setPoolAccess(bool p) { poolAccess = p; }
    void setGroupAccess(bool g) { groupClassAccess = g; }

    int  getTrainerSessions() const { return trainersSession; }
    bool getPoolAccess()      const { return poolAccess; }
    bool getGroupClass()      const { return groupClassAccess; }

    static int    getPcount() { return Pcount; }
    static double getPremiumFee() { return standardFee; }
    static void   setPremiumFee(double f) { if (f >= 0) standardFee = f; }
};

#endif