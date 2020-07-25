// Accept.c
#include "unp.h"

int Accept(int fd, struct sockaddr *addr, socklen_t *addrlen){
    int clifd = accept(fd, addr, addrlen);
    if(clifd == -1) {
        perror("accept error"); exit(1);
    }
    return clifd;
}
