// Connect.c
#include "unp.h"

void Connect(int fd, const struct sockaddr *addr, socklen_t addrlen){
    if(-1==connect(fd, addr, addrlen)){
        perror("connect error"); exit(1);
    }
}

