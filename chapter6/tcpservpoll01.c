// tcpservpoll01.c
#include "unp.h"

int main(){
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct pollfd client[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    for(i=1; i<OPEN_MAX; ++i) client[i].fd = -1;
    maxi = 0;  // max index into client[] array
    for( ; ; ){
        nready = poll(client, maxi+1, INFTIM);
        if(client[0].revents & POLLRDNORM) { // new client connection
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);
            for(i=1; i<OPEN_MAX; i++)
                if(client[i].fd < 0){
                    client[i].fd = connfd; // save descriptor
                    break;
                }
            if(i == OPEN_MAX){
                fprintf(stderr, "too many clients\n"); exit(1);
            }
            client[i].events = POLLRDNORM;
            if(i > maxi) maxi = i;  // max index in client[] array
            if(--nready <= 0) continue; // no more readable descriptors
        }
        for(i=1; i<=maxi; ++i){ // check all clients for data
            if((sockfd = client[i].fd) < 0) continue;
            if(client[i].revents & (POLLRDNORM|POLLERR)){
                if((n=read(sockfd, buf, MAXLINE)) < 0){
                    if(errno == ECONNRESET){
                        // connection reset by client
                        close(sockfd);
                        client[i].fd = -1;
                    }else{
                        perror("read error"); exit(1);
                    }
                }else if(n==0){
                    // connection closed by client
                    close(sockfd);
                    client[i].fd = -1;
                }else{
                    written(sockfd, buf, n);
                }
                if(--nready <= 0) break;
            }
        }
    }
}
