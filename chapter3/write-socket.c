// write-socket.c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BSZ 65535
#define SERV_PORT 60100
int main(){
    char buf[BSZ];
    struct sockaddr_in addr, ca;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERV_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    int pipe_fd[2];
    pipe(pipe_fd);
    pid_t pid = fork();
    if(pid==-1) { perror("fork error"); return 1; }
    else if(pid) {
        close(pipe_fd[0]); 
        int servfd = socket(AF_INET, SOCK_STREAM, 0);
        if(servfd==-1) { perror("create servfd error"); return -1;}
        if(bind(servfd, (struct sockaddr*)&addr, sizeof(addr))==-1){
            perror("bind error"); return -1;
        }
        if(listen(servfd, 16)==-1){
            perror("listen error"); return -1;
        }
        socklen_t sktlen = sizeof(ca);
        close(pipe_fd[1]);
        int cfd = accept(servfd, (struct sockaddr*)&ca, &sktlen);
        if(cfd==-1) { perror("accept error"); return -1; }
        int wn = write(cfd, buf, BSZ);
        printf("write %d bytes\n", wn);
        waitpid(pid, NULL, 0);
    }else{
        close(pipe_fd[1]);
        read(pipe_fd[0], NULL, 1); // 同步操作，等待网络服务启动
        int cfd = socket(AF_INET, SOCK_STREAM, 0);
        if(connect(cfd, (struct sockaddr*)&addr, sizeof(addr))==-1){
            perror("connect error"); return -1;
        }
        int rn = read(cfd, buf, BSZ);
        printf("read %d bytes\n", rn);
    }
}

