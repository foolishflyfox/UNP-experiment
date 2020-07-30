// libsrc/chapter6/strcli1.c
#include "unp.h"

void str_cli(FILE *fp, int sockfd){
    int maxfdp1, fpfd = fileno(fp), n;
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
        if(FD_ISSET(fpfd, &rset))
        {
            if(Fgets(sendline, sizeof(sendline), fp)==NULL){
                return;
            }
            written(sockfd, sendline, strlen(sendline));
        }
        if(FD_ISSET(sockfd, &rset))
        {
            if((n = read(sockfd, recvline, sizeof(recvline)))<=0){
                fprintf(stderr, "%s str_cli: server terminated prematurely\n",
                            getcurtime());
                exit(11);
            }
            recvline[n] = '\0';
            printf("%s", recvline);
        }
    }
}

