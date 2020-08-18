#include "sock.h"

// 打开客户端套接字描述符
int cliopen(char *host, char *port){
    int     fd, i, on;
    char *protocol = udp?"udp":"tcp";
    struct sockaddr_in cli_addr, serv_addr;
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    // 如果使用的端口是服务名而非数字
    if((i = atoi(port))==0){
        struct servent *sp = getservbyname(port, protocol);
        if(sp==NULL)
            err_quit("getservbyname() error for: %s/%s", port, protocol);
        serv_addr.sin_port = sp->s_port;
    }else{
        serv_addr.sin_port = htons(i);
    }
    // 首先尝试将主机名视为点分十进制，如果失败再当成域名进行解析
    if(inet_pton(AF_INET, host, &serv_addr.sin_addr)!=1){
        struct hostent *hp = gethostbyname(host);
        if(hp == NULL) err_quit("gethostbyname() error for: %s", host);
        bcopy(hp->h_addr, &serv_addr.sin_addr, hp->h_length);
    }
    if((fd = socket(AF_INET, udp?SOCK_DGRAM:SOCK_STREAM, 0)) < 0)
        err_sys("socket() error");
    if(reuseaddr) {
        on = 1;
        if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
            err_sys("setsockopt of SO_REUSEADDR error");
    }
    // 为客户端显式指定端口号
    if(bindport != 0 || udp){
        bzero(&cli_addr, sizeof(cli_addr));
        cli_addr.sin_family = AF_INET;
        cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        cli_addr.sin_port = htons(bindport);
        if(bind(fd, (struct sockaddr*)&cli_addr, sizeof(cli_addr))<0)
            err_sys("bind() error");
    }
    // 在调用 connect 函数前需要先分配缓冲区，因为这可能会影响 TCP 选项(如出口大小等)
    buffers(fd);
    sockopts(fd, 0);

    if(connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
        err_sys("connect() error");
    if(verbose){
        socklen_t len = sizeof(cli_addr);
        if(getsockname(fd, (struct sockaddr*)&cli_addr, &len)<0)
            err_sys("getsockname() error");
        fprintf(stderr, "connected on %s.%d ", inet_ntoa(cli_addr.sin_addr), 
            htons(cli_addr.sin_port));
        fprintf(stderr, "to %s.%d\n", inet_ntoa(serv_addr.sin_addr),
            htons(serv_addr.sin_port));
    }
    sockopts(fd, 1);  // 某些选项需要在调用 connect 函数后才能被设置
    return fd;
}

