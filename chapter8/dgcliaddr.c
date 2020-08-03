// dgcliaddr.c
#include "unp.h"

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen){
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];
    socklen_t len;
    struct sockaddr *preply_addr = malloc(servlen);
    bzero(preply_addr, servlen);
    if(preply_addr == NULL) { perror("malloc error"); exit(1); }
    while(Fgets(sendline, MAXLINE, fp)!=NULL){
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        len = servlen;
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
        preply_addr->sa_len = pservaddr->sa_len;
        if(len!=servlen || memcmp(pservaddr, preply_addr, len)!=0){
            printf("reply from %s (ignored)\n", Sock_ntop(preply_addr, len));
            continue;
        }
        recvline[n] = '\0';
        fputs(recvline, stdout);
    }
}
