// Fgets.c
#include "unp.h"

char* Fgets(char *ptr, int n, FILE *stream){
    char *rptr;
    if((rptr = fgets(ptr, n, stream))==NULL && ferror(stream)){
        perror("fgets error"); exit(1);
    }
    return rptr;
}
