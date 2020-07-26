// readline.c
#include "unp.h"

ssize_t readline(int fd, void *buff, size_t maxlen){
    ssize_t n, rc;
    char c, *ptr;
    ptr = buff;
    for(n = 1; n < maxlen; n++){
    again:
        if((rc = read(fd, &c, 1)) == 1){
            *ptr++ = c;
            if(c == '\n')
                break;
        }else if(rc == 0){
            *ptr = '\0';
            return n-1;
        }else{
            if(errno == EINTR) goto again;
            return -1;
        }
    }
    *ptr = '\0';
    return n;
}

ssize_t Readline(int fd, void *buff, size_t maxlen){
    ssize_t n;
    if((n = readline(fd, buff, maxlen)) < 0){
        perror("readline error"); exit(1);
    }
    return n;
}

