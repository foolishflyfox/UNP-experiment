#include <errno.h>
#include <stdarg.h>
#include "ourhdr.h"

static void err_doit(int errnoflag, const char *fmt, va_list ap){
    int     errno_save;
    char    buf[MAXLINE];
    
    errno_save = errno;  // 防止执行过程中 errno 值被改变
    vsprintf(buf, fmt, ap);
    if(errnoflag)
        sprintf(buf+strlen(buf), ": %s", strerror(errno_save));
    strncat(buf, "\n", sizeof(buf)-strlen(buf)-1); // 将自动添加\0
    fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
    return;
}

// 向 stderr 格式化输出错误, 附加 errno 相关内容
void err_ret(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    return;
}

// 向 stderr 格式化输出错误, 不附加 errno 相关内容
void err_msg(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);
    return;
}

// 向 stderr 格式化输出错误，并退出程序
void  err_quit(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);
    exit(1);
}

// 向 stderr 格式化输出错误(打印errno相关信息)，并退出程序
void err_sys(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    exit(1);
}

