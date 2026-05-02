#include "MEMBER.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

namespace FileData {

    void saveMemberToFile(const Member& m) {
        ofstream file("members.txt", ios::app);
        if (!file) {
            cerr << "Error opening file for writing!\n";
            return;
        }
        file << m.getID()          << "|"
             << m.getName()        << "|"
             << m.getSubType()     << "|"
             << m.getFeeStatus()   << "|"
             << m.getJoinDateStr() << "\n";
        file.close();
        cout << "Member saved to disk successfully!\n";
    }

    void displayAllFromFile() {
        ifstream file("members.txt");
        if (!file.is_open()) { 
            cout << "No data file found.\n"; 
            return; 
        }

        string line;
        cout << "\n=== Registered Members (File Database) ===\n";
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string id, name, sub, status, date;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, sub, '|');
            getline(ss, status, '|');
            getline(ss, date, '|');

            cout << "ID: " << id << " | Name: " << name
                 << " | Plan: " << sub << " | Status: " << status << "\n";
        }
        file.close();
    }

    void searchMemberInFile(int targetId) {
        ifstream file("members.txt");
        if (!file.is_open()) { cout << "No data file found.\n"; return; }

        string line;
        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string sid, name, sub, status, date;

            getline(ss, sid, '|');
            getline(ss, name, '|');
            getline(ss, sub, '|');
            getline(ss, status, '|');
            getline(ss, date, '|');

            if (sid == to_string(targetId)) {
                cout << "Found — ID: " << sid << " | Name: " << name
                     << " | Plan: " << sub << " | Status: " << status
                     << " | Joined: " << date << "\n";
                found = true;
                break;
            }
        }
        if (!found) cout << "No member with ID " << targetId << " found in file.\n";
        file.close();
    }

    void updateFileAfterRemoval(User* users[], int size) {
        ofstream file("members.txt", ios::trunc);
        for (int i = 0; i < size; i++) {
            Member* m = dynamic_cast<Member*>(users[i]);
            if (m) {
                file << m->getID()          << "|"
                     << m->getName()        << "|"
                     << m->getSubType()     << "|"
                     << m->getFeeStatus()   << "|"
                     << m->getJoinDateStr() << "\n";
            }
        }
        file.close();
    }
}