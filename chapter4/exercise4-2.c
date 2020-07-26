// exercise4-2.c
#include "unp.h"
#include <limits.h>

int main(){
    int fd[2];
    pipe(fd);
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(20001);
    pid_t pid = fork();
    if(pid < 0) { perror("fork error"); exit(1); }
    if(pid > 0){
        close(fd[0]);
        int sockfd = Socket(AF_INET, SOCK_STREAM, 0), clifd;
        Bind(sockfd, (SA*)&addr, sizeof(addr));
        Listen(sockfd, LISTENQ);
        close(fd[1]);
        while((clifd = Accept(sockfd, NULL, NULL)) > 0){
            close(clifd);
        }
    }else{
        close(fd[1]);
        unsigned char ports[65536];
        int clifd;
        struct sockaddr_in cliaddr;
        socklen_t addrlen;
        bzero(ports, sizeof(ports));
        read(fd[0], NULL, 1); sleep(1);
        while((clifd = socket(AF_INET, SOCK_STREAM, 0)) > 0){
            if(connect(clifd, (SA*)&addr, sizeof(addr)) < 0){
                break;
            }else{
                getsockname(clifd, (SA*)&cliaddr, &addrlen);
                int port = ntohs(cliaddr.sin_port);
                printf("port = %d\n", port);
                if(ports[port]) break; 
                else ports[port] = 1;
                close(clifd);
            }
        }
    }
}

