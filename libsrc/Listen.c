// Listen.c
#include "unp.h"

void Listen(int fd, int backlog){
    char *ptr;
    /* can override 2nd argument with environment variable */
    if((ptr = getenv("LISTENQ"))!=NULL)
        backlog = atoi(ptr);
    if(listen(fd, backlog)<0){
        perror("listen error");
        exit(1);
    }
}

