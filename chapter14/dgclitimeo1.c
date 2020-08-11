// dgclitimeo1.c
#include "unp.h"

int readable_timeo(int fd, int sec);
void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen){
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];
    while(Fgets(sendline, MAXLINE, fp) != NULL){
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        int res = readable_timeo(sockfd, 5);
        if(res<0) { perror("select error"); exit(1); }
        else if(res==0) { fprintf(stderr, "socket timeout\n"); }
        else {
            n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
            recvline[n] = '\0';  // null terminate
            fputs(recvline, stdout);
        }
    }
}
