#ifndef TOOLS_H
#define TOOLS_H

#include "User.h"
#include <QtDebug>
#include <QtSql>

QString userAuthentication(QString username,QString password){
    QSqlQuery getUsersQry,updateUserStatusQry;
    if (getUsersQry.exec("SELECT * from \"Users\"")){
        while(getUsersQry.next()){
            if (username==getUsersQry.value(1).toString() and password==getUsersQry.value(4).toString()){
                updateUserStatusQry.prepare("UPDATE \"Users\" SET \"ActiveStatus\"=TRUE WHERE \"Username\"=:username");
                updateUserStatusQry.bindValue(":username",username);
                if (!updateUserStatusQry.exec())
                    qCritical() <<updateUserStatusQry.lastError();

                return getUsersQry.value(0).toString()+" "+getUsersQry.value(1).toString()+" "+getUsersQry.value(2).toString()+" "+getUsersQry.value(3).toString()+" "+getUsersQry.value(4).toString()+" "+getUsersQry.value(5).toString()+" "+getUsersQry.value(6).toString();
            }


        }
    }
    return "Wrong username or password";
}

QString userRegistration(QString username,QString password){

    QSqlQuery usernameExistQry,updateUserStatusQry;

    usernameExistQry.prepare("SELECT count(*) FROM \"Users\" WHERE \"Username\"=:username");

    usernameExistQry.bindValue(":username",username);


    if (!usernameExistQry.exec())
        qCritical() <<usernameExistQry.lastError();

    usernameExistQry.next();

    if (usernameExistQry.value(0).toInt()>0)
        return "Username already taken";

    updateUserStatusQry.prepare("INSERT INTO \"Users\" VALUES (nextval('\"Users_UserId_seq\"'::regclass),:username,FALSE,'public',:password,current_date,TRUE)");


    updateUserStatusQry.bindValue(":username",username);
    updateUserStatusQry.bindValue(":password",password);

    if (!updateUserStatusQry.exec())
        qCritical() <<updateUserStatusQry.lastError();

    QSqlQuery getUserQry;

    getUserQry.prepare("SELECT * FROM \"Users\" WHERE \"Username\"=:username");

    getUserQry.bindValue(":username",username);

    if (!getUserQry.exec())
        qCritical() <<getUserQry.lastError();

    getUserQry.next();

    return getUserQry.value(0).toString()+" "+getUserQry.value(1).toString()+" "+getUserQry.value(2).toString()+" "+getUserQry.value(3).toString()+" "+getUserQry.value(4).toString()+" "+getUserQry.value(5).toString()+" "+getUserQry.value(6).toString();
}

QString userLogout(QString username){
    QSqlQuery updateUserStatusQry;
    updateUserStatusQry.prepare("UPDATE \"Users\" SET \"ActiveStatus\"=FALSE WHERE \"Username\"=:username");
    updateUserStatusQry.bindValue(":username",username);
    if (!updateUserStatusQry.exec())
        qCritical() <<updateUserStatusQry.lastError();
    return "Successfully logged out";
}

QString userUpdate(QString id,QString username,QString userVisibility,QString password){
    QSqlQuery usernameExistQry;

    usernameExistQry.prepare("SELECT count(*) FROM \"Users\" WHERE \"Username\"=:username AND \"UserId\"!=:userid");

    usernameExistQry.bindValue(":username",username);
    usernameExistQry.bindValue(":userid",id);

    if (!usernameExistQry.exec())
        qCritical() <<usernameExistQry.lastError();

    usernameExistQry.next();

    if (usernameExistQry.value(0).toInt()>0)
        return "Username already taken";

    QSqlQuery updateUserQry;

    updateUserQry.prepare("UPDATE \"Users\" SET (\"Username\",\"UserVisibility\",\"Password\")=(:username,:user_visibility,:password) WHERE \"UserId\"=:id");

    updateUserQry.bindValue(":username",username);
    updateUserQry.bindValue(":user_visibility",userVisibility);
    updateUserQry.bindValue(":password",password);
    updateUserQry.bindValue(":id",id.toInt());

    if (!updateUserQry.exec())
        qCritical() <<updateUserQry.lastError();

    QSqlQuery getUserQry;

    getUserQry.prepare("SELECT * FROM \"Users\" WHERE \"UserId\"=:userid");

    getUserQry.bindValue(":userid",id);

    if (!getUserQry.exec())
        qCritical() <<getUserQry.lastError();

    getUserQry.next();

    return getUserQry.value(0).toString()+" "+getUserQry.value(1).toString()+" "+getUserQry.value(2).toString()+" "+getUserQry.value(3).toString()+" "+getUserQry.value(4).toString()+" "+getUserQry.value(5).toString()+" "+getUserQry.value(6).toString();
}

QString deleteUser(int userId){
    QSqlQuery deleteUserQry;
    deleteUserQry.prepare("DELETE FROM \"Users\" WHERE \"UserId\"=:userId");
    deleteUserQry.bindValue(":userId",userId);
    if (!deleteUserQry.exec())
        qCritical() <<deleteUserQry.lastError();

    deleteUserQry.prepare("DELETE FROM \"Posts\" WHERE \"UserId\"=:userId");
    deleteUserQry.bindValue(":userId",userId);
    if (!deleteUserQry.exec())
        qCritical() <<deleteUserQry.lastError();

    deleteUserQry.prepare("DELETE FROM \"Friendships\" WHERE \"UserId\"=:userId OR \"FriendId\"=:userId");
    deleteUserQry.bindValue(":userId",userId);
    if (!deleteUserQry.exec())
        qCritical() <<deleteUserQry.lastError();

    deleteUserQry.prepare("DELETE FROM \"Groups\" WHERE CARDINALITY(\"MembersIds\")=2 AND (\"MembersIds\"[1]=:userId OR \"MembersIds\"[2]=:userId)");
    deleteUserQry.bindValue(":userId",userId);
    if (!deleteUserQry.exec())
        qCritical() <<deleteUserQry.lastError();

    return "Account successfully deleted";
}

QString getAllUsers(QString userId){
    QString allUsers;
    QSqlQuery getUsersQry;
    getUsersQry.prepare("SELECT * from \"Users\" WHERE \"UserId\"!=:user_id");
    getUsersQry.bindValue(":user_id",userId.toInt());
    if (getUsersQry.exec()){
        while(getUsersQry.next())
            allUsers=allUsers   +getUsersQry.value(0).toString()+" "
                                +getUsersQry.value(1).toString()+" "
                                +getUsersQry.value(2).toString()+" "
                                +getUsersQry.value(3).toString()+" "
                                +getUsersQry.value(4).toString()+" "
                                +getUsersQry.value(5).toString()+" "
                                +getUsersQry.value(6).toString()+" ";
    }
    else{
        qDebug() <<getUsersQry.lastError();
    }
    return QString(allUsers);
}

QString getAllFriends(QString userId){
    QString allUsers;
    QSqlQuery getUsersQry;
    getUsersQry.prepare("SELECT * FROM \"Users\" WHERE \"UserId\" IN (SELECT \"MembersIds\"[1] FROM \"Groups\" WHERE CARDINALITY(\"MembersIds\")=2 AND \"MembersIds\"[1]!=:user_id AND \"MembersIds\"[2]=:user_id UNION SELECT \"MembersIds\"[2] FROM \"Groups\" WHERE CARDINALITY(\"MembersIds\")=2 AND \"MembersIds\"[1]=:user_id AND \"MembersIds\"[2]!=:user_id);");
    getUsersQry.bindValue(":user_id",userId.toInt());
    if (getUsersQry.exec()){
        while(getUsersQry.next())
            allUsers=allUsers   +getUsersQry.value(0).toString()+" "
                                +getUsersQry.value(1).toString()+" "
                                +getUsersQry.value(2).toString()+" "
                                +getUsersQry.value(3).toString()+" "
                                +getUsersQry.value(4).toString()+" "
                                +getUsersQry.value(5).toString()+" "
                                +getUsersQry.value(6).toString()+" ";
    }
    else{
        qDebug() <<getUsersQry.lastError();
    }
    return QString(allUsers);
}

QString getAllGroupMsgs(int groupId){
    QString allGroupMsgs;
    QSqlQuery getAllGroupMsgsQry;
    getAllGroupMsgsQry.prepare("SELECT \"MessageId\",\"MessageText\",\"SendingDate\",\"Username\" FROM \"Messages\" JOIN \"Users\" ON \"FromId\"=\"UserId\" WHERE \"GroupId\"=:groupId ORDER BY \"SendingDate\",\"MessageId\"");
    getAllGroupMsgsQry.bindValue(":groupId",groupId);

    if (getAllGroupMsgsQry.exec()){
        while(getAllGroupMsgsQry.next())
            allGroupMsgs=allGroupMsgs   +getAllGroupMsgsQry.value(0).toString()+" "
                                        +getAllGroupMsgsQry.value(2).toString()+" "
                                        +getAllGroupMsgsQry.value(3).toString()+" "
                                        +getAllGroupMsgsQry.value(1).toString()+"\n";
    }
    else
        qDebug() <<getAllGroupMsgsQry.lastError();
    return QString(allGroupMsgs);
}


QString sendMsgToGroup(QString groupId,QString fromId, QString textMsg){

    QSqlQuery sendMsgToGroupQry;
    sendMsgToGroupQry.prepare("INSERT INTO \"Messages\" VALUES (nextval('\"Messages_MessageId_seq\"'::regclass),:textMsg,:groupId,current_date,:fromId)");
    sendMsgToGroupQry.bindValue(":groupId",groupId.toInt());
    sendMsgToGroupQry.bindValue(":fromId",fromId.toInt());
    sendMsgToGroupQry.bindValue(":textMsg",textMsg);

    if (!sendMsgToGroupQry.exec())
        qDebug() <<sendMsgToGroupQry.lastError();
    return "Message succefully sent!";
}

QString getGroup2Details(QVector<int> membersIds){

    QString groupDetails;
    QSqlQuery getGroupDetailsQry;
    getGroupDetailsQry.prepare("SELECT * FROM \"Groups\" WHERE CARDINALITY(\"MembersIds\")=2 AND ((\"MembersIds\"[1]=:id1 AND \"MembersIds\"[2]=:id2) OR (\"MembersIds\"[1]=:id2 AND \"MembersIds\"[2]=:id1));");
    getGroupDetailsQry.bindValue(":id1",membersIds.at(0));
    getGroupDetailsQry.bindValue(":id2",membersIds.at(1));


    if (getGroupDetailsQry.exec()){
        while(getGroupDetailsQry.next())
            groupDetails=groupDetails   +getGroupDetailsQry.value(0).toString()+" "
                                        +getGroupDetailsQry.value(1).toString()+" "
                                        +getGroupDetailsQry.value(2).toString()+" "
                                        +getGroupDetailsQry.value(3).toString();
    }
    else
        qDebug() <<getGroupDetailsQry.lastError();
    return QString(groupDetails);
}


QString getAllUserPosts(int userId){
    QString allUserPosts;
    QSqlQuery getAllUserPostsQry;
    getAllUserPostsQry.prepare("SELECT * FROM \"Posts\" WHERE \"UserId\"=:userId ORDER BY \"PostId\"");
    getAllUserPostsQry.bindValue(":userId",userId);

    if (getAllUserPostsQry.exec()){
        while(getAllUserPostsQry.next())
            allUserPosts=allUserPosts   +getAllUserPostsQry.value(0).toString()+"~"
                                        +getAllUserPostsQry.value(1).toString()+"~"
                                        +getAllUserPostsQry.value(2).toString()+"~"
                                        +getAllUserPostsQry.value(3).toString()+"~"
                                        +getAllUserPostsQry.value(4).toString()+"~"
                                        +getAllUserPostsQry.value(5).toString()+"~"
                                        +getAllUserPostsQry.value(6).toString()+"~";
    }
    else
        qDebug() <<getAllUserPostsQry.lastError();
    return QString(allUserPosts);
}

QString deletePost(int postId){
    QSqlQuery deletePostQry;
    deletePostQry.prepare("DELETE FROM \"Posts\" WHERE \"PostId\"=:postId");
    deletePostQry.bindValue(":postId",postId);
    if (!deletePostQry.exec())
        qCritical() <<deletePostQry.lastError();
    return "Post successfully deleted";
}

QString addLikeToPost(int postId){
    QSqlQuery updatePostLikesQry;
    updatePostLikesQry.prepare("UPDATE \"Posts\" SET \"Likes\"=\"Likes\"+1 WHERE \"PostId\"=:postId");
    updatePostLikesQry.bindValue(":postId",postId);
    if (!updatePostLikesQry.exec())
        qCritical() <<updatePostLikesQry.lastError();
    return "Successfully logged out";
}

QString createPost(QString title, QString text, QString visibility,QString userId){

    QSqlQuery insertPostQry;
    insertPostQry.prepare("INSERT INTO \"Posts\" values(nextval('\"Posts_PostId_seq\"'::regclass),:visibility,:userId,current_date,:text,0,:title)");

    insertPostQry.bindValue(":visibility",visibility);
    insertPostQry.bindValue(":text",text);
    insertPostQry.bindValue(":userId",userId.toInt());
    insertPostQry.bindValue(":title",title);

    if (!insertPostQry.exec())
        qDebug() <<insertPostQry.lastError();
    return "Post created!";

}

QString getFriendshipType(int userId1, int userId2){
    QSqlQuery friendshipQry;
    friendshipQry.prepare("SELECT 'Delete friend from friendlist' FROM \"Users\" WHERE \"UserId\" IN (SELECT \"MembersIds\"[1] FROM \"Groups\" WHERE CARDINALITY(\"MembersIds\")=2 AND \"MembersIds\"[1]=:userId2 AND \"MembersIds\"[2]=:userId1 UNION SELECT \"MembersIds\"[2] FROM \"Groups\" WHERE CARDINALITY(\"MembersIds\")=2 AND \"MembersIds\"[1]=:userId1 AND \"MembersIds\"[2]=:userId2)");
    friendshipQry.bindValue(":userId1",userId1);
    friendshipQry.bindValue(":userId2",userId2);
    if (friendshipQry.exec())
        if(friendshipQry.next())
            return friendshipQry.value(0).toString();
    else
        qDebug() <<friendshipQry.lastError();

    friendshipQry.prepare("SELECT 'Cancel friend request' FROM \"Friendships\" WHERE \"UserId\"=:userId1 AND \"FriendId\"=:userId2");
    friendshipQry.bindValue(":userId1",userId1);
    friendshipQry.bindValue(":userId2",userId2);
    if (friendshipQry.exec())
        if(friendshipQry.next())
            return friendshipQry.value(0).toString();
        else{
            qDebug() <<friendshipQry.lastError();
        }
    friendshipQry.prepare("SELECT 'Accept friend request' FROM \"Friendships\" WHERE \"UserId\"=:userId2 AND \"FriendId\"=:userId1");
    friendshipQry.bindValue(":userId1",userId1);
    friendshipQry.bindValue(":userId2",userId2);
    if (friendshipQry.exec())
        if(friendshipQry.next())
            return friendshipQry.value(0).toString();
        else{
            qDebug() <<friendshipQry.lastError();
        }
    return "Send friend request";
}
QString addFriendship(int userId1,int userId2, bool friends){
    QSqlQuery insertFrinshipQry;
    insertFrinshipQry.prepare("INSERT INTO \"Friendships\" values(:userId1,:userId2);");
    insertFrinshipQry.bindValue(":userId1",userId1);
    insertFrinshipQry.bindValue(":userId2",userId2);
    if (!insertFrinshipQry.exec())
        qDebug() <<insertFrinshipQry.lastError();
    if (friends){
        insertFrinshipQry.prepare("INSERT INTO \"Groups\" values(nextval('\"Groups_GroupId_seq\"'::regclass),'',current_date,:membersIds)");
        insertFrinshipQry.bindValue(":membersIds","{"+QString::number(userId1)+","+QString::number(userId2)+"}");
        if (!insertFrinshipQry.exec()){
            qDebug() <<insertFrinshipQry.lastError();
        }
    }
    return "Friendship added!";
}
QString deleteFriendship(QString userId1,QString userId2){

    QSqlQuery deleteFrinshipQry;
    deleteFrinshipQry.prepare("DELETE FROM \"Friendships\" WHERE (\"UserId\"=:userId1 AND \"FriendId\"=:userId2) OR (\"UserId\"=:userId2 AND \"FriendId\"=:userId1)");
    deleteFrinshipQry.bindValue(":userId1",userId1.toInt());
    deleteFrinshipQry.bindValue(":userId2",userId2.toInt());
    if (!deleteFrinshipQry.exec())
        qDebug() <<deleteFrinshipQry.lastError();

    deleteFrinshipQry.prepare("DELETE FROM \"Groups\" WHERE \"MembersIds\"=:group1 or \"MembersIds\"=:group2");
    deleteFrinshipQry.bindValue(":group1","{"+userId1+","+userId2+"}");
    deleteFrinshipQry.bindValue(":group2","{"+userId2+","+userId1+"}");
    if (!deleteFrinshipQry.exec())
        qDebug() <<deleteFrinshipQry.lastError();

    return "Friedship deleted";
}

QString getAllFriendRequests(int userId){
    QString allFriendRequests;
    QSqlQuery getAllFriendRequestsQry;
    getAllFriendRequestsQry.prepare("SELECT * FROM \"Users\" u WHERE \"UserId\" IN (SELECT \"UserId\" FROM \"Friendships\" WHERE \"FriendId\"=:userId AND u.\"UserId\" NOT IN (SELECT \"FriendId\" From \"Friendships\" WHERE \"UserId\"=:userId))");
    getAllFriendRequestsQry.bindValue(":userId",userId);
    if (getAllFriendRequestsQry.exec()){
        while(getAllFriendRequestsQry.next())
            allFriendRequests=allFriendRequests     +getAllFriendRequestsQry.value(0).toString()+" "
                                                    +getAllFriendRequestsQry.value(1).toString()+" "
                                                    +getAllFriendRequestsQry.value(2).toString()+" "
                                                    +getAllFriendRequestsQry.value(3).toString()+" "
                                                    +getAllFriendRequestsQry.value(4).toString()+" "
                                                    +getAllFriendRequestsQry.value(5).toString()+" "
                                                    +getAllFriendRequestsQry.value(6).toString()+" ";
    }
    else{
        qDebug() <<getAllFriendRequestsQry.lastError();
    }
    return QString(allFriendRequests);
}

QString createGroup(QString groupName, QString groupDetails){
    QSqlQuery insertGroup;
    insertGroup.prepare("INSERT INTO \"Groups\" values(nextval('\"Groups_GroupId_seq\"'::regclass),:groupName,current_date,:membersIds)");
    insertGroup.bindValue(":membersIds",groupDetails);
    insertGroup.bindValue(":groupName",groupName);
    if (!insertGroup.exec())
        qDebug() <<insertGroup.lastError();

    return "Group created";
}
QString getGroups(int userId){
    QString groupsDetails;
    QSqlQuery getGroupsQry;
    getGroupsQry.prepare("SELECT * FROM \"Groups\" WHERE CARDINALITY(\"MembersIds\")!=2 AND :userId=ANY(\"MembersIds\")");
    getGroupsQry.bindValue(":userId",userId);
    if (getGroupsQry.exec()){
        while(getGroupsQry.next())
            groupsDetails=groupsDetails +getGroupsQry.value(0).toString()+" "
                                        +getGroupsQry.value(1).toString()+" "
                                        +getGroupsQry.value(2).toString()+" "
                                        +getGroupsQry.value(3).toString()+" ";
    }
    else
        qDebug() <<getGroupsQry.lastError();
    return QString(groupsDetails);
}
#endif // TOOLS_H
