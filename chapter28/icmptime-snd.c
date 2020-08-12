// icmptime-snd.c
// 该程序用于构建ICMP时间戳请求报文
#include "tools.h"

void SendProcess(in_addr_t srcaddr, in_addr_t dstaddr){
    u_char buf[1500] = {0};
    struct ip *ip = (struct ip*)buf;
    struct icmp *icmp = (struct icmp*)(ip+1);
    // 填充 IP 首部默认值
    SetIPDftHdr(ip);
    ip->ip_len = 40;
    ip->ip_p = IPPROTO_ICMP;
    ip->ip_src.s_addr = srcaddr;
    ip->ip_dst.s_addr = dstaddr;
    // 填充时间戳请求 ICMP 内容
    icmp->icmp_type = ICMP_TSTAMP; // 类型(1B): 13 发送
    icmp->icmp_code = 0;  // 代码(1B)
    icmp->icmp_cksum = 0;  // 校验和(2B): 之后计算
    icmp->icmp_id = getpid();  // 可任意，标识符(2B)
    icmp->icmp_seq = 12345;  // 可任意，序列号(2B)
    // 发起时间戳(4B) 接收时间戳(4B) 传送时间戳(4B)
    struct timeval cur;
    gettimeofday(&cur, NULL);
    //发送时间戳: 从午夜开始的毫秒数，其他两个时间戳保持为0
    icmp->icmp_otime = htonl((cur.tv_sec%(24*3600))*1000+cur.tv_usec/1000);
    // ICMP 计算校验和
    icmp->icmp_cksum = CheckSum((unsigned short*)icmp, 10);
    SendIPData(buf, 40);
}

int main(int argc, char *argv[]){
    char s_err[256], c;
    snprintf(s_err, sizeof(s_err), "Usage: %s "
            "[-s src-host] <-d dst-host>\n", argv[0]);

    opterr = 0;
    in_addr_t srcaddr, dstaddr;
    while((c = getopt(argc, argv, "s:d:"))!=-1){
        switch(c){
            case 's':
                if(-1==GetInAddrByName(optarg, &srcaddr))
                    srcaddr = 0;
                break;
            case 'd':
                if(-1==GetInAddrByName(optarg, &dstaddr)){
                    fprintf(stderr, "dst %s is invalidate\n", optarg);
                    exit(1);
                }
                break;
            case '?':
                fprintf(stderr, "unrecognized option: '%s'\n", argv[optind-1]);
                exit(1);
        }
    }
    if(dstaddr == 0){ fputs(s_err, stderr); exit(1); }
    SendProcess(srcaddr, dstaddr);
    // pid_t pid = fork();
    // if(pid==-1) { perror("fork error"); exit(1); }
    // if(pid){
    //     usleep(1);  // 让接收进程先启动
    //     SendProcess(srcaddr, dstaddr);
    // }else{

    // }
}


