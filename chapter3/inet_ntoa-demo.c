// inet_ntoa-demo.c
#include <stdio.h>
#include <arpa/inet.h>

int main(){
    union {unsigned int x; unsigned char y[4];} a;
    a.x = 1; printf("%s-endian\n", a.y[0]==1?"little":"big");
    struct in_addr addr;
    addr.s_addr = 0x01020304;
    printf("%s\n", inet_ntoa(addr));
}
