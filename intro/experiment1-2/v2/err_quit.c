// intro/experiment1-2/v2/err_quit.c
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 4095

void err_quit(const char* fmt, ...){
    fputs("\033[35mUSER ERROR:\033[0m ", stderr);
    va_list ap;
    va_start(ap, fmt);
    char buf[MAXLINE+1];
    vsnprintf(buf, 255, fmt, ap);
    fputs(buf, stderr);
    va_end(ap);
    exit(1);
}

int main(int argc, char* argv[]){
    err_quit("%d+%f=20 is wrong\n", 10, 2.5, 28);
    printf("End of main.\n");
    return 0;
}

