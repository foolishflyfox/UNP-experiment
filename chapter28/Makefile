

CC = gcc

LIB_SRCS = tools.c
LIB_HEADS = tools.h

mk-icmptime: ip-recv.out icmptime-snd.out icmptime-rcv.out
	
icmptime-snd.out: icmptime-snd.c ${LIB_SRCS} ${LIB_HEADS}
	gcc $< ${LIB_SRCS} -o $@
icmptime-rcv.out: icmptime-rcv.c ${LIB_SRCS} ${LIB_HEADS}
	gcc $< ${LIB_SRCS} -o $@
ip-recv.out: ip-recv.c ${LIB_SRCS} ${LIB_HEADS}
	gcc $< ${LIB_SRCS} -o $@


