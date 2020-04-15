#ifndef __unp_h
#define __unp_h

#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

#define MAXLINE 4096 /* max text line length */

void err_doit(const char* fmt, va_list ap);
void err_quit(const char* fmt, ...);
void err_sys(const char* fmt, ...);

int Socket(int family, int type, int protocol);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
ssize_t Read(int fildes, void *buf, size_t nbyte);
int Fputs(const char *restrict s, FILE *restrict stream);
int Inet_pton(int family, const char* strptr, void* addrptr);

#endif
