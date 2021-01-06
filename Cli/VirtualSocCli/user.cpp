#include "user.h"
#include <QString>
#include <QStringList>

User::User(QString user){

    QStringList userDetails = user.split(QLatin1Char(' '));

    UserId=userDetails[0].toInt();
    Username=userDetails[1];
    if (userDetails[2]=="false")
        Admin=false;
    else
        Admin=true;
    UserVisibility=userDetails[3];
    Password=userDetails[4];
    RegistrationDate=userDetails[5];
    if (userDetails[6]=="false")
        ActiveStatus=false;
    else
        ActiveStatus=true;
}

User::User(){

}

User::User(const User &u2) {
    UserId=u2.UserId;
    Username=u2.Username;
    Admin=u2.Admin;
    UserVisibility=u2.UserVisibility;
    Password=u2.Password;
    RegistrationDate=u2.RegistrationDate;
    ActiveStatus=u2.ActiveStatus;
}

const User& User::operator=(const User& u){
    UserId=u.UserId;
    Username=u.Username;
    UserVisibility=u.UserVisibility;
    Admin=u.Admin;
    Password=u.Password;
    RegistrationDate=u.RegistrationDate;
    ActiveStatus=u.ActiveStatus;
    return *this;
}
