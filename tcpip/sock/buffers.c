#include "sock.h"

void buffers(int sockfd){
    int n;
    socklen_t optlen;
    if(rbuf == NULL){
        if((rbuf = malloc(readlen))==NULL)
            err_sys("malloc error for read buffer");
    }
    if(wbuf == NULL){
        if((wbuf = malloc(writelen))==NULL)
            err_sys("malloc error for write buffer");
    }
    /* 设置套接字发送与接收的缓冲区大小(如果已经指定)
       接收缓冲区的大小与 TCP 的建议窗口大小相关 */
    if(rcvbuflen){
        if(setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuflen,
            sizeof(rcvbuflen)) < 0)
            err_sys("SO_RCVBUF setsockopt error");
        optlen=sizeof(int);
        if(getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, &optlen)<0)
            err_sys("SO_RCVBUF getsockopt error");
        if(n!=rcvbuflen)
            fprintf(stderr, "rcvbuflen = %d, SO_RCVBUF = %d", rcvbuflen, n);
        if(verbose)
            fprintf(stderr, "SO_RCVBUF = %d\n", n);
    }
    if(sndbuflen){
        if(setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sndbuflen, 
            sizeof(sndbuflen)) < 0)
            err_sys("SO_SNDBUF setsockopt error");
        optlen = sizeof(int);
        if(getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &n, &optlen)<0)
            err_sys("SO_SND getsockopt error");
        if(sndbuflen != n)
            err_quit("sndbuflen = %d, SO_SNDBUF = %d", sndbuflen, n);
        if(verbose)
            fprintf(stderr, "SO_SNDBUF = %d\n", n);
    }
}

