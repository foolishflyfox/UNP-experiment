// dgclitimeo2.c
#include "unp.h"

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen){
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    Setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    while(Fgets(recvline, MAXLINE, fp) != NULL){
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        if(n < 0){
            if(errno == EWOULDBLOCK){
                fprintf(stderr, "socket timeout\n");
                continue;
            }else{
                perror("recvfrom error"); exit(1);
            }
        }
        recvline[n] = '\0';
        fputs(recvline, stdout);
    }
}
