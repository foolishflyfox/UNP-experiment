// 4-13.c
#include "unp.h"

int main(){
    pid_t pid;
    int listenfd, connfd;
    listenfd = Socket( ... );
    /* fill in sockaddr_in with server's well-known port */
    Bind(listenfd, ...);
    Listen(listenfd, LISTENQ);
    for( ; ; ){
        connfd = accept(listenfd, ...); /* probably blocks */
        if((pid = fork()) == 0){
            Close(listenfd);    /* child closes listening socket */
            doit(connfd);       /* process the request */
            Close(connfd);      /* done with this client */
            exit(0);            /* child terminates */
        }
        Close(connfd);
    }
}
