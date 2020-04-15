// intro/experiment1-4/wrapunix.c
#include "unp.h"

ssize_t Read(int fildes, void *buf, size_t nbyte){
    ssize_t n = read(fildes, buf, nbyte);
    if(n == -1){
        err_sys("read error");
    }
    return n;
}

