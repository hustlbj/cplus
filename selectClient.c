//:selectClient.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define BUF_LEN 1024
#define SERVER_PORT 6000

int main(int argc, char const **argv)
{
	int connfd;
	int message_len;
	struct sockaddr_in remote_addr;
	char buf[BUF_LEN];
	memset(&remote_addr, 0, sizeof(remote_addr));
	memset(buf, 0, BUF_LEN);
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	remote_addr.sin_port = htons(SERVER_PORT);
	connfd = socket(AF_INET, SOCK_STREAM, 0);
	if (connfd < 0)
	{
		//perror和strerror都是C语言提供的库函数，用于获取与errno相关的错误信息
		//不同的是perror向stderr输出结果，strerror(errno)向stdout输出结果
		perror("socket error!");
		return -1;
	}
	if (connect(connfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("connect error!");
		return -1;
	}
	printf("Connected! You can send message.\n");
	while(1)
	{
		gets(buf);
		if (strcmp(buf, "q") == 0)
		{
			write(connfd, buf, message_len);
			printf("Exit.\n");
			break;
		}
		if ((message_len = strlen(buf)) > 0)
		{
			write(connfd, buf, message_len);
			memset(buf, 0, BUF_LEN);
			message_len = read(connfd, buf, BUF_LEN);
			if (message_len > 0)
			{
				printf("Receive from server: %s\n", buf);
			}
		}
	}
	//客户端主动断开连接
	close(connfd);
	return 0;
}