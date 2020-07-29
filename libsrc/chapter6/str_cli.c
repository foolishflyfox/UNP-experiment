// libsrc/chapter6/str_cli.c
#include "unp.h"

void str_cli(FILE *fp, int sockfd){
    int maxfdp1, fpfd = fileno(fp);
    fd_set rset;
    char sendline[MAXLINE], recvline[MAXLINE];
    FD_ZERO(&rset);
    maxfdp1 = (fpfd>sockfd?fpfd:sockfd)+1;
    for ( ; ; ){
        FD_SET(fpfd, &rset);
        FD_SET(sockfd, &rset);
        if(select(maxfdp1, &rset, NULL, NULL, NULL)==-1){
            if(errno == EINTR) continue;
            perror("select error"); exit(1);
        }
        if(FD_ISSET(sockfd, &rset)){
            if(Readline(sockfd, recvline, sizeof(recvline))==0){
                fprintf(stderr, "%s str_cli: server terminated prematurely\n",
                            getcurtime());
                exit(1);
            }
            fprintf(stdout, "%s: %s", getcurtime(), recvline);
        }
        if(FD_ISSET(fpfd, &rset)){
            if(Fgets(sendline, sizeof(sendline), fp)==NULL)
                return;
            written(sockfd, sendline, strlen(sendline));
        }
    }
}

