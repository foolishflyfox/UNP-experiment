// tcpcli01.c
#include "unp.h"

const char* getcurtime(){
    static char strtm[64];
    time_t t = time(NULL);
    strftime(strtm, sizeof(strtm), "%F %T", localtime(&t));
    return strtm;
}

int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <IP>\n", argv[0]); exit(1);
    }
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servsock;
    char buf[MAXLINE];
    bzero(&servsock, sizeof(servsock));
    servsock.sin_family = AF_INET;
    servsock.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servsock.sin_addr);
    Connect(sockfd, (SA*)&servsock, sizeof(servsock));
    written(sockfd, "hello!\n", 7);
    Readline(sockfd, buf, sizeof(buf));
    printf("%s: GET %s", getcurtime(), buf);
    sleep(10);  // 等待服务器被关闭
    printf("%s: write data\n", getcurtime());
    written(sockfd, "abc\n", 4);
    printf("%s: after written\n", getcurtime());
    sleep(10);
    printf("%s: read data\n", getcurtime());
    Readline(sockfd, buf, sizeof(buf));
    printf("%s: after readline\n", getcurtime());
}

