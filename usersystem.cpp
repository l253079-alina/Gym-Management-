#include "usersystem.h"
#include "MEMBER.h"      
#include "Trainer.h"
#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

User::User(string name, string email, string password)
    : name(name), email(email), password(password) {
}

void User::displayInfo() const {
    cout << "Name  : " << name << "\n";
    cout << "Email : " << email << "\n";
    cout << "Role  : " << getRole() << "\n";
}

bool User::login(string inputEmail, string inputPassword) {
    return (inputEmail == email && inputPassword == password);
}

bool User::validateEmail(const string& email) {
    int count = 0, pos = -1;
    for (int i = 0; i < (int)email.length(); i++)
        if (email[i] == '@') { count++; pos = i; }

    if (count != 1) { cout << "Invalid email (name@gmail.com)\n"; return false; }

    string namePart = email.substr(0, pos);
    string domainPart = email.substr(pos + 1);
    bool valid = true;
    if (namePart.empty()) { cout << "Missing name part.\n"; valid = false; }
    if (domainPart != "gmail.com") { cout << "Only @gmail.com accepted.\n"; valid = false; }
    if (valid) cout << "  OK Email valid.\n";
    return valid;
}

bool User::validatePassword(const string& pwd) {
    bool valid = true;
    if ((int)pwd.length() < 6) { cout << "Too short (min 6).\n"; valid = false; }
    bool hasUpper = false;
    for (char c : pwd) if (c >= 'A' && c <= 'Z') { hasUpper = true; break; }
    if (!hasUpper) { cout << "Need at least 1 capital letter.\n"; valid = false; }
    bool hasDigit = false;
    for (char c : pwd) if (c >= '0' && c <= '9') { hasDigit = true; break; }
    if (!hasDigit) { cout << "Need at least 1 digit.\n"; valid = false; }
    if (valid) cout << "  OK Password valid.\n";
    return valid;
}

void User::forgotPassword(User* users[], const int& size) {
    string email;
    cout << " FORGOT PASSWORD "<<endl;
    cout << "Enter registered email: ";
    cin >> email;
    if (!validateEmail(email)) { cout << "Cancelled.\n"; return; }

    User* found = nullptr;
    for (int i = 0; i < size; i++)
        if (users[i]->getEmail() == email) { found = users[i]; break; }
    if (!found) { cout << "No account found.\n"; return; }

    cout << "Account found: " << found->getName() << " (" << found->getRole() << ")\n";
    string newPwd, confirmPwd;
    while (true) {
        cout << "New password: "; cin >> newPwd;
        if (!validatePassword(newPwd)) { cout << "Try again.\n"; continue; }
        cout << "Confirm: "; cin >> confirmPwd;
        if (newPwd != confirmPwd) { cout << "No match. Try again.\n"; continue; }
        found->setPassword(newPwd);
        cout << "  OK Password updated for " << found->getName() << "!\n";
        break;
    }
}

void User::registerUsers(User* users[], int& size) {
    int memberCount, adminCount;
    cout << "REGISTER USERS "<<endl;
    cout << "How many Members: "; cin >> memberCount;
    cout << "How many Admins : "; cin >> adminCount;

    for (int i = 0; i < memberCount; i++) {
        string firstName, lastName, email, password;
        cout << "Member " << (i + 1) << endl;
        cout << "First Name: "; cin >> firstName;
        cout << "Last Name : "; cin >> lastName;
        string name = firstName + " " + lastName;

        while (true) {
            cout << "Email: "; cin >> email;
            if (!validateEmail(email)) { cout << "Try again.\n"; continue; }
            bool dup = false;
            for (int j = 0; j < size; j++)
                if (users[j]->getEmail() == email) { dup = true; break; }
            if (dup) { cout << "Email already registered.\n"; continue; }
            break;
        }
        while (true) {
            cout << "Password: "; cin >> password;
            if (validatePassword(password)) break;
            cout << "Try again.\n";
        }
        users[size++] = new Member(name, email, password);
    }

    for (int i = 0; i < adminCount; i++) {
        string firstName, lastName, email, password, adminCode;
        cout << " Admin " << (i + 1) << endl;
        cout << "First Name: "; cin >> firstName;
        cout << "Last Name : "; cin >> lastName;
        string name = firstName + " " + lastName;

        while (true) {
            cout << "Email: "; cin >> email;
            if (!validateEmail(email)) { cout << "Try again.\n"; continue; }
            bool dup = false;
            for (int j = 0; j < size; j++)
                if (users[j]->getEmail() == email) { dup = true; break; }
            if (dup) { cout << "Email already registered.\n"; continue; }
            break;
        }
        while (true) {
            cout << "Password: "; cin >> password;
            if (validatePassword(password)) break;
            cout << "Try again.\n";
        }
        cout << "Admin Code: "; cin >> adminCode;
        users[size++] = new Admin(name, email, password, adminCode);
    }
    cout << "\n  OK " << size << " users registered.\n";
}

void User::loginSystem(User* users[], int& size) {
    string email, password;
    cout << " GYM LOGIN "<<endl;
    cout << "Email: "; cin >> email;
    if (!validateEmail(email)) { cout << "Login cancelled.\n"; return; }
    cout << "Password: "; cin >> password;

    for (int i = 0; i < size; i++) {
        if (users[i]->getEmail() == email) {
            if (users[i]->login(email, password)) {
                Admin* a = dynamic_cast<Admin*>(users[i]);
                if (a) a->adminPanel(users, size);
                else {
                    Member* m = dynamic_cast<Member*>(users[i]);
                    if (m) m->memberPortal(users, size);
                }
            }
            return;
        }
    }
    cout << "No account found."<<endl;
}

Member::Member(string n, string e, string p)
    : User(n, e, p), personalTrainer(nullptr), memberID(0),
    joinDate(Date()), feeStatus("Unpaid"), subscriptionType("None") {
}

Member::Member(string n, string e, string p,
    int id, const Date& jDate, string fStatus, string subType)
    : User(n, e, p), personalTrainer(nullptr), memberID(id),
    joinDate(jDate), feeStatus(fStatus), subscriptionType(subType) {
}

Member::~Member() {
    if (personalTrainer != nullptr) {
        personalTrainer->clearClient();
        personalTrainer = nullptr;
    }
}

void Member::displayInfo() const {
    User::displayInfo();
    cout << "ID     : " << memberID << endl;
    cout << "Joined : " << joinDate.toString() << endl;
    cout << "Plan   : " << subscriptionType << endl;
    cout << "Status : " << feeStatus << endl;
    if (personalTrainer)
        cout << "Trainer: " << personalTrainer->getName() << endl;
}

bool Member::login(string inputEmail, string inputPassword) {
    if (User::login(inputEmail, inputPassword)) {
        cout << " OK Member login successful! Welcome, " << name << endl;
        return true;
    }
    cout << "Incorrect email or password."<<endl;
    return false;
}

void Member::updateProfile(User* users[], int size) {
    int choice;
    cout << " PROFILE SETTINGS "<<endl;
    cout << "1. Change Email\n2. Change Password\n3. Back\nChoice: ";
    cin >> choice;

    bool changed = false;
    if (choice == 1) {
        string newEmail;
        cout << "New Email: "; cin >> newEmail;
        if (User::validateEmail(newEmail)) { email = newEmail; changed = true; }
    }
    else if (choice == 2) {
        string newPass;
        cout << "New Password: "; cin >> newPass;
        if (User::validatePassword(newPass)) { password = newPass; changed = true; }
    }
    if (changed) {
        cout << "Update successful. Syncing"<<endl;
        FileData::updateFileAfterRemoval(users, size);
    }
}

void Member::memberPortal(User* users[], int size) {
    int choice;
    do {
        cout << "\n MEMBER PORTAL (" << name << ") \n";
        cout << "1. View Profile\n2. Edit Credentials\n3. Logout\nChoice: ";
        cin >> choice;
        if (choice == 1) displayInfo();
        else if (choice == 2) updateProfile(users, size);
        else if (choice != 3) cout << "Invalid.\n";
    } while (choice != 3);
}

Admin::Admin(string name, string email, string password, string code)
    : User(name, email, password), adminCode(code) {
}

void Admin::displayInfo() const {
    User::displayInfo();
    cout << "Admin Code: [hidden]\n";
}

bool Admin::login(string inputEmail, string inputPassword) {
    if (User::login(inputEmail, inputPassword)) {
        cout << "\n  OK Admin login successful! Welcome, " << name << "\n";
        return true;
    }
    cout << "Incorrect email or password.\n";
    return false;
}

void Admin::addMember(User* users[], int& size) const {
    if (size >= 50) { cout << "System limit reached.\n"; return; }

    string firstName, lastName, email, password;
    cout << "\n-- Registering New Member --\n";
    cout << "First Name: "; cin >> firstName;
    cout << "Last Name : "; cin >> lastName;
    string fullName = firstName + " " + lastName;

    cout << "Email: "; cin >> email;
    if (!validateEmail(email)) return;
    cout << "Password: "; cin >> password;
    if (!validatePassword(password)) return;

    int d, m, y;
    cout << "Join Date (DD MM YYYY): "; cin >> d >> m >> y;
    Date today(d, m, y);

    int newID = 1000 + size;
    Member* newMemb = new Member(fullName, email, password, newID, today, "Pending", "Basic");
    users[size++] = newMemb;

    FileData::saveMemberToFile(*newMemb);
    cout << "Member '" << fullName << "' added with ID: " << newID << "\n";
}

void Admin::searchMember(User* users[], int size) const {
    cout << "Search by: 1. Email  2. ID\nChoice: ";
    int opt; cin >> opt;
    bool found = false;

    if (opt == 1) {
        string searchEmail;
        cout << "Enter Email: "; cin >> searchEmail;
        for (int i = 0; i < size; i++) {
            if (users[i]->getEmail() == searchEmail) {
                users[i]->displayInfo(); found = true; break;
            }
        }
    }
    else if (opt == 2) {
        int targetID; cout << "Enter ID: "; cin >> targetID;
        for (int i = 0; i < size; i++) {
            Member* m = dynamic_cast<Member*>(users[i]);
            if (m && m->getID() == targetID) { m->displayInfo(); found = true; break; }
        }
    }
    if (!found) cout << "Member not found.\n";
}

void Admin::updateMember(User* users[], int size) const {
    int targetID;
    cout << "Enter Member ID to update: "; cin >> targetID;

    Member* found = nullptr;
    for (int i = 0; i < size; i++) {
        Member* m = dynamic_cast<Member*>(users[i]);
        if (m && m->getID() == targetID) { found = m; break; }
    }
    if (!found) { cout << "Member not found.\n"; return; }

    int choice;
    cout << "Update Member: " << found->getName() << endl;
    cout << "1. Fee Status\n2. Subscription Type\n3. Back\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        string status;
        cout << "New fee status (Paid/Unpaid/Pending): "; cin >> status;
        found->setFeeStatus(status);
        cout << "Fee status updated."<<endl;
    }
    else if (choice == 2) {
        string subType;
        cout << "New subscription (Basic/Premium/Unique): "; cin >> subType;
        found->setSubType(subType);
        cout << "Subscription updated."<<endl;
    }
    FileData::updateFileAfterRemoval(users, size);
}

void Admin::removeMember(User* users[], int& size) const {
    int targetID;
    cout << "Enter Member ID to remove: "; cin >> targetID;

    int foundIndex = -1;
    for (int i = 0; i < size; i++) {
        Member* m = dynamic_cast<Member*>(users[i]);
        if (m && m->getID() == targetID) {
            foundIndex = i;
            if (m->getTrainer()) {
                m->getTrainer()->clearClient();
                m->setTrainer(nullptr);
            }
            break;
        }
    }

    if (foundIndex == -1) { cout << "Member not found.\n"; return; }

    delete users[foundIndex];
    for (int i = foundIndex; i < size - 1; i++)
        users[i] = users[i + 1];
    users[--size] = nullptr;

    FileData::updateFileAfterRemoval(users, size);
    cout << "Member removed successfully.\n";
}

void Admin::viewMembers(User* users[], int size) const {
    cout << "All Members "<<endl;
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (users[i]->getRole() == "Member") {
            cout << "\n";
            users[i]->displayInfo();
            count++;
        }
    }
    if (count == 0) cout << "No members registered yet."<<endl;
    else cout << "\nTotal Members: " << count << endl;
}

void Admin::adminPanel(User* users[], int& size) const {
    int choice;
    do {
        cout << "ADMIN PANEL (" << name << ")"<<endl;
        cout << "1. Add Member\n";
        cout << "2. Remove Member\n";
        cout << "3. View All Members\n";
        cout << "4. Search Member\n";
        cout << "5. Update Member\n";
        cout << "6. Exit\n";
        cout << "Choice: "; cin >> choice;

        if (choice == 1) addMember(users, size);
        else if (choice == 2) removeMember(users, size);
        else if (choice == 3) viewMembers(users, size);
        else if (choice == 4) searchMember(users, size);
        else if (choice == 5) updateMember(users, size);
        else if (choice != 6) cout << "Invalid choice.\n";
    } while (choice != 6);
}

void Admin::assignTrainer(Member* m, Trainer* t) const {
    if (m && t) {
        t->pairWithClient(m);
        cout << "[Admin " << name << "] Trainer " << t->getName()
            << " assigned to " << m->getName() << ".\n";
    }
    else {
        cout << "Error: Invalid Member or Trainer.\n";
    }
}
