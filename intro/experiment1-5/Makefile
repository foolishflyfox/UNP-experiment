# intro/experiment1-5/Makefile

unp_source = error.c wraplib.c wrapsock.c wrapstdio.c wrapunix.c
targets = srv.out cli.out

all: $(targets)

cli.out: daytimetcpcli.c $(unp_source)
	gcc $^ -o $@
srv.out: daytimetcpsrv.c $(unp_source)
	gcc $^ -o $@


