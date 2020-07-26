// Fork.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

pid_t Fork(void){
    pid_t pid = fork();
    if(pid < 0) { perror("fork error"); exit(1); }
    return pid;
}

