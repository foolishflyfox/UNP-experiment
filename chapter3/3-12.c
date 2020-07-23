// 3-12.c
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
int inet_pton(int family, const char *strptr, void *addrptr){
    if(family==AF_INET){
        struct in_addr in_val;
        if(inet_aton(strptr, &in_val)){
            memcpy(addrptr, &in_val, sizeof(in_val));
            return 1;
        }
        return 0;
    }
    errno = EAFNOSUPPORT;
    return -1;
}
