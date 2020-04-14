// intro/experiment1-2/v2/text-colors.c
#include <stdio.h>

int main(){
    printf("背景色:\n");
    for(int i=40; i<49; ++i){
        printf("%d\033[%d;30m  \033[0m %c", i, i, " \n"[i==48]);
    }
    printf("文本色:\n");
    for(int i=30; i<39; ++i){
        printf("\033[%dm  %d \033[0m%c", i, i, " \n"[i==38]);
    }
}
