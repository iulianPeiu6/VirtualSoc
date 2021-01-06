#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>


#define PORT 2728
#define ADDR "127.0.0.1"
extern int errno;


using namespace std;

int setupClientConn(){
    int sd;
    struct sockaddr_in server;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("[client] Eroare la socket().\n");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ADDR);
    server.sin_port = htons(PORT);

    if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1){
        perror("[client]Eroare la connect().\n");
        exit(EXIT_FAILURE);
    }

    return sd;
}
