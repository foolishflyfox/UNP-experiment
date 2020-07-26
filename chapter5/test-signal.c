// test-signal.h
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>

void sigtstp(int signo){
    printf("enter sigtstp\n");
    sleep(5);
    printf("exit sigtstp\n");
}

int main(){
    if(signal(SIGTSTP, sigtstp)==SIG_ERR){
        perror("signal error"); return 1;
    }
    while(1) pause();
}



