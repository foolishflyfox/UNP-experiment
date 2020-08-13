#include "tools.h"

// 根据域名获取IP地址
const char* GetIPByName(const char *name){
    static char str[INET_ADDRSTRLEN];
    memset(str, 0, sizeof(str));
    struct hostent *hptr = gethostbyname(name);
    if(hptr == NULL){
        fprintf(stderr, "GethostnameStr: gethostbyname error for host %s: %s\n",
            name, hstrerror(h_errno));
        exit(1);
    }
    char **pptr = hptr->h_addr_list;
    if(hptr->h_addrtype!=AF_INET || *pptr == NULL) {
        fprintf(stderr, "GethostnameStr: Can't get IP of %s\n", name);
        exit(1);
    }
    return inet_ntop(AF_INET, *pptr, str, sizeof(str));
}

ushort CheckSum(unsigned short data[], size_t len){
    u_int32_t sum = 0;
    for(int i=0; i<len; ++i){
        ushort tv = data[i];
        sum += ((~tv)&0xFFFF);
        while((0xFF0000 & sum) != 0)
            sum = ((0xFF0000 & sum)>>16)+(0xFFFF & sum);
    }
    return sum;
}

int SendIPData(unsigned char data[], int datalen){
    if(datalen < 20) {
        fprintf(stderr, "SendIPData errpr: datalen less than 20");
        return -1;
    }
    // 超级用户才能创建 IP 套接字
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if(sockfd == -1) { perror("socket error"); return -1; }
    int on = 1;
    if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on))<0){
        perror("setsocketopt error"); return -1;
    }
    struct sockaddr_in dst_addr;
    struct ip *ip = (struct ip*)data;
    memset(&dst_addr, 0, sizeof(dst_addr));
    dst_addr.sin_family = AF_INET;
    dst_addr.sin_addr = ip->ip_dst;

    if(sendto(sockfd, data, datalen, 0, (struct sockaddr*)&dst_addr,
        sizeof(dst_addr)) < 0){
        perror("sendto error"); return -1;
    }
    return 0;
}

int InitIPRawSocket(in_addr_t dst, struct sockaddr_in *addr, socklen_t *len){
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if(sockfd < 0){ return -1; }
    *len = sizeof(struct sockaddr_in);
    bzero(addr, *len);
    addr->sin_family = AF_INET;
    // dst 为0时，接收任何目标地址的除TCP/IP外的数据报
    addr->sin_addr.s_addr = dst;
    return sockfd;
}

int GetInAddrByName(const char *name, in_addr_t* addrptr){
    struct hostent *hp;
    if((hp = gethostbyname(name))==NULL) return -1;
    if(hp->h_addrtype != AF_INET) return -1;
    memcpy(addrptr, hp->h_addr_list[0], hp->h_length);
    return 0;
}

void SetIPDftHdr(struct ip *ip){
    ip->ip_v = 4;  // 使用 IPv4 协议
    ip->ip_hl = (sizeof(*ip)) >> 2;  // 首部长度(以4字节为单位)
    ip->ip_tos = 0;  // 4~1位: 最小延时/最大吞吐量/最高可靠性/最小费用
    // ip->ip_len = sizeof(*ip)+20;  // IP PDU报文长度
    ip->ip_id = 0;  // 可以为任意值, 若置为0，则由内核配置
    ip->ip_off = 0;  // 标记(3bit)+段偏移量(13bit)
    ip->ip_ttl = 64;
    // ip->ip_p = proto;  // 高层协议为
    ip->ip_sum = 0;  // 内核计算校验和
    // ip->ip_src;  // 源IP地址字段
    // ip->ip_dst;  // 目标IP地址字段
}

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
// 读入 fp 流指定的十六进制表示的文本，并将其保持到 buf 中
int HexToData(FILE *fp, unsigned char buf[], int bufsize){
    int v1, v2, datalen = 0;
    char c1, c2;
    while(1){
        if(bufsize <= datalen) {
            fprintf(stderr, "HexToData error: out of buffer\n");
            exit(1);
        }
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
        buf[datalen++] = ((v1<<4)|v2);
    }
    return datalen;
}



