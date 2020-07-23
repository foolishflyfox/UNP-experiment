// inet_ntop-demo.c
#include <arpa/inet.h>
#include <stdio.h>

int main(){
    union { struct in_addr ip; u_char data[4]; }ip4;
    union { struct in6_addr ip; u_char data[16]; }ip6;
    char s1[INET_ADDRSTRLEN], s2[INET6_ADDRSTRLEN];
    for(int i=0; i<4; ++i) ip4.data[i] = i+1;
    for(int i=0; i<16; ++i)
        if(i<6 || i >10) ip6.data[i] = i+1;
        else ip6.data[i] = 0;
    printf("IPv4: %s\n", inet_ntop(AF_INET, &ip4, s1, sizeof(s1)));
    printf("IPv6: %s\n", inet_ntop(AF_INET6, &ip6, s2, sizeof(s2)));
}

