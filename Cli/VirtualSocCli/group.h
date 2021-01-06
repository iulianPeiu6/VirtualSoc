#ifndef GROUP_H
#define GROUP_H

#include <QString>

class Group
{
public:
    int GroupId;
    QString GroupName;
    QString CreationDate;
    int NumOfMembers;
    int* MembersIds;

    Group();
    Group(QString);
};

#endif // GROUP_H
