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
#include <limits.h>
#include <poll.h>
#include <sys/un.h>
#include <netdb.h>

#define MAXLINE 4096
#define	LISTENQ 1024
#define SERV_PORT 9877

#ifndef INFTIM
#define INFTIM -1
#endif
#ifndef OPEN_MAX
#define OPEN_MAX 1024
#endif

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
ssize_t Recvfrom(int fd, void *buff, size_t nbytes, int flags,
                struct sockaddr *sa, socklen_t *salenptr);
void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
                const struct sockaddr *sa, socklen_t salen);
void Write(int fd, const void *ptr, size_t nbytes);
ssize_t Read(int fd, void *ptr, size_t nbytes);

void Inet_pton(int family, const char *src, void *dst);
const char* Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
char * sock_ntop(const struct sockaddr *sa, socklen_t salen);
char * Sock_ntop(const struct sockaddr *sa, socklen_t salen);
void Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Setsockopt(int fd, int level, int optname, const void*optval, socklen_t optlen);

typedef void Sigfunc(int);
Sigfunc* Signal(int signo, Sigfunc *func);

int Select(int maxfdp1, fd_set *rset, fd_set *wset, fd_set *eset, 
            struct timeval *timeout);

const char* getcurtime();

void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);
void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen);
void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

int connect_timeo(int sockfd, const SA *addr, socklen_t len, int nsec);
#endif

