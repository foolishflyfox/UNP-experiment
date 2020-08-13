// ip-send.c
#include "tools.h"

int main(int argc, char *argv[]){
    char c, srcip[INET_ADDRSTRLEN], dstip[INET_ADDRSTRLEN];
    char s_err[256];
    snprintf(s_err, sizeof(s_err), 
        "Usage: %s <proto> <dst-host> [data-file]\n", 
        argv[0]);
    if(argc < 3) { fputs(s_err, stderr); exit(1); }

    unsigned char sendbuf[BSZ] = {0};
    struct ip *ip = (struct ip*)sendbuf;
    SetIPDftHdr(ip);
    if(GetInAddrByName(argv[2], &ip->ip_dst.s_addr)==-1){
        fputs(s_err, stderr); exit(1);
    }
    ip->ip_p = atoi(argv[1]);

    FILE* fp = stdin;
    const char *datafile = NULL;
    if(argc==4){
        datafile = argv[3];
        if(access(datafile, R_OK)==-1){ perror("access error"); exit(1); }
        if((fp = fopen(datafile, "r"))==NULL){ perror("fopen error"); exit(1); }
    }
    int sdulen = HexToData(fp, sendbuf+sizeof(*ip), BSZ);
    ip->ip_len = sizeof(*ip)+sdulen;

    SendIPData(-1, sendbuf, ip->ip_len);
    return 0;
}


