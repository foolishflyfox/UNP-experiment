// tools.h
#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <strings.h>
#include <signal.h>
#include <sys/wait.h>

// 可以发送的最大数据量
#ifndef BSZ
#define BSZ 4096
#endif

#define Perror(s) \
    (fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__), \
    perror(s))

// 与数据收发相关的函数
int SendIPData(int fd, unsigned char data[], int datalen);

// 与协议相关的填充函数
void SetIPDftHdr(struct ip *ip); // 设置 IP 的通用字段
ushort CheckSum(unsigned short data[], size_t len);

int InitIPRawSocket(in_addr_t dst, struct sockaddr_in *addr, socklen_t *len);
const char* GetIPByName(const char *name);
int GetInAddrByName(const char *name, in_addr_t *addrptr);
int HexToData(FILE *fp, unsigned char buf[], int bufsize);

#endif
