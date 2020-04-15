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

void Bind(int fd, const struct sockaddr *sa, socklen_t salen){
    if(bind(fd, sa, salen)==-1)
        err_sys("bind error");
}

void Listen(int fd, int backlog){
    if(listen(fd, backlog)==-1)
        err_sys("listen error");
}

int Accept(int fd, struct sockaddr* sa, socklen_t* salen){
    int n = accept(fd, sa, salen);
    if(n < 0)
        err_sys("accept error");
    return n;
}
