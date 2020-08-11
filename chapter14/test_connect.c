// test_connect.c
#include "unp.h"

int main(){
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, "212.64.51.28", &addr.sin_addr);
    #ifdef CONNECT_TIMEO
    if(connect_timeo(fd, (SA*)&addr, sizeof(addr), 5)!=0){
        perror("connect_timeo error"); exit(1);
    }
    #else
    if(connect(fd, (SA*)&addr, sizeof(addr))!=0){
        perror("connect error"); exit(1);
    }
    #endif
}
