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

ushort checksum(u_char data[], size_t len){
    u_int32_t sum = 0;
    for(int i=0; i<len; ++i){
        ushort tv = data[i];
        sum += ((~tv)&0xFFFF);
        while((0xFF0000 & sum) != 0)
            sum = ((0xFF0000 & sum)>>16)+(0xFFFF & sum);
    }
    return sum;
}



