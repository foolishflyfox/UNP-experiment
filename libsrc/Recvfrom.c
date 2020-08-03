// Recvfrom.c
#include "unp.h"

ssize_t Recvfrom(int fd, void *buff, size_t nbytes, int flags,
                struct sockaddr *sa, socklen_t *salenptr){
    ssize_t n = recvfrom(fd, buff, nbytes, flags, sa, salenptr);
    if(n < 0) {
        perror("recvfrom error"); exit(1);
    }
    return n;
}
