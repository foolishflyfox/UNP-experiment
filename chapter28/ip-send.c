// ip-send.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h>
#include <netinet/ip.h>

// 可以发送的最大数据量
#ifndef BSZ
#define BSZ 4096
#endif

static inline int TOHEX_VALUE(char c) {
    if(c<='f' && c>='a') c = 10+c-'a';
    else if(c<='F' && c>='A') c = 10+c-'A';
    else if(c<='9' && c>='0') c -= '0';
    else c = 0xff;
    return c;
}
static inline int ISBLANK_CHAR(char c){
    return (c==' ' || c=='\t' || c=='\n');
}

int main(int argc, char *argv[]){
    char c, c1, c2, srcip[INET_ADDRSTRLEN], dstip[INET_ADDRSTRLEN];
    srcip[0] = dstip[0] = '\0';
    char s_err[256];
    snprintf(s_err, sizeof(s_err), "Usage: %s [data-file]", argv[0]);
    // int proto = IPPROTO_IP;
    const char *datafile = NULL;
    FILE* fp = stdin;
    
    if(argc==2){
        datafile = argv[1];
        if(access(datafile, R_OK)==-1){ perror("access error"); exit(1); }
        if((fp = fopen(datafile, "r"))==NULL){ perror("fopen error"); exit(1); }
    }
    // printf("Source IP = %s,  Destination IP = %s\n", srcip, dstip);
    unsigned char sendbuf[BSZ];
    int datalen = 0, v1, v2;
    while(1){
        while((c1=fgetc(fp))!=EOF && c1)
            if(ISBLANK_CHAR(c1)) continue;
            else break;
        if(c1==EOF) break;
        while((c2=fgetc(fp))!=EOF)
            if(c2==' ' || c2=='\n') continue;
            else break;
        if(c2==EOF) break;
        if((v1=TOHEX_VALUE(c1))==0xFF || (v2=TOHEX_VALUE(c2))==0xFF){
            fprintf(stderr, "%c%c is not a hex number", c1, c2);
            exit(1);
        }
        sendbuf[datalen++] = ((v1<<4)|v2);
    }
    // 超级用户才能创建 IP 套接字
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if(sockfd == -1) { perror("socket error"); exit(1); }
    setuid(getuid());  // 退出超级用户模式
    int on = 1;
    if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on))<0){
        perror("setsocketopt error"); exit(1);
    }

    struct sockaddr_in dst_addr;
    struct ip *ip = (struct ip*)sendbuf;
    memset(&dst_addr, 0, sizeof(dst_addr));
    dst_addr.sin_family = AF_INET;
    dst_addr.sin_addr = ip->ip_dst;

    if(sendto(sockfd, sendbuf, datalen, 0, (struct sockaddr*)&dst_addr,
        sizeof(dst_addr)) < 0){
        perror("sendto error"); exit(1);
    }
    // sleep(1);
    return 0;
}


