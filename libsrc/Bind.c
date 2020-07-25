// Bind.c
#include "unp.h"

void Bind(int fd, const struct sockaddr *addr, socklen_t addrlen){
    if(-1==bind(fd, addr, addrlen)){
        perror("bind error"); exit(1);
    }
}

