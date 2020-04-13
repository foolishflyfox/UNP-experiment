// intro/experiment1-2/v1/daytimetcpcli.c
#include <stdio.h>
#include <netinet/in.h>    // sockaddr_in
#include <string.h>        // bzero
#include <arpa/inet.h>     // inet_pton
#include <unistd.h>        // read

#define MAXLINE 4096 /* max text line length */

int main(int argc, char **argv) {
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2){
		printf("usage: a.out <IPaddress>\n");
		return 1;
	}
	// 创建套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// 配置套接字接口(协议、服务端口号、服务器地址)
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13); /* daytime server */
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	// 连接服务器
	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	// 读取数据
	while ((n = read(sockfd, recvline, MAXLINE)) > 0){
		recvline[n] = 0; /* null terminate */
		fputs(recvline, stdout);
	}
	return 0;
}
