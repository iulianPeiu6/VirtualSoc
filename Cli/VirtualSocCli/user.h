#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    int UserId;
    QString Username;
    bool Admin;
    QString UserVisibility;
    QString Password;
    QString RegistrationDate;
    bool ActiveStatus;

    User();
    User(QString user);
    User(const User &u2);
    const User& operator= (const User& u);


};

#endif // USER_H
