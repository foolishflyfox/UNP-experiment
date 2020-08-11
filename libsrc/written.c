// written.c
#include "unp.h"
ssize_t written(int fd, const void *buff, size_t nbytes){
    ssize_t nwritten = 0;
    size_t nleft = nbytes;
    const char *ptr = buff;
    while(nleft > 0){
        if((nwritten = write(fd, ptr, nleft)) <= 0){
            if(nwritten < 0 && errno == EINTR) nwritten = 0;
            else return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return nbytes;
}
