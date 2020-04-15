// intro/experiment1-5/test-ctime.c
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    for(int i=0; i<5; ++i){
        time_t t = time(NULL);
        printf("%s", ctime(&t));
        sleep(1);
    }
}
