#ifndef __UNP_H__
#define __UNP_H__

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/signal.h>
#include <signal.h>
#include <time.h>

#define MAXLINE 4096
#define	LISTENQ 1024
#define SERV_PORT 9877
typedef struct sockaddr SA;

pid_t Fork(void);

int Socket(int family, int type, int protocol);
void Listen(int fd, int backlog);
void Bind(int fd, const struct sockaddr *addr, socklen_t addrlen);
int Accept(int fd, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int fd, const struct sockaddr *addr, socklen_t addrlen);

ssize_t readn(int fd, void *buff, size_t nbytes);
ssize_t written(int fd, const void *buff, size_t nbytes);
char* Fgets(char *ptr, int n, FILE *stream);
ssize_t readline(int fd, void *buff, size_t maxlen);
ssize_t Readline(int fd, void *buff, size_t maxlen);

void Inet_pton(int family, const char *src, void *dst);

typedef void Sigfunc(int);
Sigfunc* Signal(int signo, Sigfunc *func);

const char* getcurtime();

void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);
#endif

