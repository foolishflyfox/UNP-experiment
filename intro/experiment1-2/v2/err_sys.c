// intro/experiment1-2/v2/err_sys.c
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#define MAXLINE 4095

void err_sys(const char* fmt, ...){
    fputs("\033[31mSYSTEM ERROR:\033[0m ", stderr);
    if(errno){
        fprintf(stderr, "[%d: %s] ", errno, strerror(errno));
    }
    va_list ap;
    va_start(ap, fmt);
    char buf[MAXLINE+1];
    vsnprintf(buf, 255, fmt, ap);
    fputs(buf, stderr);
    va_end(ap);

    exit(1);
}

int main(int argc, char* argv[]){
    open("wrong-path.txt", O_RDONLY);
    err_sys("%d+%f=20 is wrong\n", 10, 2.5, 28);
    printf("End of main.\n");
    return 0;
}

