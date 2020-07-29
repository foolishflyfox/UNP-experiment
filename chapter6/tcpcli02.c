// tcpcli02.c
#include "unp.h"

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc!=2){
        fprintf(stderr, "usage: %s <IPaddress>\n", argv[0]);
        exit(1);
    }
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);     /* do it all */
    exit(0);
}