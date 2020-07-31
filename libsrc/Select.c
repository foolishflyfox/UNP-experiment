// Select.c
#include "unp.h"

int Select(int maxfdp1, fd_set *rset, fd_set *wset, fd_set *eset, 
            struct timeval *timeout){
    int n = select(maxfdp1, rset, wset, eset, timeout);
    if(n < 0){
        perror("select error"); exit(1);
    }
    return n;
}
