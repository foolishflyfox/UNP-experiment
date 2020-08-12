// ip-send.c
#include "tools.h"

int main(int argc, char *argv[]){
    char c, srcip[INET_ADDRSTRLEN], dstip[INET_ADDRSTRLEN];
    srcip[0] = dstip[0] = '\0';
    char s_err[256];
    snprintf(s_err, sizeof(s_err), "Usage: %s [data-file]", argv[0]);
    const char *datafile = NULL;
    FILE* fp = stdin;
    
    if(argc==2){
        datafile = argv[1];
        if(access(datafile, R_OK)==-1){ perror("access error"); exit(1); }
        if((fp = fopen(datafile, "r"))==NULL){ perror("fopen error"); exit(1); }
    }
    unsigned char sendbuf[BSZ];
    int datalen = HexToData(fp, sendbuf, BSZ);
    SendIPData(sendbuf, datalen);
    return 0;
}


