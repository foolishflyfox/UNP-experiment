// Inet_ntop.c
#include "unp.h"

const char* Inet_ntop(int family, const void *addrptr, char *strptr, size_t len){
    const char *ptr = NULL;
    if(strptr == NULL){
        fprintf(stderr, "NULL 3rd argument to inet_ntop");
        exit(1);
    }
    if((ptr = inet_ntop(AF_INET, addrptr, strptr, len))==NULL){
        perror("inet_ntop error");
        exit(1);
    }
    return ptr;
}
