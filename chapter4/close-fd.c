// close-fd.c
#include "unp.h"

#define TEST_CNT 3

int main(){
    int fd[2];
    if(-1==pipe(fd)) { perror("pipe error"); exit(1); }
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(11000);
    pid_t pid = fork();
    if(pid==-1) { perror("fork error");  exit(1); }
    if(pid > 0){  // parent
        close(fd[0]);
        int servfd = Socket(AF_INET, SOCK_STREAM, 0);
        Bind(servfd, (SA*)&addr, sizeof(addr));
        Listen(servfd, LISTENQ);
        close(fd[1]);
        for(int i=0; i<TEST_CNT; ++i){
            int clifd = Accept(servfd, NULL, NULL);
            printf("clifd = %d\n", clifd);
            sleep(1);
            #ifdef CLOSE_CLIFD
            close(clifd);
            #endif
        }
    }else{  // child
        close(fd[1]);
        read(fd[0], NULL, 1);  // 同步，等待父进程服务开启
        for(int i=0; i<TEST_CNT; ++i){
            int clifd = Socket(AF_INET, SOCK_STREAM, 0);
            Connect(clifd, (SA*)&addr, sizeof(addr));
            close(clifd);
        }
    }
}

