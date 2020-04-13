// intro/experiment1-2/v1/test-fd.c
#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int file_fd = open("test-fd.c", O_RDONLY);
    int pipe_fds[2];
    pipe(pipe_fds);
    printf("%d, %d, %d, %d\n", socket_fd, file_fd, pipe_fds[0], pipe_fds[1]);
    while(1) sleep(1);
    return 0;    
}


