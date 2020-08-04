// testbuf_serv.c
#include "unp.h"

int main(int argc, char *argv[]){
    int fd = Socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(fd, (SA*)&servaddr, sizeof(servaddr));
    char buf[1000000];
    socklen_t len = sizeof(cliaddr);
    int n = Recvfrom(fd, buf, sizeof(buf), 0, (SA*)&cliaddr, &len);
    printf("receive %d bytes\n", n);
}