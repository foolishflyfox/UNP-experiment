// str_echo.c
#include "unp.h"

void str_echo(int sockfd){
    ssize_t n;
    char buf[MAXLINE];
again:
    while ((n = read(sockfd, buf, MAXLINE)) > 0){
        written(sockfd, buf, n);
        if(n < 0 && errno==EINTR)
            goto again;
        else if (n < 0){
            perror("str_echo: read error"); exit(1);
        }
    }
}
