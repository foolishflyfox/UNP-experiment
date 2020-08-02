// so_reuseaddr.c
#include "unp.h"

int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: %s <IP1> <IP2>\n", argv[0]);
        exit(1);
    }
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = SERV_PORT;
    pid_t pid = fork();
    if(pid<0) {perror("fork error"); exit(1);}
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    int reuse_addr= 1;
#ifdef REUSEADDR
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr))==-1){
        perror("setsockopt error"); exit(1);
    }
#endif
    if(pid > 0){
        Inet_pton(AF_INET, argv[1], &addr.sin_addr);
        Bind(fd, (SA*)&addr, sizeof(addr));
        sleep(3);
    }else{
        sleep(1);
        Inet_pton(AF_INET, argv[2], &addr.sin_addr);
        Bind(fd, (SA*)&addr, sizeof(addr));
        sleep(2);
    }
}


