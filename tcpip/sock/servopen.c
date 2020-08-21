#include "sock.h"

int servopen(char *host, char *port){
    // int fd, newfd, i, on, pid;
    int fd, i, on, newfd;
    socklen_t len;
    pid_t pid;
    struct sockaddr_in cli_addr, serv_addr;
    char *protocol = udp?"udp":"tcp";
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    if(host==NULL)
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    else{
        if((serv_addr.sin_addr.s_addr = inet_addr(host))==INADDR_NONE)
            err_quit("invalid host name for server: %s", host);
    }
    if((i=atoi(port))==0){
        struct servent *sp = getservbyname(port, protocol);
        if(sp==NULL)
            err_ret("getservbyname() error for: %s/%s", port, protocol);
        else
            serv_addr.sin_port = sp->s_port;
    }else
        serv_addr.sin_port = htons(i);
    if((fd = socket(AF_INET, udp?SOCK_DGRAM:SOCK_STREAM, 0)) < 0)
        err_sys("socket() error");
    if(reuseaddr){
        on = 1;
        if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))<0)
            err_sys("setsockopt of SO_REUSEADDR error");
    }
    if(bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
        err_sys("can't bind local address");

    // buffers(fd);
    
    if(udp){
        buffers(fd);
        if(foreignip[0]!=0){
            bzero(&cli_addr, sizeof(cli_addr));
            cli_addr.sin_family = AF_INET;
            cli_addr.sin_addr.s_addr = inet_addr(foreignip);
            cli_addr.sin_port = htons(foreignport);
            if(connect(fd, (struct sockaddr*)&cli_addr, sizeof(cli_addr))<0)
                err_sys("connect() error");
        }
        sockopts(fd, 1);
        return fd;
    }
    buffers(fd);
    sockopts(fd, 0);
    if(listen(fd, listenq)<0)
        err_sys("listen() error");
    
    if(pauselisten > 0) sleep(pauselisten);

    if(dofork)
        TELL_WAIT();  // 初始化同步元素
    for( ; ; ){
        len = sizeof(cli_addr);
        if((newfd = accept(fd, (struct sockaddr*)&cli_addr, &len))<0)
            err_sys("accept() error");
        if(dofork){
            if((pid = fork())<0)
                err_sys("fork error");
            if(pid > 0){
                close(newfd);  // 父进程关闭读写套接字
                WAIT_CHILD();
                continue;       // 继续等待子进程连接
            }else{
                close(fd);      // 子进程关闭侦听套接字
            }
        }
        // 子进程(或迭代服务器)将会运行到此处
        if(verbose){
            len = sizeof(serv_addr);
            if(getsockname(newfd, (struct sockaddr*)&serv_addr, &len)<0)
                err_sys("getsockname() error");
            fprintf(stderr, "connection on %s.%d ", inet_ntoa(serv_addr.sin_addr),
                ntohs(serv_addr.sin_port));
            fprintf(stderr, "from %s.%d\n", inet_ntoa(cli_addr.sin_addr),
                ntohs(cli_addr.sin_port));
        }
        buffers(newfd);  // 再次调用 setsockopt，因为连接套接字不能继承侦听套接字属性
        sockopts(newfd, 1);
        if(dofork)
            TELL_PARENT(getppid()); // 子链接的初始化完成，允许接收其他连接请求
        return newfd;
    }
    return fd;
}

