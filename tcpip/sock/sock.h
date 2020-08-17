#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#include  "ourhdr.h"

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


