
#ifndef USERSYSTEM_H
#define USERSYSTEM_H

#include "DATE.h"
#include <string>
#include <iostream>

class Trainer;

class User {
protected:
    std::string name;
    std::string email;
    std::string password;

public:
    User(std::string name, std::string email, std::string password);
    virtual ~User() {}

    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    std::string getPassword() const { return password; }
    void setPassword(std::string newPassword) { password = newPassword; }

    virtual void displayInfo() const;
    virtual bool login(std::string inputEmail, std::string inputPassword);
    virtual std::string getRole()     const = 0;

    static bool validateEmail(const std::string& email);
    static bool validatePassword(const std::string& pwd);
    static void loginSystem(User* users[], int& size);
    static void registerUsers(User* users[], int& size);
    static void forgotPassword(User* users[], const int& size);
};

class Member : public User {
private:
    Trainer* personalTrainer;
    int  memberID;
    Date  joinDate;
    std::string feeStatus;
    std::string subscriptionType;

public:
    Member(std::string n, std::string e, std::string p);
    Member(std::string n, std::string e, std::string p,
        int id, const Date& jDate, std::string fStatus, std::string subType);

    virtual ~Member();

    Date        getJoinDate()  const { return joinDate; }
    std::string getJoinDateStr() const { return joinDate.toString(); }

    int         getID()        const { return memberID; }
    std::string getFeeStatus() const { return feeStatus; }
    std::string getSubType()   const { return subscriptionType; }

    void setFeeStatus(std::string status) { feeStatus = status; }
    void setSubType(std::string type) { subscriptionType = type; }
    void setTrainer(Trainer* t) { personalTrainer = t; }
    Trainer* getTrainer()      const { return personalTrainer; }

    std::string getRole()    const override { return "Member"; }
    void displayInfo()       const override;
    bool login(std::string inputEmail, std::string inputPassword) override;

    void memberPortal(User* users[], int size);
    void updateProfile(User* users[], int size);
};

class Admin : public User {
private:
    std::string adminCode;

public:
    Admin(std::string name, std::string email, std::string password,
        std::string code = "");

    std::string getAdminCode() const { return adminCode; }
    std::string getRole()      const override { return "Admin"; }

    void displayInfo() const override;
    bool login(std::string inputEmail, std::string inputPassword) override;

    void adminPanel(User* users[], int& size) const;
    void addMember(User* users[], int& size) const;
    void searchMember(User* users[], int  size) const;
    void updateMember(User* users[], int  size) const;
    void removeMember(User* users[], int& size) const;
    void viewMembers(User* users[], int  size) const;

    void assignTrainer(Member* m, Trainer* t) const;
};

#endif
