// hostent.c
#include "unp.h"

int main(int argc, char *argv[]){
    char *ptr, **pptr;
    char str[INET_ADDRSTRLEN];
    struct hostent *hptr;
    while(--argc > 0){
        ptr = *++argv;
        if((hptr = gethostbyname(ptr))==NULL){
            fprintf(stderr, "gethostbyname error for host: %s: %s\n",
                ptr, hstrerror(h_errno));
            continue;
        }
        printf("official hostname: %s\n", hptr->h_name);
        for(pptr = hptr->h_aliases; *pptr!=NULL; ++pptr)
            printf("    alias: %s\n", *pptr);
        switch(hptr->h_addrtype){
            case AF_INET:
                for(pptr = hptr->h_addr_list; *pptr!=NULL; pptr++)
                    printf("    address: %s\n",
                        Inet_ntop(AF_INET, *pptr, str, sizeof(str)));
                break;
            default:
                fprintf(stderr, "unknow address type\n");
                break;
        }
    }
}


