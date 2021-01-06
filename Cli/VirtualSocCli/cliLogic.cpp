#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QString>
#include <QtDebug>

#define MSG_LEN 25000

void closeConn(int sd){
    close(sd);
}

QString sendMsg(int sd,QString cmd){

    char msg[MSG_LEN];

    bzero(msg,MSG_LEN);
    strcpy(msg,cmd.toLocal8Bit().data());

    printf("[Client] %s\n",msg);
    fflush(stdout);
    if (write(sd, msg, MSG_LEN) <= 0)
        perror("[client]Eroare la write() spre server.\n");

    bzero(msg, MSG_LEN);
    if (read(sd, msg, MSG_LEN) < 0)
        perror("[client]Eroare la read() de la server.\n");

    printf("[Server] %s\n",msg);
    fflush(stdout);

    return msg;
}
