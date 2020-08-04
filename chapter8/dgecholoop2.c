// dgecholoop2.c
#include "unp.h"

static int count;
static void recvfrom_int(int signo){
    printf("\nreceived %d datagrams\n", count);
    exit(0);
}
void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen){
    socklen_t len;
    char mesg[MAXLINE];
    int n = 131072*2;
    Signal(SIGINT, recvfrom_int);
    if(-1 == setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n))){
        perror("setsockopt error"); exit(1);
    }
    for( ; ; ){
        len = clilen;
        Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        count++;
    }
}
