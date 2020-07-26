// inet_pton.c
#include "unp.h"

void Inet_pton(int family, const char *src, void *dst){
    if(-1==inet_pton(family, src, dst)){
        perror("inet_pton error"); exit(1);
    }
}
