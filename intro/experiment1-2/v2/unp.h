#ifndef __unp_h
#define __unp_h

#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAXLINE 4096 /* max text line length */

void err_doit(const char* fmt, va_list ap);
void err_quit(const char* fmt, ...);
void err_sys(const char* fmt, ...);

#endif
