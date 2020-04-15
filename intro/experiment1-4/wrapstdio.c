// intro/experiment1-4/wrapstdio.c
#include "unp.h"

int Fputs(const char *restrict s, FILE *restrict stream){
    int n = fputs(s, stream);
    if(n == EOF)
        err_sys("fputs error");
    return n;
}

