// libsrc/chapter6/strcli2.c
#include "unp.h"

void str_cli(FILE *fp, int sockfd){
    int maxfdp1, fpfd = fileno(fp), n, stdineof = 0;
    fd_set rset;
    char sendline[MAXLINE], recvline[MAXLINE];
    FD_ZERO(&rset);
    maxfdp1 = (fpfd>sockfd?fpfd:sockfd)+1;
    for ( ; ; ){
        if(stdineof == 0) FD_SET(fpfd, &rset);
        FD_SET(sockfd, &rset);
        if(select(maxfdp1, &rset, NULL, NULL, NULL)==-1){
            if(errno == EINTR) continue;
            perror("select error"); exit(1);
        }
        if(FD_ISSET(fpfd, &rset)){
            if((n = read(fpfd, sendline, MAXLINE))==0){
                stdineof = 1;
                if(shutdown(sockfd, SHUT_WR)==-1){
                    perror("shutdown error"); exit(1);
                }
                FD_CLR(fpfd, &rset);
                continue;
            }
            written(sockfd, sendline, n);
        }
        if(FD_ISSET(sockfd, &rset)){
            if((n = read(sockfd, recvline, sizeof(recvline)))<0){
                fprintf(stderr, "%s str_cli: server terminated prematurely\n",
                            getcurtime());
                exit(11);
            }else if(n == 0){
                if(stdineof == 1) return;
                else {
                    fprintf(stderr, "str_cli: server terminated permaturely\n");
                    exit(1);
                }
            }
            write(fileno(stdout), recvline, n);
        }
    }
}

