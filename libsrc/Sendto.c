// Sendto.c
#include "unp.h"

void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
                const struct sockaddr *sa, socklen_t salen){
    if(sendto(fd, ptr, nbytes, flags, sa, salen)!=nbytes){
        perror("sendto error"); exit(1);
    }
}
