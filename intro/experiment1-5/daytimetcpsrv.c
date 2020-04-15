// intro/experiment1-5/daytimetcpsrv.c
#include "unp.h"

int main(int argc, char* argv[]){
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    // 服务器使用 0.0.0.0 地址，其实可以直接赋值为0
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    Listen(sockfd, 16);

    while(1){
        int connfd = Accept(sockfd, (struct sockaddr*)NULL, 0);
        time_t tm = time(NULL);
        const char* str_tm = ctime(&tm);
        Write(connfd, str_tm, strlen(str_tm));
        Close(connfd);
    }
}



