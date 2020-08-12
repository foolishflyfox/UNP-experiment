// ip-recv.c
#include "tools.h"

int main(int argc, char *argv[]){
    char s_err[256];
    snprintf(s_err, 256, "Usage: %s [dst-host]\n", argv[0]);
    unsigned char recvbuf[BSZ];
    struct sockaddr_in peeraddr;
    socklen_t addrlen = sizeof(peeraddr);
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if(sockfd < 0){ perror("socket error"); exit(1); }
    setuid(getuid());
    if(argc > 1){
        // 可以添加IP地址参数
        struct hostent *hp;
        if((hp = gethostbyname(argv[1]))!=NULL)
            memcpy(&peeraddr.sin_addr, hp->h_addr_list[0], hp->h_length);
        else{
            fputs(s_err, stderr);  exit(1);
        }
    }
    int cc = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0,
        (struct sockaddr*)&peeraddr, &addrlen);
    if(cc < 0) { perror("recvfrom error"); exit(1); }
    for(int i=0; i<cc; ++i){
        printf("%02x%c", recvbuf[i], " \n"[(i+1)%16==0]);
    }
}

