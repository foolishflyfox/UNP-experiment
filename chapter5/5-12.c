// 5-12.c
#include "unp.h"

void sig_child(int signo){
    pid_t pid;
    int stat;
    while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
    return;
}

int main(int argc, char *argv[]){
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    if(signal(SIGCHLD, sig_child)==SIG_ERR){ // 添加信号处理函数
        perror("signal error"); exit(1);
    }
    Listen(listenfd, LISTENQ);
    for( ; ; ){
        clilen = sizeof(cliaddr);
        if((connfd = accept(listenfd, (SA*)&cliaddr, &clilen))<0){
            if(errno == EINTR) continue;
            else { perror("accept error"); exit(1); }
        }
        if((childpid = Fork()) == 0){  // child process
            close(listenfd);    // close listening socket
            str_echo(connfd);   // process the request
            exit(0);
        }
        close(connfd);
    }
}
