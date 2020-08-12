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

// 可以发送的最大数据量
#ifndef BSZ
#define BSZ 4096
#endif

int SendIPData(unsigned char data[], int datalen);
// 设置 IP 的通用字段
void SetIPDftHdr(struct ip *ip);
ushort CheckSum(unsigned short data[], size_t len);

const char* GetIPByName(const char *name);
int GetInAddrByName(const char *name, in_addr_t *addrptr);
int HexToData(FILE *fp, unsigned char buf[], int bufsize);

#endif
