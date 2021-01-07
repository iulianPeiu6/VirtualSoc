#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <QtDebug>
#include "BusinessLogic.h"
#include <QtSql>

#define PORT 2728
#define MSG_LEN 25000

#define QUIT 0
#define USER_REGISTRATION 1
#define USER_AUTHENTICATION 2
#define UPDATE_USER 3
#define USER_LOGOUT 4
#define DELETE_USER 5
#define GET_ALL_USERS 6
#define GET_ALL_FRIENDS 7
#define GET_GROUP_MESSAGES 8
#define SEND_MSG_TO_GROUP 9
#define GET_GROUP2_DETAILS 10
#define GET_CURRENT_USER_POSTS 11
#define DELETE_POST 12
#define ADD_LIKE_TO_POST 13
#define CREATE_POST 14
#define GET_FRIENDSHIP_TYPE 15
#define ADD_FRIENDSHIP 16
#define DELETE_FRIENDSHIP 17
#define GET_FRIEND_REQUEST 18
#define CREATE_GROUP 19
#define GET_USER_GROUPS 20
#define GET_ALL_PUBLIC_USERS 21
#define GET_ALL_PUBLIC_USER_POSTS 22

extern int errno;

char *conv_addr(struct sockaddr_in address)
{
    static char str[25];
    char port[7];

    strcpy(str, inet_ntoa(address.sin_addr));
    bzero(port, 7);
    sprintf(port, ":%d", ntohs(address.sin_port));
    strcat(str, port);
    return (str);
}

int setupServer(){
    struct sockaddr_in server;
    int sd,optval = 1;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("[server] Eroare la socket().\n");
        exit(EXIT_FAILURE);
    }

    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1){
        perror("[server] Eroare la bind().\n");
        exit(EXIT_FAILURE);
    }

    if (listen(sd, 5) == -1){
        perror("[server] Eroare la listen().\n");
        exit(EXIT_FAILURE);
    }

    return sd;

}

char* getResponse(char msg[MSG_LEN]){
    QString msg_text=msg;
    QStringList cmd_prop=msg_text.split(QLatin1Char(' '));
    int cmd=cmd_prop[0].toInt();

    switch(cmd) {

    case USER_REGISTRATION:
        msg=userRegistration(cmd_prop[1],cmd_prop[2]).toLocal8Bit().data();
        break;
    case USER_AUTHENTICATION:
        msg=userAuthentication(cmd_prop[1],cmd_prop[2]).toLocal8Bit().data();
        break;
    case UPDATE_USER:
        msg=userUpdate(cmd_prop[1],cmd_prop[2],cmd_prop[3],cmd_prop[4]).toLocal8Bit().data();
        break;
    case USER_LOGOUT:
        msg=userLogout(cmd_prop[1]).toLocal8Bit().data();
        break;
    case DELETE_USER:
        msg=deleteUser(cmd_prop[1].toInt()).toLocal8Bit().data();
        break;
    case GET_ALL_USERS:{
        QString allUsers=getAllUsers(cmd_prop[1]);
        for (int i=0;i<allUsers.length();i++)
            msg[i]=allUsers.at(i).toLatin1();
        break;
    }
    case GET_ALL_FRIENDS:{
        QString allFriendsUsers=getAllFriends(cmd_prop[1]);
        for (int i=0;i<allFriendsUsers.length();i++)
            msg[i]=allFriendsUsers.at(i).toLatin1();
        break;
    }
    case GET_GROUP_MESSAGES:{
        QString allGroupMsgs=getAllGroupMsgs(cmd_prop[1].toInt());
        for (int i=0;i<allGroupMsgs.length();i++)
            msg[i]=allGroupMsgs.at(i).toLatin1();
        break;
    }
    case SEND_MSG_TO_GROUP:{
        QString txt;
        for (int i=3;i<cmd_prop.count();i++)
            txt=txt+cmd_prop[i]+" ";
        msg=sendMsgToGroup(cmd_prop[1],cmd_prop[2],txt).toLocal8Bit().data();
        break;
    }
    case GET_GROUP2_DETAILS:
        msg=getGroup2Details(QVector<int>{cmd_prop[1].toInt(),cmd_prop[2].toInt()}).toLocal8Bit().data();
        break;
    case GET_CURRENT_USER_POSTS:{
        QString allPosts=getAllUserPosts(cmd_prop[1].toInt());
        for (int i=0;i<allPosts.length();i++)
            msg[i]=allPosts.at(i).toLatin1();
        break;
    }
    case DELETE_POST:
        msg=deletePost(cmd_prop[1].toInt()).toLocal8Bit().data();
        break;
    case ADD_LIKE_TO_POST:
        msg=addLikeToPost(cmd_prop[1].toInt()).toLocal8Bit().data();
        break;
    case CREATE_POST:{
        QString postDetails;
        for (int i=1;i<cmd_prop.count();i++)
            postDetails=postDetails+cmd_prop[i]+" ";
        QStringList cmd_prop=postDetails.split(QLatin1Char('~'));

        msg=createPost(cmd_prop[0],cmd_prop[1],cmd_prop[2],cmd_prop[3]).toLocal8Bit().data();
        break;
    }
    case GET_FRIENDSHIP_TYPE:
        msg=getFriendshipType(cmd_prop[1].toInt(),cmd_prop[2].toInt()).toLocal8Bit().data();
        break;
    case ADD_FRIENDSHIP:
        msg=addFriendship(cmd_prop[1].toInt(),cmd_prop[2].toInt(),cmd_prop[3].toInt()).toLocal8Bit().data();
        break;
    case DELETE_FRIENDSHIP:
        msg=deleteFriendship(cmd_prop[1],cmd_prop[2]).toLocal8Bit().data();
        break;
    case GET_FRIEND_REQUEST:
        msg=getAllFriendRequests(cmd_prop[1].toInt()).toLocal8Bit().data();
        break;
    case CREATE_GROUP:
        msg=createGroup(cmd_prop[1],cmd_prop[2]).toLocal8Bit().data();
        break;
    case GET_USER_GROUPS:
        msg=getGroups(cmd_prop[1].toInt()).toLocal8Bit().data();
        break;
    case GET_ALL_PUBLIC_USERS:{
        QString allPublicUsers=getAllPublicUsers().toLocal8Bit().data();
        for (int i=0;i<allPublicUsers.length();i++)
            msg[i]=allPublicUsers.at(i).toLatin1();
        break;
    }
    case GET_ALL_PUBLIC_USER_POSTS:{
        QString allPublicUserPosts=getAllPublicUserPosts(cmd_prop[1].toInt());
        for (int i=0;i<allPublicUserPosts.length();i++)
            msg[i]=allPublicUserPosts.at(i).toLatin1();
        break;
    }
    default:
        msg=cmd_prop[1].toLocal8Bit().data();
    }

    return msg;
}
bool sendResponse(int fd)
{
    int bytes;
    char msg[MSG_LEN];
    char* msgResp;

    bzero(msg,MSG_LEN);
    bytes = read(fd, msg, sizeof(msg));
    if (bytes < 0){
        perror("Eroare la read() de la client.\n");
        return true;
    }

    printf("[Client] %s\n", msg);
    fflush(stdout);

    msgResp=getResponse(msg);

    printf("[server] %s\n", msgResp);
    fflush(stdout);

    if (bytes && write(fd, msgResp, bytes) < 0){
        perror("[server] Eroare la write() catre client.\n");
        return true;
    }

    if (strcmp(msgResp,"quit")==0)
        return false;

    return true;

}

void writeResponses(int sd,int nfds, fd_set &actfds, fd_set &readfds){
    for (int fd = 0; fd <= nfds; fd++){
        if (fd != sd && FD_ISSET(fd, &readfds)){
            if (!sendResponse(fd)){
                printf("[server] S-a deconectat clientul cu descriptorul %d.\n", fd);
                fflush(stdout);
                close(fd);
                FD_CLR(fd, &actfds);
            }
        }
    }
}

void acceptClient(int sd, int &nfds, fd_set &actfds){
    struct sockaddr_in from;
    unsigned int len = sizeof(from);
    bzero(&from, sizeof(from));

    int client = accept(sd, (struct sockaddr *)&from, &len);

    if (client < 0)
    {
        perror("[server] Eroare la accept().\n");
        return ;
    }

    if (nfds < client)
        nfds = client;

    FD_SET(client, &actfds);

    printf("[server] S-a conectat clientul cu descriptorul %d, de la adresa %s .\n", client, conv_addr(from));
    fflush(stdout);
}
void handleClientsRequests(int sd){

    fd_set actfds,readfds;
    struct timeval tv;
    int nfds=sd;

    FD_ZERO(&actfds);
    FD_SET(sd, &actfds);

    tv.tv_sec = 1;
    tv.tv_usec = 0;

    nfds = sd;

    while (true){
        bcopy((char *)&actfds, (char *)&readfds, sizeof(readfds));

        if (select(nfds + 1, &readfds, NULL, NULL, &tv) < 0){
            perror("[server] Eroare la select().\n");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(sd, &readfds))
            acceptClient(sd,nfds,actfds);

        writeResponses(sd,nfds,actfds,readfds);
    }
}

void connectToDb(){
    QSqlDatabase db=QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("postgres");

    if (!db.open())
        qDebug() <<db.lastError();
}

int main(){

    int sd = setupServer();

    connectToDb();

    handleClientsRequests(sd);

    return 0;
}
