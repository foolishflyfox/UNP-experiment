// 5-14.c
#include "unp.h"

void str_cli2(FILE* fp, int sockfd){
    char sendline[MAXLINE], recvline[MAXLINE];
    while(Fgets(sendline, MAXLINE, fp)!=NULL){
        written(sockfd, sendline, 1);
        sleep(1);
        written(sockfd, sendline+1, strlen(sendline)-1);
        if(Readline(sockfd, recvline, MAXLINE)==0){
            perror("str_cli: server terminated permaturely");
            exit(1);
        }
        fputs(recvline, stdout);
    }
}
int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc!=2){
        fprintf(stderr, "usage: %s <IPaddress>\n", argv[0]);
        exit(1);
    }
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
    str_cli2(stdin, sockfd);     /* do it all */
    exit(0);
}


