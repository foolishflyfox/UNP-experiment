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



