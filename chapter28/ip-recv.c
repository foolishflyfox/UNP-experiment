// ip-recv.c
#include "tools.h"

int main(int argc, char *argv[]){
    char s_err[256];
    snprintf(s_err, 256, "Usage: %s [dst-host]\n", argv[0]);
    in_addr_t dstaddr = 0;
    if(argc > 1){
        // 可以添加IP地址参数
        if(GetInAddrByName(argv[1], &dstaddr)==-1){
            fprintf(stderr, "dst %s is invalidate", argv[1]);
            exit(1);
        }
    }
    // 创建套接字
    unsigned char recvbuf[BSZ];
    struct sockaddr_in peeraddr = {0, AF_INET};
    peeraddr.sin_addr.s_addr = dstaddr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if(-1==sockfd){ perror("socket error"); exit(1); }
    // 接收数据
    int cc = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0,
        (struct sockaddr*)&peeraddr, &addrlen);
    if(cc < 0) { perror("recvfrom error"); exit(1); }

    for(int i=0; i<cc; ++i){
        printf("%02x%c", recvbuf[i], " \n"[(i+1)%16==0]);
    }
}

