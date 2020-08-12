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

const char* GetIPByName(const char *name);
ushort CheckSum(unsigned short data[], size_t len);
int HexToData(FILE *fp, unsigned char buf[], int bufsize);

#endif
