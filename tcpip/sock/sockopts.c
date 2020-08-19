#include "sock.h"

void sockopts(int sockfd, int doall){
    int option;
    socklen_t optlen;
    if(debug){
        option = 1;
        if(setsockopt(sockfd, SOL_SOCKET, SO_DEBUG, &option, sizeof(option)) < 0){
            err_sys("SO_DEBUG setsockopt error");
        }
        option = 0;
        optlen = sizeof(option);
        if(getsockopt(sockfd, SOL_SOCKET, SO_DEBUG, &option, &optlen)<0)
            err_sys("SO_DEBUG getsockopt error");
        if(option == 1)
            err_quit("SO_DEBUG not set (%d)", option);
        if(verbose)
            fprintf(stderr, "SO_DEBUG set\n");
    }
    if(broadcast && doall){
        option = 1;
        if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &option, sizeof(option))<0)
            err_sys("SO_BROADCAST setsockopt error");
        option = 0;
        optlen = sizeof(option);
        if(getsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &option, &optlen)<0)
            err_sys("SO_BROADCAST getsockopt error");
        if(option==0)
            err_quit("SO_BROADCAST not set (%d)", option);
        if(verbose)
            fprintf(stderr, "SO_BROADCAST set\n");
    }
    if(keepalive && doall && udp==0){
        option = 1;
        if(setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &option, sizeof(option))<0)
            err_sys("SO_KEEPALIVE setsockopt error");
        option = 0;
        optlen = sizeof(option);
        if(getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &option, &optlen))
            err_sys("SO_KEEPALIVE getsockopt error");
        if(option == 0)
            err_quit("SO_KEEPALIVE not set (%d)", option);
        if(verbose)
            fprintf(stderr, "SO_KEEPALIVE set\n");
    }
    if(nodelay && doall && udp==0){
        option = 1;
        if(setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &option, sizeof(option))<0)
            err_sys("TCP_NODELAY setsockopt error");
        option = 0;
        optlen = sizeof(option);
        if(getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &option, &optlen)<0)
            err_sys("TCP_NODELAY getsockopt error");
        if(option==0)
            err_quit("TCP_NODELAY not set (%d)", option);
        if(verbose)
            fprintf(stderr, "TCP_NODELAY set\n");
    }
    if(doall && verbose && udp==0){  // 打印 MSS
        option = 0;
        optlen = sizeof(option);
        if(getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &option, &optlen)<0)
            err_sys("TCP_MAXSEG getsockopt error");
        fprintf(stderr, "TCP_MAXSEG = %d\n", option);
    }
    if(linger>=0 && doall && udp==0){
        struct linger ling;
        ling.l_onoff = 1;
        ling.l_linger = linger;
        if(setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &ling, sizeof(linger))<0)
            err_sys("SO_LINGER setsockopt error");
        ling.l_onoff = 0;
        ling.l_linger = -1;
        optlen = sizeof(ling);
        if(getsockopt(sockfd, SOL_SOCKET, SO_LINGER, &ling, &optlen)<0)
            err_sys("SO_LINGER getsockopt error");
        if(ling.l_onoff==0 || ling.l_linger!=linger)
            err_quit("SO_LINGER not set (%d, %d)", ling.l_onoff, ling.l_linger);
        if(verbose)
            fprintf(stderr, "linger %s, time = %d\n", ling.l_onoff?"on":"off", ling.l_linger);
    }
    if(recvdstaddr && udp){
#ifdef IP_RECVDSTADDR
        option = 1;
        if(setsockopt(sockfd, IPPROTO_IP, IP_RECVDSTADDR, &option, sizeof(option))<0)
            err_sys("IP_RECVDSTADDR setsockopt error");
        option = 0;
        optlen = sizeof(option);
        if(getsockopt(sockfd, IPPROTO_IP, IP_RECVDSTADDR, &option, &optlen)<0)
            err_sys("IP_RECVDSTADDR getsockopt error");
        if(option==0)
            err_quit("IP_RECVDSTADDR not set (%d)", option);
        if(verbose)
            fprintf(stderr, "IP_RECVDSTADDR set\n");
#else
        fprintf(stderr, "warning: IP_RECVDSTADDR not supported by host\n");
#endif
    }
}

