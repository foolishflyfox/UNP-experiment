// myecho.c
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) { perror("socket error"); return 1; }
    if(listen(sockfd, 16)==-1){
        perror("listen error"); return 1;
    }
    // 获取系统分配的套接字地址与端口号
    struct sockaddr_in addr;
    socklen_t socklen = sizeof(addr);
    if(getsockname(sockfd, (struct sockaddr*)&addr, &socklen)==-1){
        perror("getsockname error"); return 1;
    }
    // 打印套接字地址与端口号
    char buf[INET_ADDRSTRLEN];
    printf("Server IP: %s\n", inet_ntop(AF_INET, 
        &addr.sin_addr.s_addr, buf, INET_ADDRSTRLEN));
    printf("Server Port: %d\n", ntohs(addr.sin_port));
    // 回显服务
    struct sockaddr cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    int clifd = accept(sockfd, &cliaddr, &clilen), n;
    if(clifd < 0) { perror("accept error"); return 1; }
    char data[256];
    while((n = read(clifd, data, 256))>0){
        write(clifd, data, n);
    }
}

