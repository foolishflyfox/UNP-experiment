#ifndef __ourhdr_h
#define __ourhdr_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern int bindport;
extern int broadcast;
extern int cbreak;
extern int client;
extern int crlf;
extern int debug;
extern int dofork;
extern char foreignip[];
extern int foreignport;
extern int halfclose;
extern int keepalive;
extern long linger;
extern int listenq;
extern int nodelay;
extern int nbuf;
extern int pauseclose;
extern int pauseinit;
extern int pauselisten;
extern int pauserw;
extern int reuseaddr;
extern int readlen;
extern int writelen;
extern int recvdstaddr;
extern int rcvbuflen;
extern int sndbuflen;
extern char *rbuf;
extern char *wbuf;
extern int server;
extern int sourcesink;
extern int udp;
extern int urgwrite;
extern int verbose;

int cliopen(char *host, char *port);
int servopen(char *host, char *port);

void buffers(int sockfd);  // 设置套接字缓冲区大小
void sockopts(int sockfd, int doall);
void sink(int sockfd);
void loop(int sockfd);

ssize_t writen(int fd, const void *vptr, size_t n);
int crlf_add(char *dst, int dstsize, const char *src, int lenin);
int crlf_strip(char *dst, int dstsize, const char *src, int lenin);

void err_msg(const char*, ...);
void  err_quit(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_ret(const char *fmt, ...);

void TELL_WAIT();
void WAIT_CHILD(void);
void TELL_PARENT(pid_t pid);
void TELL_CHILD(pid_t pid);

#define MAXLINE 4096    /* max line size */

#endif


