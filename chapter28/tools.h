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

const char* GetIPByName(const char *name);
ushort checksum(u_char data[], size_t len);

#endif
