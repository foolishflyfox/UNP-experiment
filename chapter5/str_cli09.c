// str_cli09.c
#include "unp.h"
#include "sum.h"
void str_cli(FILE *fp, int sockfd){
    char sendline[MAXLINE];
    struct args args;
    struct result result;
    while(Fgets(sendline, MAXLINE, fp) != NULL){
        if(sscanf(sendline, "%ld%ld", &args.arg1, &args.arg2)!=2){
            printf("invalid input: %s", sendline);
            continue;
        }
        written(sockfd, &args, sizeof(args));
        if(readn(sockfd, &result, sizeof(result))==0){
            perror("str_cli: server terminated permaturely");
            exit(1);
        }
        printf("%ld\n", result.sum);
    }
}
