// testbuf_cli.c
#include "unp.h"

int main(int argc, char *argv[]){
    int fd = Socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    if(argc != 3){
        fprintf(stderr, "Usage: %s <IP> <nbytes>\n", argv[0]);
        exit(1);
    }
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    int n = atoi(argv[2]);
    char *buf = malloc(n);
    if(buf == NULL) { perror("malloc error"); exit(1); }
    Sendto(fd, buf, n, 0, (SA*)&servaddr, sizeof(servaddr));
}

