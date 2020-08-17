// udp-tool.c
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc!=3) {
        fprintf(stderr, "Usage: %s <IP> <Port>\n", argv[0]); exit(1);
    }
    char buf[1024];
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd==-1){ perror("socket error"); exit(1); }
    struct sockaddr_in addr, local;
    bzero(&addr, sizeof(addr));
    bzero(&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    if(-1==bind(sockfd, (struct sockaddr*)&local, sizeof(local))){
        perror("bind error"); exit(1);
    }
    socklen_t addrlen = sizeof(local);
    if(-1==getsockname(sockfd, (struct sockaddr*)&local, &addrlen)){
        perror("getsockname error"); exit(1);
    }else{
        printf("LOCAL PORT = %d\n", ntohs(local.sin_port));
    }
    int on = 1;
    if(-1==setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on))){
        perror("setsockopt error"); exit(1);
    }
    pid_t pid = fork();
    if(pid < 0) { perror("fork error"); exit(1); }
    if(pid){
        addr.sin_family = AF_INET;
        if(-1==inet_pton(AF_INET, argv[1], &addr.sin_addr)){
            perror("inet_pton error"); exit(1);
        }
        addr.sin_port = htons(atoi(argv[2]));
        while(fgets(buf, sizeof(buf), stdin)!=NULL){
            if(-1 == sendto(sockfd, buf, strlen(buf), 0, 
                (struct sockaddr*)&addr, sizeof(addr))){
                perror("sendto error"); 
            }
        }
    }else{
        int n = 0;
        addrlen = sizeof(addr);
        char strip[INET_ADDRSTRLEN];
        while(1){
            if(-1!=(n = recvfrom(sockfd, buf, sizeof(buf)-1, 0, 
                (struct sockaddr*)&addr, &addrlen))){
                buf[n] = 0;
                printf("%s.%d: %s\n", inet_ntop(AF_INET, &addr.sin_addr, 
                    strip, sizeof(strip)), ntohs(addr.sin_port), buf);
                bzero(&addr, sizeof(addr));
                addrlen = sizeof(addr);
            }
        }
    }
}

