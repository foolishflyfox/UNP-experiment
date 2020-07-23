// 3-13.c
#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
const char* inet_ntop(int family, const void *addrptr, char *strptr, size_t len){
    const u_char *p = (const u_char *)addrptr;
    if(family == AF_INET){
        char temp[INET_ADDRSTRLEN];
        snprintf(temp, sizeof(temp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
        if(strlen(temp) >= len){
            errno = ENOSPC;
            return NULL;
        }
        strcpy(strptr, temp);
        return strptr;
    }
    errno = EAFNOSUPPORT;
    return NULL;
}
