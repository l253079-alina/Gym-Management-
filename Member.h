#ifndef MEMBER_H
#define MEMBER_H

#include "usersystem.h"

namespace FileData {
    void saveMemberToFile(const Member& m);
    void displayAllFromFile();
    void searchMemberInFile(int id);
    void updateFileAfterRemoval(User* users[], int size);
}

#endif