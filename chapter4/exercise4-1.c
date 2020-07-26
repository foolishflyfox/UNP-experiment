// exercise4-1.c
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(){
    unsigned int addr;
    inet_pton(AF_INET, "127.0.0.1", &addr);
    printf("INADDR_LOOPBACK = 0x%x\n", INADDR_LOOPBACK);
    printf(" 127.0.0.1(net) = 0x%08x\n", addr);
}
