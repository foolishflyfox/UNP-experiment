// getservbyport-demo.c
#include "unp.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Usage: %s <port> [protoname]", argv[0]);
        exit(1);
    }
    const char *protoname = NULL;
    if(argc >=2 ) protoname = argv[2];
    struct servent *sptr = getservbyport(htons(atoi(argv[1])), protoname);
    if(sptr == NULL) exit(1);
    printf("%s (%s):%d\n", sptr->s_name, sptr->s_proto, htons(sptr->s_port));
    for(char **pptr = sptr->s_aliases; *pptr!=NULL; ++pptr){
        printf("    alias: %s\n", *pptr);
    }
}