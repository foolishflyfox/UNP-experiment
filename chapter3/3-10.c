#include <stdio.h>

int main(){
    union {
        short s;
        unsigned char  c[2];
    } un;
    un.s = 0x0102;
    printf("%s: ", CPU_VENDOR_OS);
    if(un.c[0]==0x01) printf("big-endian\n");
    else if(un.c[0]==0x02) printf("little-endian\n");
    else printf("unknown\n");
}

