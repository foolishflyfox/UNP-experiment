# 可以根据系统改变下列选项
CC = gcc
CFLAGS = -Wall

PROGS = sock
OBJS = error.o main.o cliopen.o servopen.o buffers.o \
		sockopts.o tellwait.c sourcesink.o loop.c crlf.c writen.c
LIBS = 

all: ${PROGS}

${OBJS}: sock.h ourhdr.h

sock: ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS}

clean:
	rm -f ${PROGS} core core.* *.o temp.* *.out typescript*

