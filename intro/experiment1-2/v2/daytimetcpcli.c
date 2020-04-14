// intro/experiment1-2/v2/daytimetcpcli.c
#include "unp.h"

int main(int argc, char **argv) {
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2) {
		err_quit("usage: a.out <IPaddress>");
	}
	// 创建套接字
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))==-1){
		err_sys("socket error");
	}
	// 配置套接字接口(协议、服务端口号、服务器地址)
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13); /* daytime server */
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0){
		err_quit("inet_pton error for %s", argv[1]);
	}
	// 连接服务器
	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0){
		err_sys("connect error");
	}
	// 读取数据
	while ((n = read(sockfd, recvline, MAXLINE)) > 0){
		recvline[n] = 0;
		if(fputs(recvline, stdout)==EOF){
			err_sys("fputs error");
		}
	}
	if(n < 0) {
		err_sys("read error");
	}
	return 0;
}
