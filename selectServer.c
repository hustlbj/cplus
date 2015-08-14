//:selectServer.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUF_LEN 1024
#define SERV_PORT 6000
#define FD_SIZE 100
#define MAX_BACK 100

int main(int argc, char **argv)
{
	int listenfd, connfd, sockfd, maxfd, maxi, i;
	int nready, client[FD_SIZE]; //接收select返回值，保存客户端套接字
	int lens;
	size_t n; //read字节数
	//fd_set的数据结构，实际上是一long类型的数组，
	//每一个数组元素都能与一打开的文件句柄（不管是socket句柄，还是其他文件或命名管道或设备句柄）建立联系
	fd_set rset, allset;
	char buf[BUF_LEN];
	socklen_t clilen;
	struct sockaddr_in servaddr, cliaddr;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("Create socket Error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	//bzero是传统BSD函数，属于POSIX标准，使用头文件string.h，bzero无返回值，推荐使用memset替代bzero
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1)
	{
		printf("Bind Error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	if (listen(listenfd, MAX_BACK) == -1)
	{
		printf("Listen Error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	maxfd = listenfd;
	maxi = -1;
	for(i = 0; i < FD_SIZE; i ++)
	{
		client[i] = -1;
	}
	FD_ZERO(&allset);
	//把服务端侦听的listenfd放到allset中
	FD_SET(listenfd, &allset);

	while(1)
	{
		rset = allset;
		//select(最大句柄数+1, 监视的文件句柄集合, 写, 异常, 超时)
		if ((nready = select(maxfd + 1, &rset, NULL, NULL, NULL)) == -1)
		{
			printf("Select Error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		if (nready <= 0)
		{
			continue;
		}

		//如果是侦听的listenfd就绪，则说明是有新的连接进入
		if(FD_ISSET(listenfd, &rset))
		{
			clilen = sizeof(cliaddr);
			printf("Start doing...\n");
			//新连接
			if ((	) == -1)
			{
				printf("Accept Error: %d\n", errno);
				continue;
			}
			for (i = 0; i < FD_SIZE; i ++)
			{
				//保存这个新的client fd
				if (client[i] < 0)
				{
					client[i] = connfd;
					break;
				}
			}
			if (i == FD_SIZE)
			{
				printf("To many clients...Reject\n");
				close(connfd);
				continue;
			}
			FD_SET(connfd, &allset);
			if (connfd > maxfd)
			{
				maxfd = connfd;
			}
			if (i > maxi)
			{
				maxi = i;
			}
		}

		//否则轮训一遍，看看是哪个客户端socket的读就绪
		for (i = 0; i <= maxi; i ++)
		{
			if ((sockfd = client[i]) > 0)
			{
				if (FD_ISSET(sockfd, &rset))
				{
					memset(buf, 0, sizeof(buf));
					n = read(sockfd, buf, BUF_LEN);
					if (n < 0)
					{
						printf("Error!\n");
						close(sockfd);
						FD_CLR(sockfd, &allset);
						client[i] = -1;
						continue;
					}
					if (n == 0)
					{
						printf("No data\n");
						//close(sockfd);
						//FD_CLR(sockfd, &allset);
						//client[i] = -1;
						continue;
					}

					printf("Server Recv: %s\n", buf);
					if (strcmp(buf, "q") == 0)
					{
						close(sockfd);
						FD_CLR(sockfd, &allset);
						client[i] = -1;
						continue;
					}
					printf("Server send: %s\n", buf);
					write(sockfd, buf, n);
				}
			}
		}
	}
	return 0;
}