// testbuf_tcpcli.c
#include "unp.h"

int main(int argc, char *argv[]){
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    if(argc != 3){
        fprintf(stderr, "Usage: %s <IP> <nbytes>\n", argv[0]);
        exit(1);
    }
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    Connect(fd, (SA*)&servaddr, sizeof(servaddr));
    int n = atoi(argv[2]);
    char *buf = malloc(n);
    if(buf == NULL) { perror("malloc error"); exit(1); }
    Write(fd, buf, n);
}

