// intro/experiment1-2/v1/test-inet-pton.c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

typedef union{
    uint32_t wholeaddr;
    uint8_t subaddr[4];
}  NetAddress;

void ShowNetAddress(int result, const NetAddress* p_addr){
    printf("result = %d; 0x%x (", result, p_addr->wholeaddr);
    for(int i=0; i<4; ++i) printf("%d%c", p_addr->subaddr[i], ",)"[i==3]);
    printf("[");
    for(int i=0; i<4; ++i) printf("0x%x%c", p_addr->subaddr[i], ",]"[i==3]);
    printf("\n");
}

int main(){
    int result = 0;
	NetAddress addr;
    bzero(&addr, sizeof(addr));
    result = inet_pton(AF_INET, "192.10.87.78", &addr);
    printf("1:%p\n", &addr);
    ShowNetAddress(result, &addr);
    bzero(&addr, sizeof(addr));
    result = inet_pton(AF_INET, "192.10.78", &addr);
    ShowNetAddress(result, &addr);
    return 0;
}