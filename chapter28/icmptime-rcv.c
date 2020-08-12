// icmptime-rcv.c
#include "tools.h"

int main(int argc, char* argv[]){
    struct timeval tv;
    unsigned char buf[BSZ];
    int datalen = HexToData(stdin, buf, BSZ);
    if(datalen != 40){  // ICMP 时间戳请求与应答IP数据报长度都为40B
        fprintf(stderr, "error: icmptime recv data is not 40B\n");
        exit(1);
    }
    gettimeofday(&tv, 0);
    struct icmp *icmp = (struct icmp*)(buf+sizeof(struct ip));
    // icmp->icmp_rtime = icmp->icmp_otime;
    // icmp->icmp_ttime = icmp->icmp_otime;
    long otime = ntohl(icmp->icmp_otime);
    long rtime = ntohl(icmp->icmp_rtime);
    long ttime = ntohl(icmp->icmp_ttime);
    long rtt = (tv.tv_sec%(24*3600))*1000+tv.tv_usec/1000-otime;
    long difference = rtime - (otime + rtt/2);
    printf("orig = %ld, recv = %ld, xmit = %ld, rtt = %ld ms\n"
    "difference = %ld ms\n", otime, rtime, ttime, rtt, difference);
        
}

