// str_cli.c
#include "unp.h"

void str_cli(FILE *fp, int sockfd){
    char sendline[MAXLINE], recvline[MAXLINE];
    while(Fgets(sendline, MAXLINE, fp)!=NULL){
        written(sockfd, sendline, strlen(sendline));
        if(Readline(sockfd, recvline, MAXLINE)==0){
            perror("str_cli: server terminated prematurely");
            exit(1);
        }
        fputs(recvline, stdout);
    }
}

