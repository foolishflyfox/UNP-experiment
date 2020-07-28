// str_echo08.c
#include "unp.h"
void str_echo(int sockfd){
    long arg1, arg2;
    ssize_t n;
    char line[MAXLINE];
    for( ; ; ){
        if((n = Readline(sockfd, line, MAXLINE)) == 0)
            return;
        if(sscanf(line, "%ld %ld", &arg1, &arg2)==2)
            snprintf(line, sizeof(line), "%ld\n", arg1+arg2 );
        else
            snprintf(line, sizeof(line), "input error\n");
        n = strlen(line);
        written(sockfd, line, n);
    }
}

