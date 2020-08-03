// udpcli01.c
#include "unp.h"

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc!=2){ 
        fprintf(stderr, "Usage: %s <IP>\n", argv[0]); exit(1); 
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));
    exit(0);
}
