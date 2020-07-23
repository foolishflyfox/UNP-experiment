// host_net.c
#include <stdio.h>
#include <netinet/in.h>

int main(){
    union {uint16_t u16; uint8_t c2[2];}a;
    union {uint32_t u32; uint8_t c4[4];}b;
    a.u16 = 0x0102; printf("0x%x,0x%x\n",  a.c2[0], a.c2[1]);
    a.u16 = htons(a.u16); printf("0x%x,0x%x\n",  a.c2[0], a.c2[1]);
    a.u16 = ntohs(a.u16); printf("0x%x,0x%x\n",  a.c2[0], a.c2[1]);
    b.u32 = 0x01020304;
    printf("0x%x,0x%x,0x%x,0x%x\n",b.c4[0],b.c4[1],b.c4[2],b.c4[3]);
    b.u32 = htonl(b.u32);
    printf("0x%x,0x%x,0x%x,0x%x\n",b.c4[0],b.c4[1],b.c4[2],b.c4[3]);
    b.u32 = ntohl(b.u32);
    printf("0x%x,0x%x,0x%x,0x%x\n",b.c4[0],b.c4[1],b.c4[2],b.c4[3]);
}

