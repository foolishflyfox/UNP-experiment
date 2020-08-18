#include "sock.h"

// 定义全局变量
// 套接字参数
int client = 1;     // 作为客户端启动
int server;         // 作为服务器启动
int udp;            // 是否使用 UDP 协议, 默认 TCP
char *host;
char *port;
char foreignip[32];
int foreignport;
int dofork;         // 通过 fork 创建并行服务器，默认 select 迭代

// 套接字选项
int reuseaddr;      // 使能 SO_REUSEADDR 选项
int broadcast;      // 使能 SO_BROADCAST 选项
int debug;          // 使能 SO_DEBUG 选项
int recvdstaddr;    // 使能 SO_RECVDSTADDR 选项
int keepalive;      // 使能 SO_KEEPALIVE 选项
long linger = -1;         // 使能 SO_LINGER 选项的整型参数
int nodelay;        // 使能 SO_NODELAY
int rcvbuflen;      // SO_RCVBUF 要指定的接收缓冲区大小
int sndbuflen;      // SO_SNDBUF 要制定的发送缓冲区大小
int urgwrite;       // 何时写紧急字节

// 连接控制参数
int bindport;       // 为 0 或为希望绑定的端口号(UDP/TCP)
int listenq = 5;    // TCP 侦听队列的最大长度(已连接但未accept描述符的最大数量)
int halfclose;      // TCP 半连接选项
int pauserw;        // 读/写 结束后阻塞的秒数
int pauselisten;    // 指定在 listen 函数调用后 accept 调用前暂停的秒数
int pauseinit;      // 指定在首次调用 read 前暂停的秒数
int pauseclose;     // 指定在收到 FIN 后，在调用 close 函数前暂停的秒数

// 数据处理参数
int nbuf = 1024;    // 输出模式下，write 调用的次数
int readlen = 1024; // read() 函数指定的大小
int writelen = 1024;// write() 函数指定的大小
int crlf;           // 用于 \r\n 与 \n 的互转(多用于 Windows)
int verbose;        // 显示正在进行的处理信息

// 程序全局变量
char *rbuf;         // 指向用 malloc 开辟的堆空间，用于读缓冲区
char *wbuf;         // 指向用 malloc 开辟的堆空间，用于写缓冲区

int sourcesink;
int cbreak;

static void usage(const char *);

int main(int argc, char *argv[]){
    int c, fd;
    char *ptr;

    if(argc < 2) usage("");
    opterr = 0;  // 匹配出错时，禁止系统向stderr输出错误信息
    while((c = getopt(argc, argv, "b:cf:hin:p:q:r:suvw:ABCDEFKL:NO:P:Q:R:S:U:"))!=EOF){
        switch(c){
            case 'b':   // 绑定端口
                bindport = atoi(optarg);
                break;
            case 'c':
                crlf = 1;
                break;
            case 'f':   // 指定套接字
                if((ptr = strrchr(optarg, '.')) == NULL)
                    usage("invalid -f option");
                *ptr++ = 0;
                foreignport = atoi(ptr);
                strcpy(foreignip, optarg);
                break;
            case 'h':   // TCP 半关闭选项
                halfclose = 1;
                break;
            case 'i':  // source/sink option
                sourcesink = 1;
                break;
            case 'n':
                nbuf = atoi(optarg);
                break;
            case 'p':
                pauserw = atoi(optarg);
                break;
            case 'q':
                listenq = atoi(optarg);
                break;
            case 'r':
                readlen = atoi(optarg);
                break;
            case 's':
                server = 1;
                client = 0;
                break;
            case 'u':
                udp = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'w':
                writelen = atoi(optarg);
                break;
            case 'A':
                reuseaddr = 1;
                break;
            case 'B':
                broadcast = 1;
                break;
            case 'C':
                cbreak = 1;
                break;
            case 'D':
                debug = 1;
                break;
            case 'E':
                recvdstaddr = 1;
                break;
            case 'F':
                dofork = 1;
                break;
            case 'K':
                keepalive = 1;
                break;
            case 'L':
                linger = atol(optarg);
                break;
            case 'N':
                nodelay = 1;
                break;
            case 'O':
                pauselisten = atoi(optarg);
                break;
            case 'P':
                pauseinit = atoi(optarg);
                break;
            case 'Q':
                pauseclose = atoi(optarg);
                break;
            case 'R':
                rcvbuflen = atoi(optarg);
                break;
            case 'S':
                sndbuflen = atoi(optarg);
                break;
            case 'U':
                urgwrite = atoi(optarg);
                break;
            case '?':
                usage("unrecognized option");
        }
    }
    // 判断选项间是否存在冲突
    if(udp && halfclose) usage("can't specify -h and -v");
    if(udp && debug) usage("can't specify -D and -u");
    if(udp && linger >=0) usage("can't specify -L and -u");
    if(udp && nodelay) usage("can't specify -N and -u");
    if(udp==0 && broadcast) usage("can't specify -B and TCP");
    if(udp==0 && foreignip[0]!=0)  // 服务器不能指定对端IP,只能被动打开
        usage("can't specifi -f with TCP");
    if(client){
        if(argc-optind!=2)
            usage("missing <hostname> and/or <port>");
        host = argv[optind];
        port = argv[optind+1];
    }else{
        if(optind == argc-2){
            host = argv[optind];
            port = argv[optind+1];
        }else if(optind == argc-1){
            host = NULL;
            port = argv[optind];
        }else
            usage("missing <port>");
    }
    if(client)
        fd = cliopen(host, port);
    else
        fd = servopen(host, port);
    if(sourcesink)
        sink(fd);
    else
        loop(fd);
}

static void usage(const char *msg){
    err_msg(
"usage: sock [ options ] <host> <port>              (for client; default)\n"
"       sock [ options ] -s [ <IPaddr> ] <port>     (for server)\n"
"       sock [ options ] -i <host> <port>           (for \"source\" client)\n"
"       sock [ options ] -i -s [ <IPaddr> ] <port>  (for \"sink\" server)\n"
"options:   -b n    bind n as client's local port number\n"
"           -c      convert newline to CR/LF & vice versa \n"
"           -f a.b.c.d.p  foreign IP address = a.b.c.d, foreign port# = p\n"
"           -h      issue TCP half close on standard input EOF\n"
"           -i      \"source\" data to socket, \"sink\" data from socket (w/-s)\n"
"           -n n    #buffers to write for \"source\" client (default 5)\n"
"           -p n    #seconds to pause before each read or write(source/sink)\n"
"           -q n    size of listen queue for TCP server(default 5)\n"
"           -r n    #bytes per read() for \"sink\" server (default 1024\n"
"           -s      operate as server instead of client\n"
"           -u      use UDP instead of TCP\n"
"           -v      verbose\n"
"           -w n    #bytes per write() for \"source\" client (default 1024)\n"
"           -A      SO_REUSEADDR option\n"
"           -B      SO_BROADCAST option\n"
"           -C      set terminal to cbreak mode\n"
"           -D      SO_DEBUG option\n"
"           -E      IP_RECVDSTADDR option\n"
"           -F      fork after connection accepted (TCP concurrent server)\n"
"           -K      SO_KEEPALIVE option\n"
"           -L n    SO_LINGER option, n = linger time\n"
"           -N      TCP_NODELAY option\n"
"           -O n    #seconds to pause after listen, but before first accept\n"
"           -P n    #seconds to pause before first read or write (source/sink)\n"
"           -Q n    #seconds to pause after receiving FIN, but before close\n"
"           -R n    SO_RCVBUF option\n"
"           -S n    SO_SNDBUF option\n"
"           -U n    enter urgent mode after write number n(source only)"
    );
    if(msg!=NULL && msg[0]!='\0') err_quit(msg);
    exit(1);
}


