// dgclitimeo3.c
#include "unp.h"

static void sig_alrm(int signo) { return; }

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen){
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];
    Signal(SIGALRM, sig_alrm);
    while(Fgets(sendline, MAXLINE, fp)!=NULL){
        Sendto(sockfd, sendline, strlen(sendline), 0, (SA*)pservaddr, servlen);
        alarm(5);
        if((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL))<0){
            if(errno==EINTR) fprintf(stderr, "socket timeout\n");
            else{
                perror("recvfrom error"); exit(1);
            }
        }else{
            alarm(0);
            recvline[n] = '\0';
            fputs(recvline, stdout);
        }
    }
}

