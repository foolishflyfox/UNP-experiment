// 4-10.c
#include "unp.h"

#define MAX_BACKLOG 14

int main(){
    setbuf(stdout, NULL);  // 设置无缓冲
    printf("backlog(max conn): ");
    int fd[2];
    if(pipe(fd)==-1){ perror("pipe error"); exit(1); }
    pid_t pid = fork();
    if(pid < 0) { perror("fork error"); exit(1); }
    if(pid > 0){  // parent
        close(fd[0]);
        for(int i=0; i<=MAX_BACKLOG; ++i){
            printf("%d", i);
            int servfd = Socket(AF_INET, SOCK_STREAM, 0);
            Listen(servfd, i);
            struct sockaddr_in addr;
            socklen_t len = sizeof(addr);
            if(getsockname(servfd, (SA*)&addr, &len)==-1){
                perror("getsockname error"); exit(1);
            }
            write(fd[1], &addr.sin_port, sizeof(in_port_t));
            sleep(3);
            close(servfd);
            sleep(1);
        }
        printf("\n");
    }else{
        close(fd[1]);
        for(int i=0; i<=MAX_BACKLOG; ++i){
            struct sockaddr_in addr;
            bzero(&addr, sizeof(addr));
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            read(fd[0], &addr.sin_port, sizeof(in_port_t));
            // printf("%d\n", addr.sin_port);
            int result = 0;
            while(1){
                int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
                if(connect(sockfd, (SA*)&addr, sizeof(addr))==0)
                    result++;
                else
                    break;
            }
            printf("(%d), ", result);
        }
    }
}

