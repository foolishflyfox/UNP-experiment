// dgecholoop1.c
#include "unp.h"

static int count;
static void recvfrom_int(int signo){
    printf("\nreceived %d datagrams\n", count);
    exit(0);
}
void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen){
    socklen_t len;
    char mesg[MAXLINE];
    Signal(SIGINT, recvfrom_int);
    for( ; ; ){
        len = clilen;
        Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        count++;
    }
}
