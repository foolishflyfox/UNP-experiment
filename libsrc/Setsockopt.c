// Setsockopt.c
#include "unp.h"

void Setsockopt(int fd, int level, int optname, const void*optval, socklen_t optlen){
    if(setsockopt(fd, level, optname, optval, optlen) < 0){
        perror("setsockopt error"); exit(1);
    }
}
