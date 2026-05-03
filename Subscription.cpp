#include "Subscription.h"
#include "BasicSubscription.h"
#include "PremiumSubscription.h"
#include "UniqueSubscription.h"
#include <iostream>
using namespace std;

int    Subscription::total_members = 0;
double Subscription::total_revenue = 0.0;
double Subscription::penalty = 0.10;

double BasicSubscription::standardFee = 5000.0;
int    BasicSubscription::Bcount = 0;

double PremiumSubscription::standardFee = 10000.0;
int    PremiumSubscription::Pcount = 0;

double UniqueSubscription::standardFee = 20000.0;
int    UniqueSubscription::activeCount = 0;
int    UniqueSubscription::maxSlots = 10;
double UniqueSubscription::adminFee = 500.0;

static string feeStatusString(feestatus s) {
    if (s == PAID)    return "Paid";
    if (s == OVERDUE) return "Overdue";
    return "Pending";
}

Subscription::Subscription(string name, int age, string plan, double fee,
    const Date& start, const Date& expiry)
    : memberName(name), age(age), planType(plan), monthly_fee(fee),
    status(PENDING), startDate(start), expiryDate(expiry), isActive(true) {
    subID = ++total_members;
}

Subscription::Subscription(const Subscription& other)
    : memberName(other.memberName), age(other.age), planType(other.planType),
    monthly_fee(other.monthly_fee), status(other.status),
    startDate(other.startDate), expiryDate(other.expiryDate),
    isActive(other.isActive) {
    subID = other.subID;
}

void Subscription::payFee(const Date&) {
    if (status == PAID) {
        cout << "[" << memberName << "] Fee already paid.\n";
        return;
    }
    status = PAID;
    double amount = computeFee();
    total_revenue += amount;
    cout << "[" << memberName << "] Fee paid. Amount: PKR " << amount << "\n";
}

void Subscription::trackstatus(const Date& today) {
    if (expiryDate < today) {
        if (status != PAID) {
            status = OVERDUE;
            cout << "[SYSTEM] Account for " << memberName << " is now OVERDUE. Penalty applied.\n";
        }
    }
    else if (status != PAID) {
        status = PENDING;
    }
}

void Subscription::renew(int months, const Date& today) {
    expiryDate = today.addMonths(months);
    status = PENDING;
    cout << "[" << memberName << "] Subscription renewed for " << months
        << " month(s). New expiry: " << expiryDate.toString() << "\n";
}

void Subscription::display() const {
    cout << "\n----- Subscription #" << subID << " -----\n";
    cout << "| Member   : " << memberName << "\n";
    cout << "| Age      : " << age << "\n";
    cout << "| Plan     : " << planType << "\n";
    cout << "| Fee/mo   : PKR " << monthly_fee << "\n";
    cout << "| Status   : " << feeStatusString(status) << "\n";
    cout << "| Start    : " << startDate.toString() << "\n";
    cout << "| Expiry   : " << expiryDate.toString() << "\n";
    cout << "| Active   : " << (isActive ? "Yes" : "Frozen") << "\n";
    cout << "| Access   : " << getAccessRights() << "\n";
    displayTierInfo();
    cout << "----------------------------\n";
}