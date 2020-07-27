// 5-9.c
#include "unp.h"

int main(int argc, char *argv[]){
    int i, sockfd[5];
    struct sockaddr_in servaddr;
    if(argc != 2){
        fprintf(stderr, "Usage: %s <IPaddress>\n", argv[0]);
        exit(1);
    }
    for(i=0; i<5; i++){
        sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
        Connect(sockfd[i], (SA*)&servaddr, sizeof(servaddr));
    }
    str_cli(stdin, sockfd[0]);  /* do it all */
    exit(0);
}
