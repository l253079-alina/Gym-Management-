#pragma once
#ifndef SUBSCRIPTIONMANAGER_H
#define SUBSCRIPTIONMANAGER_H
#include"Subscription.h"
using namespace std;

class SubscriptionManager {
private:
	static const int MAX_MEMBERS = 250;
	Subscription* membs[MAX_MEMBERS];
	int count;
public:
	SubscriptionManager() {
		count = 0;
		for (int i = 0; i < MAX_MEMBERS; i++)
			*(membs + i) = nullptr;
	}

	~SubscriptionManager() {
		for (int i = 0; i < count; i++) {
			delete* (membs + i);
			*(membs + i) = nullptr;
		}
	}

	bool enroll(Subscription* sub) {
		if (count >= MAX_MEMBERS) {
			cout << "Capacity FULL!" << endl;
			return false;
		}
		*(membs + (count++)) = sub;
		cout << "[ENROLLED] " << sub->getMemberName() << " (#" << sub->getId() << ") - " << sub->getPlan() << "\n";
		return true;
	}

	void trackAllStatus(const Date& today) {
		for (int i = 0; i < count; i++) {
			membs[i]->trackstatus(today);
		}
	}

	void display()const {
		cout << "\n========  GYM MEMBER ROSTER  ========\n";
		for (int i = 0; i < count; i++)
			membs[i]->display();
		cout << "=====================================\n";
	}

	void displaybyStatus(feestatus status)const {
		string label;
		if (status == PAID)
			label = "PAID";
		else if (status == OVERDUE)
			label = "OVERDUE";
		else
			label = "PENDING";

		cout << "\n========  STATUS: " << label << "  ========\n";
		bool found = false;
		for (int i = 0; i < count; i++) {
			if (membs[i]->getFeeStatus() == status) {
				membs[i]->display();
				found = true;
			}
		}
		if (!found)
			cout << " (none)\n";
		cout << "==========================================\n";
	}

	void displayByPlan(const string& plan)const {
		cout << "\n========  TIER: " << plan << "  ========\n";
		for (int i = 0; i < count; i++)
			if (membs[i]->getPlan() == plan)
				membs[i]->display();
		cout << "===========================================\n";
	}

	void payFeebyID(int ID, const Date& today) {
		for (int i = 0; i < count; i++) {
			if (membs[i]->getId() == ID) {
				membs[i]->payFee(today);
				return;
			}
		}
		cout << "Sub#" << ID << " not found!\n";
	}

	void renewbyID(int ID, int months, const Date& today) {
		for (int i = 0; i < count; i++) {
			if (membs[i]->getId() == ID) {
				membs[i]->renew(months, today);
				return;
			}
		}
		cout << "Sub#" << ID << " not found.\n";
	}

	void setActivebyId(int ID, bool active) {
		for (int i = 0; i < count; i++) {
			if (membs[i]->getId() == ID) {
				membs[i]->setActive(active);
				return;
			}
		}
		cout << "[GYM] Member #" << ID << " not found.\n";
	}

	void PrintSummary()const {
		int paid = 0, overdue = 0, pending = 0, frozen = 0;
		for (int i = 0; i < count; i++) {
			feestatus s = membs[i]->getFeeStatus();
			if (s == PAID)
				paid++;
			else if (s == OVERDUE)
				overdue++;
			else
				pending++;
			if (!membs[i]->Active())
				frozen++;
		}
		cout << "\n========== ROSTER SUMMARY ==========\n";
		cout << "  Total Enrolled : " << count << "\n";
		cout << "  Fees Paid      : " << paid << "\n";
		cout << "  Fees Pending   : " << pending << "\n";
		cout << "  Fees Overdue   : " << overdue << "\n";
		cout << "  Frozen Members : " << frozen << "\n";
		cout << "  Total Revenue  : PKR " << Subscription::getTotalRevenue() << "\n";
		cout << "=====================================\n";
	}

	int getCount()const {
		return count;
	}
};

#endif