#include "unp.h"

int Inet_pton(int family, const char* strptr, void* addrptr){
    int n = inet_pton(family, strptr, addrptr);
    if (n < 0)
        err_sys("inet_pton error for %s", strptr);
    else if (n == 0)
        err_quit("inet_pton error for %s", strptr);
    return n;
}
