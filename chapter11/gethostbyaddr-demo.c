// gethostbyaddr-demo.c
#include "unp.h"

int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <IP>\n", argv[0]);
        exit(1);
    }
    struct in_addr addr;
    Inet_pton(AF_INET, argv[1], &addr);
    struct hostent *hptr = gethostbyaddr(&addr, sizeof(addr), AF_INET);
    if(hptr == NULL){
        fprintf(stderr, "gethostbyaddr error for host: %s: %s\n",
            argv[1], hstrerror(h_errno));
        exit(1);
    }
    char **pptr, str[INET_ADDRSTRLEN];
    printf("official hostname: %s\n", hptr->h_name);
    for(pptr = hptr->h_aliases; *pptr!=NULL; ++pptr)
        printf("    alias: %s\n", *pptr);
    switch(hptr->h_addrtype){
        case AF_INET:
            pptr = hptr->h_addr_list;
            for(; *pptr!=NULL; pptr++)
                printf("    address: %s\n",
                    Inet_ntop(AF_INET, *pptr, str, sizeof(str)));
            break;
        default:
            fprintf(stderr, "unknow address type\n");
            break;
    }
}
