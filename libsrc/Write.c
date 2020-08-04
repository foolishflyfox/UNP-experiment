// Write.c
#include "unp.h"

void Write(int fd, const void *ptr, size_t nbytes){
    if(write(fd, ptr, nbytes) != nbytes){
        perror("write error"); exit(1);
    }
}
