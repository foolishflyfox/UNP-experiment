// Read.c
#include "unp.h"

ssize_t Read(int fd, void *ptr, size_t nbytes){
    ssize_t n = read(fd, ptr, nbytes);
    if(n == -1){
        perror("read error"); exit(1);
    }
    return n;
}
