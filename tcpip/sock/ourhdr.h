#ifndef __ourhdr_h
#define __ourhdr_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void err_msg(const char*, ...);
void  err_quit(const char *fmt, ...);

#define MAXLINE 4096    /* max line size */

#endif


