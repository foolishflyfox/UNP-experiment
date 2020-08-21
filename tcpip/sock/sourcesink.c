#include "sock.h"
#include <ctype.h>

static void pattern(char *ptr, int len);

void sink(int sockfd){
    int n;
    char oob;
    if(client){  // 客户端仅发送数据
        pattern(wbuf, writelen);
        if(pauseinit) sleep(pauseinit);
        for(int i=1; i<=nbuf; i++){
            if(urgwrite == i){
                oob = urgwrite;
                if((n = send(sockfd, &oob, 1, MSG_OOB))!=1)
                    err_sys("send of MSG_OOB returned %d, expected %d", n, writelen);
                if(verbose)
                    fprintf(stderr, "write %d byte of urgent data\n", n);
            }
            if((n = write(sockfd, wbuf, writelen))!=writelen)
                err_sys("write returned %d, expected %d", n, writelen);
            if(verbose)
                fprintf(stderr, "wrote %d bytes\n", n);
            if(pauserw)
                sleep(pauserw);
        }
    }else{  // 服务器仅接收数据
        if(pauseinit)
            sleep(pauseinit);
        for( ; ; ){
            if((n = read(sockfd, rbuf, readlen)) < 0){
                err_sys("read error");
            }else if(n==0)
                break;  // 连接被对端关闭
            // else if(n != readlen)
                // err_quit("read returned %d, expected %d", n, readlen);
            if(verbose)
                fprintf(stderr, "received %d bytes\n", n);
            if(pauserw)
                sleep(pauserw);
        }
    }
    if(pauseclose){
        if(verbose) fprintf(stderr, "pausing before close\n");
        sleep(pauseclose);
    }
    if(close(sockfd) < 0)
        err_sys("close error");  // since SO_LINGER may be set
}

// 用可打印字符填充 ptr 指向的缓冲区
static void pattern(char *ptr, int len){
    char c = 0;
    while(len-- > 0){
        while(isprint(c & 0x7F) == 0)
            c++;
        *ptr++ = (c++ & 0x7F);
    }
}
