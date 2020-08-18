#include "ourhdr.h"

// 向 fd 写入 n 个字节
ssize_t writen(int fd, const void *vptr, size_t n){
    const char *ptr = vptr;
    size_t nleft = n;
    ssize_t nwritten;
    while(nleft > 0){
        if((nwritten = write(fd, ptr, nleft)) <= 0)
            return nwritten;
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}
