#ifndef USER_H
#define USER_H

#include <cstring>

class User {
public:
    int UserId;
    char Username[16];
    bool Admin;
    char UserVisibility[8];
    char Password[16];
    char RegistrationDate[32];
    bool ActiveStatus;

    User(   int userId,
            char username[16],
            bool admin,
            char userVisibility[8],
            char password[16],
            char registrationDate[32],
            bool activeStatus){

        UserId=userId;
        strcpy(Username,username);
        Admin=admin;
        strcpy(UserVisibility,userVisibility);
        strcpy(Password,password);
        strcpy(RegistrationDate,registrationDate);
        ActiveStatus=activeStatus;
    }
};

#endif // USER_H
