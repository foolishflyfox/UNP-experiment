// icmptime.c
// 该程序用于构建ICMP时间戳请求报文
#include "tools.h"

int main(int argc, char *argv[]){
    // char srcip[INET_ADDRSTRLEN], dstip[INET_ADDRSTRLEN];
    // srcip[0] = dstip[0] = '\0';
    char s_err[256], c;
    u_char buf[1500] = {0};
    struct hostent *hp;
    struct ip *ip = (struct ip*)buf;
    struct icmp *icmp = (struct icmp*)(ip+1);
    snprintf(s_err, sizeof(s_err), "Usage: %s "
            "[-s src-host] <-d dst-host>\n", argv[0]);
    opterr = 0;
    ip->ip_src.s_addr = 0;  // 将源IP地址设置为0，内核将会填充
    while((c = getopt(argc, argv, "s:d:"))!=-1){
        switch(c){
            case 's':
                if((hp = gethostbyname(optarg))!=NULL)
                    memcpy(&ip->ip_src, hp->h_addr_list[0], hp->h_length);
                break;
            case 'd':
                if((hp = gethostbyname(optarg))!=NULL){
                    memcpy(&ip->ip_dst, hp->h_addr_list[0], hp->h_length);
                }else{
                    fprintf(stderr, "dst %s is invalidate\n", optarg);
                    exit(1);
                }
                break;
            case '?':
                fprintf(stderr, "unrecognized option: '%s'\n", argv[optind-1]);
                exit(1);
        }
    }
    if(ip->ip_dst.s_addr == 0){
        fputs(s_err, stderr); exit(1);
    }
    // 填充 IP 首部
    ip->ip_v = 4;  // 使用 IPv4 协议
    ip->ip_hl = sizeof(*ip) >> 2;  // 首部长度(以4字节为单位)
    ip->ip_tos = 0;  // 4~1位: 最小延时/最大吞吐量/最高可靠性/最小费用
    ip->ip_len = sizeof(*ip)+20;  // ICMP 时间请求报文长度为 20
    ip->ip_id = 0;  // 可以为任意值, 若置为0，则由内核配置
    ip->ip_off = 0;  // 标记(3bit)+段偏移量(13bit)
    ip->ip_ttl = 64;
    ip->ip_p = IPPROTO_ICMP;  // 高层协议为 ICMP
    ip->ip_sum = 0;  // 内核计算校验和
    // 源地址、目的地址已填，无可选项字段
    // 填充时间戳请求 ICMP 内容
    icmp->icmp_type = ICMP_TSTAMP; // 类型(1B): 13 发送
    icmp->icmp_code = 0;  // 代码(1B)
    icmp->icmp_cksum = 0;  // 校验和(2B): 之后计算
    icmp->icmp_id = getpid();  // 标识符(2B)
    icmp->icmp_seq = 12345;  // 序列号(2B)
    // 发起时间戳(4B) 接收时间戳(4B) 传送时间戳(4B)
    struct timeval cur;
    gettimeofday(&cur, NULL);
    //发送时间戳: 从午夜开始的毫秒数，其他两个时间戳保持为0
    icmp->icmp_otime = htonl((cur.tv_sec%(24*3600))*1000+cur.tv_usec/1000);
    // ICMP 计算校验和
    icmp->icmp_cksum = CheckSum((unsigned short*)icmp, 10);
    for(int i=0; i<40; ++i)
        printf("%02x%c", buf[i], " \n"[(i+1)%16==0]);
}


