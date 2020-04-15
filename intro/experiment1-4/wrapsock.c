// intro/experiment1-4/wrapsock.c
#include "unp.h"

int Socket(int family, int type, int protocol){
    int n;
    if ((n = socket(family, type, protocol)) < 0)
        err_sys("socket error");
    return n;
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen){
    if (connect(fd, sa, salen) < 0)
        err_sys("connect error");
}
