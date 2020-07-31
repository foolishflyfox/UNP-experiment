// tcpservselect01.c
#include "unp.h"

int main(int argc, char* argv[]){
    int i, maxi, maxfd, listenfd, connfd, sockfd;
    int nready, client[FD_SETSIZE];
    ssize_t n;
    fd_set rset, allset;
    char buf[MAXLINE];
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    maxfd = listenfd;   /* initialize */
    maxi = -1;  /* index into client array */
    for(i=0; i<FD_SETSIZE; ++i) client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    for( ; ; ){
        rset = allset;  /* structure assignment */
        nready = Select(maxfd+1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(listenfd, &rset)){  // new client connection
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);
            for(i=0; i<FD_SETSIZE; i++){
                if(client[i] < 0){
                    client[i] = connfd;
                    break;
                }
            }
            if(i == FD_SETSIZE) {
                fprintf(stderr, "too many clients\n");
                exit(1);
            }
            FD_SET(connfd, &allset);  // add new descriptor to set
            if(connfd > maxfd) maxfd = connfd;  /* for select */
            if(i > maxi) maxi = i;  // max index in client[] array
            if(--nready <= 0) continue;
        }
        for(i=0; i<=maxi; i++){ // check all clients for data
            if((sockfd = client[i]) < 0) continue;
            if(FD_ISSET(sockfd, &rset)){
                if((n = read(sockfd, buf, MAXLINE)) < 0){
                    perror("read error"); exit(1);
                }else if(n == 0){
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }else
                    written(sockfd, buf, n);
                if(--nready <=0) break;
            }
        }
    }
}
