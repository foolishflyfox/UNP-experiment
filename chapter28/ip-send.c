// ip-send.c
#include "tools.h"

int main(int argc, char *argv[]){
    char c, srcip[INET_ADDRSTRLEN], dstip[INET_ADDRSTRLEN];
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
    unsigned char sendbuf[BSZ];
    int datalen = HexToData(fp, sendbuf, BSZ);
    // int v1, v2;
    // char c1, c2;
    // while(1){
    //     while((c1=fgetc(fp))!=EOF && c1)
    //         if(ISBLANK_CHAR(c1)) continue;
    //         else break;
    //     if(c1==EOF) break;
    //     while((c2=fgetc(fp))!=EOF)
    //         if(c2==' ' || c2=='\n') continue;
    //         else break;
    //     if(c2==EOF) break;
    //     if((v1=TOHEX_VALUE(c1))==0xFF || (v2=TOHEX_VALUE(c2))==0xFF){
    //         fprintf(stderr, "%c%c is not a hex number", c1, c2);
    //         exit(1);
    //     }
    //     sendbuf[datalen++] = ((v1<<4)|v2);
    // }
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


