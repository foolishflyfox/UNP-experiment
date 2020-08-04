// connect_effect.c
#include "unp.h"

#define LOOPS 1000000
int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <IP>\n", argv[0]); exit(1);
    }
    int fd = Socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
#ifdef USE_CONNECT
    Connect(fd, (SA*)&servaddr, sizeof(servaddr));
#endif
    printf("t0: %s\n", getcurtime());
    for(int i=0; i<LOOPS; ++i){
#ifdef USE_CONNECT
        if(-1==write(fd, "a", 1)){
            perror("write error"); exit(1);
        }
#else
        Sendto(fd, "a", 1, 0, (SA*)&servaddr, sizeof(servaddr));
#endif
    }
    printf("t1: %s\n", getcurtime());
}

