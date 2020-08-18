#include "sock.h"

// 将 \n 与 \r\n 互转
int crlf_add(char *dst, int dstsize, const char *src, int lenin){
    char c;
    int lenout = lenin;
    if(lenout > dstsize)
        err_quit("crlf_add: destination not big enough");
    for( ; lenin > 0 ; lenin-- ){
        if((c = *src++)=='\n'){
            if(++lenout > dstsize)
                err_quit("crlf_add: destination not big enough");
            *dst++ = '\r';
        }
        *dst++ = c;
    }
    return lenout;
}
int crlf_strip(char *dst, int dstsize, const char *src, int lenin){
    int lenout;
    char c;
    for(lenout=0; lenin > 0; lenin--){
        if((c = *src++) != '\r'){
            if(++lenout > dstsize)
                err_quit("crlf_strip: destination not big enough");
            *dst++ = c;
        }
    }
    return lenout;
}

