// readn.c
#include "unp.h"

ssize_t readn(int fd, void *buff, size_t nbytes){
    ssize_t nread = 0;
    size_t nleft = nbytes;
    char *ptr = buff;
    while(nleft > 0){
        if((nread = read(fd, ptr, nleft))<0){
            if(errno == EINTR) nread = 0;
            else return -1;
        }else if(nread == 0){
            break;
        }else{
            nleft -= nread;
            ptr += nread;
        }
    }
    return nbytes-nleft;
}

