#include "unp.h"

int main(int argc, char **argv) {
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2) {
		err_quit("usage: a.out <IPaddress>");
	}
	// 创建套接字
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	// 配置套接字接口(协议、服务端口号、服务器地址)
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13); /* daytime server */
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	// 连接服务器
	Connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	// 读取数据
	while ((n = Read(sockfd, recvline, MAXLINE))!=0){
		recvline[n] = 0;
		Fputs(recvline, stdout);
	}
	return 0;
}
