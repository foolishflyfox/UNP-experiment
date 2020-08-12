// ping-main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

int verbose;
char *host;
pid_t pid;
int sockfd;

void sig_alrm(int signo){
    alarm(1);
    return;
}
// 根据域名获取IP地址
const char* GetIPByName(const char *name){
    static char str[INET_ADDRSTRLEN];
    struct hostent *hptr = gethostbyname(name);
    if(hptr == NULL){
        fprintf(stderr, "GethostnameStr: gethostbyname error for host %s: %s\n",
            name, hstrerror(h_errno));
        exit(1);
    }
    char **pptr = hptr->h_addr_list;
    if(hptr->h_addrtype!=AF_INET || *pptr == NULL) {
        fprintf(stderr, "GethostnameStr: Can't get IP of %s\n", name);
        exit(1);
    }
    return inet_ntop(AF_INET, *pptr, str, sizeof(str));
}
void readloop(){
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if(sockfd==-1) { perror("socket error"); exit(1); }
    // 本程序需要以超级用户创建原始套接字，完成创建后退出超级用户模式
    setuid(getuid());
    // 设置接收缓冲区的大小，设置失败也没关系
    int size = 60 * 1024;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
    sig_alrm(SIGALRM);  // 发送第一个数据报
    
}

int main(int argc, char *argv[]){
    int c, datalen;
    opterr = 0;  // don't want getopt() writing to stderr
    while((c = getopt(argc, argv, "v"))!=-1){
        switch(c){
            case 'v': verbose++; break;
            case '?':
                fprintf(stderr, "unrecognized option: %c\n", c);
                exit(1);
        }
    }
    if(optind != argc-1){
        fprintf(stderr, "usage: ping [-v] <hostname>\n"); exit(1);
    }
    host = argv[optind];
    pid = getpid() & 0xFFFF;  // ICMP ID field is 16 bits
    if(SIG_ERR==signal(SIGALRM, sig_alrm)){
        perror("signal error"); exit(1);
    }
    printf("PING %s (%s): 56 data bytes\n", host, GetIPByName(host));
}

