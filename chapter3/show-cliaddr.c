// show-cliaddr.c
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char *argv[]){
    if(argc!=3){
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        exit(1);
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) { perror("socket error"); exit(1); }
    struct sockaddr_in addr, cli;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &addr.sin_addr.s_addr);
    addr.sin_port = htons(atoi(argv[2]));
    if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr))<0){
        perror("connect error"); exit(1);
    }
    socklen_t len = sizeof(cli);
    if(getsockname(sockfd, (struct sockaddr*)&cli, &len) < 0){
        perror("getsockname error"); exit(1);
    }
    char buf[INET_ADDRSTRLEN];
    printf("client IP: %s, Port: %d\n", 
        inet_ntop(AF_INET, &cli.sin_addr.s_addr, buf, sizeof(buf)),
        htons(cli.sin_port));
}

