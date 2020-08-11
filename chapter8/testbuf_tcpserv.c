// testbuf_tcpserv.c
#include "unp.h"

int main(int argc, char *argv[]){
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(fd, (SA*)&servaddr, sizeof(servaddr));
    Listen(fd, LISTENQ);
    char buf[1000000];
    socklen_t len = sizeof(cliaddr);
    int clifd = Accept(fd, (SA*)&cliaddr, &len);
    int n = read(clifd, buf, sizeof(buf));
    if(n < 0) { perror("read error"); exit(1); }
    printf("receive %d bytes\n", n);
}