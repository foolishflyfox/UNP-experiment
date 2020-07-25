// Socket.c
#include "unp.h"

int Socket(int family, int type, int protocol){
    int fd = socket(family, type, protocol);
    if(fd < 0) {
        perror("socket error");
        exit(1);
    }
    return fd;
}

