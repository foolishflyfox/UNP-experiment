// connect-demo.c
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <strings.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
    if(argc!=3){
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        exit(1);
    }
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &addr.sin_addr.s_addr);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) { perror("socket error"); exit(1); }
    time_t t0 = time(NULL);
    int result = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    time_t t1 = time(NULL);
    printf("connect use %d s\n", (int)(t1-t0));
    if(result==-1){
        perror("connect error"); return 1;
    }else{
        printf("connect success\n"); return 0;
    }
}

