#include "group.h"
#include <QStringList>
#include <QtDebug>

Group::Group()
{

}

Group::Group(QString group){



    QStringList groupDetails = group.split(QLatin1Char(' '));

    GroupId=groupDetails[0].toInt();
    GroupName=groupDetails[1];
    CreationDate=groupDetails[2];

    QStringList membersIds = groupDetails[3].mid(1,groupDetails.length()-2).split(QLatin1Char(','));

    NumOfMembers=membersIds.count();

    MembersIds= new int[NumOfMembers];

    for (int i=0;i<NumOfMembers;i++)
        MembersIds[i]=membersIds[i].toInt();

}
