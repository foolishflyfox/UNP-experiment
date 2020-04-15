#include "unp.h"

ssize_t Read(int fildes, void *buf, size_t nbyte){
    ssize_t n = read(fildes, buf, nbyte);
    if(n == -1){
        err_sys("read error");
    }
    return n;
}

void Write(int fd, const void *buf, size_t nbyte){
    if(write(fd, buf, nbyte)!=nbyte)
        err_sys("write error");
}

void Close(int fd){
    if(close(fd)==-1)
        err_sys("close error");
}

