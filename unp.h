#ifndef __UNP_H__
#define __UNP_H__

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>

#define MAXLINE 4096
#define	LISTENQ 1024
typedef struct sockaddr SA;

int Socket(int family, int type, int protocol);
void Listen(int fd, int backlog);
void Bind(int fd, const struct sockaddr *addr, socklen_t addrlen);
int Accept(int fd, struct sockaddr *addr, socklen_t *addrlen);

ssize_t readn(int fd, void *buff, size_t nbytes);
ssize_t written(int fd, const void *buff, size_t nbytes);
ssize_t readline(int fd, void *buff, size_t maxlen);

#endif

