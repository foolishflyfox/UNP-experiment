// fgets-test.c
#include <stdio.h>
#include <sys/select.h>
#include <errno.h>

int main(){
    fd_set rset;
    int fd = fileno(stdin);
    char buf[4096];
    FD_ZERO(&rset);
    for( int i=1; 1; i++){
        FD_SET(fd, &rset);
        if(select(fd+1, &rset, NULL, NULL, NULL)<0){
            if(errno == EINTR) continue;
            break;
        }
        if(FD_ISSET(fd, &rset)){
            if(fgets(buf, 4096, stdin))
                printf("%d: %s", i, buf);
            else
                break;
        }
    }
}
