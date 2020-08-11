// connect_timeo.c
#include "unp.h"

static void sig_alrm(int signo){ return; }

int connect_timeo(int sockfd, const SA *addr, socklen_t len, int nsec){
    int n;
    Sigfunc *sigfunc = Signal(SIGALRM, sig_alrm);
    if(alarm(nsec)!=0)
        fprintf(stderr, "connect_timeo: alarm was already set\n");
    if((n = connect(sockfd, addr, len)) < 0){
        close(sockfd);
        if(errno == EINTR)
            errno = ETIMEDOUT;
    }
    alarm(0);  // turn off the alarm
    Signal(SIGALRM, sigfunc);
    return n;
}

