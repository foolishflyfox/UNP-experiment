// dgcliloop1.c
#include "unp.h"

#define     NDG     2000    /* datagrams to send */
#define     DGLEN   1400    /* length of each datagram */

void dg_cli(FILE *_, int sockfd, const SA *pservaddr, socklen_t servlen){
    char sendline[DGLEN];
    for(int i=0; i<NDG; i++){
        Sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
    }
}
