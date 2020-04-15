// intro/experiment1-5/test-time.c
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    for(int i=0; i<5; ++i){
        printf("%ld %c", time(NULL), " \n"[i==4]);
        fflush(stdout);
        sleep(1);
    }
}
