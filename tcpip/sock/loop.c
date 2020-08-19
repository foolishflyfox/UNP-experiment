#include "sock.h"

#define CONTROLLEN (sizeof(struct cmsghdr)+sizeof(struct in_addr))

// 将 stdin 输入数据写到 sockfd 中
// 将 sockfd 接收数据显示到 stdout

void loop(int sockfd){
    static struct cmsghdr *cmptr = NULL;
    (void)cmptr; // 不显示可能出现的 cmptr 未使用警告
    int stdineof = 0, nread, ntowrite;
    fd_set rset;
    int maxfdp1 = sockfd+1;  // 检查文件描述符 [0 .. sockfd]
    struct sockaddr_in cliaddr;
    FD_ZERO(&rset);
    if(pauseinit)
        sleep(pauseinit);  // -P 选项，为服务器准备
    for( ; ; ){
        if(stdineof == 0)
            FD_SET(STDIN_FILENO, &rset);
        FD_SET(sockfd, &rset);
        if(select(maxfdp1, &rset, NULL, NULL, NULL)<0)
            err_sys("select error");
        if(FD_ISSET(STDIN_FILENO, &rset)){ // 标准输入中有数据可读
            if((nread = read(STDIN_FILENO, rbuf, readlen))<0)
                err_sys("read error from stdin");
            else if(nread == 0){  // EOF on stdin
                if(halfclose){
                    if(shutdown(sockfd, SHUT_WR)<0)
                        err_sys("shutdown() error");
                    FD_CLR(STDIN_FILENO, &rset);
                    stdineof = 1;  // 不再读取stdin
                    continue;
                }
                break;  // 默认: stdin EOF -> 结束
            }
            if(crlf){
                ntowrite = crlf_add(wbuf, writelen, rbuf, nread);
                if(write(sockfd, wbuf, ntowrite)!=ntowrite)
                    err_sys("write error");
            }else{
                if(write(sockfd, rbuf, nread)!=nread)
                    err_sys("write error");
            }
        }
        if(FD_ISSET(sockfd, &rset)){  // 从套接字中读取数据
            if(udp && server){
                socklen_t clilen = sizeof(cliaddr);
#ifndef MSG_TRUNC
                nread = recvfrom(sockfd, rbuf, readlen, 0, 
                    (struct sockaddr*)&cliaddr, &clilen);
#else
                struct iovec iov[1];
                struct msghdr msg;
                iov[0].iov_base = rbuf;
                iov[0].iov_len = readlen;
                msg.msg_iov = iov;
                msg.msg_iovlen = 1;
                msg.msg_name = &cliaddr;
                msg.msg_namelen = clilen;
#ifdef IP_RECVDSTADDR
                if(cmptr==NULL && (cmptr=malloc(CONTROLLEN))==NULL)
                    err_sys("malloc error for control buffer");
                msg.msg_control = cmptr;
                msg.msg_controllen = CONTROLLEN;
#else
                msg.msg_control = NULL;
                msg.msg_controllen = 0;
#endif
                msg.msg_flags = 0;  // 通过该属性返回标志
                nread = recvmsg(sockfd, &msg, 0);
#endif
                if(nread < 0)
                    err_sys("datagram receive error");
                if(verbose) {
                    printf("from %s", inet_ntoa(cliaddr.sin_addr));
#ifdef MSG_TRUNC
#ifdef IP_RECVDSTADDR
                    if(recvdstaddr){
                        if(cmptr->cmsg_level != IPPROTO_IP)
                            err_quit("control level != IPPROTO_IP");
                        if(cmptr->cmsg_type != IP_RECVDSTADDR)
                            err_quit("control type != IP_RECVDSTADDR");
                        if(cmptr->cmsg_len != CONTROLLEN)
                            err_quit("control length (%d) != %d",
                                cmptr->cmsg_len, CONTROLLEN);
                        struct in_addr dstinaddr;
                        bcopy(CMSG_DATA(cmptr), &dstinaddr, sizeof(struct in_addr));
                        printf(", to %s", inet_ntoa(dstinaddr));
                    }
#endif // IP_RECVDSTADDR
#endif // MSG_TRUNC
                    printf(": ");
                    fflush(stdout);
                }
#ifdef MSG_TRUNC
                if(msg.msg_flags & MSG_TRUNC)
                    printf("(datagram truncated)\n");
#endif
            }else{
                if((nread = read(sockfd, rbuf, readlen))<0)
                    err_sys("read error");
                else if(nread == 0){
                    if(verbose)
                        fprintf(stderr, "connection closed by peer\n");
                    break;
                }
            }
            if(crlf){
                ntowrite = crlf_strip(wbuf, writelen, rbuf, nread);
                if(writen(STDOUT_FILENO, wbuf, ntowrite)!=ntowrite)
                    err_sys("writen error to stdout");
            }else{
                if(writen(STDOUT_FILENO, rbuf, nread) != nread)
                    err_sys("writen error to stdout");
            }
        }
    }
    if(pauseclose){
        if(verbose)
            fprintf(stderr, "pausing before close\n");
        sleep(pauseclose);
    }
    if(close(sockfd) < 0)
        err_sys("close error");
}

