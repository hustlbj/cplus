/**
* fork构建最简单的并发服务器
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	int listenfd, connfd;
	int message_len = 0;
	char buf[128*1024];
	struct sockaddr_in server_sock, client_sock;
	memset(&server_sock, 0, sizeof(server_sock));
	memset(buf, 0, 128*1024);
	server_sock.sin_family = AF_INET;
	server_sock.sin_port = htons(8888);
	server_sock.sin_addr.s_addr = inet_addr("127.0.0.1");
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		perror("socket create error!");
		return -1;
	}
	if (bind(listenfd, (struct sockaddr * )&server_sock, sizeof(server_sock)) < 0)
	{
		perror("bind error!\n");
		return -1;
	}
	if (listen(listenfd, 8) == 0) 
	{
		socklen_t length = sizeof(client_sock);
		for (; ;) 
		{
			connfd = accept(listenfd, (struct sockaddr * )&client_sock, &length);
			printf("accept client %s: %d\n", inet_ntoa(client_sock.sin_addr), client_sock.sin_port);
			if ((pid = fork()) == 0)
			{   //子线程复制了主线程的listenfd和clientfd，所以先关掉listenfd
				close(listenfd);
				//message_len = send(connfd, "Welcome to my server\0", 21, 0);
				// recv or read
				message_len = recv(connfd, buf, 128*1024, 0);
				if (message_len > 0)
				{
					printf("Receive client message: %d\n", message_len);
				}
				close(connfd);
				exit(0);
			}
			//clientfd交给子线程处理后，主线程关掉自己内存中的clientfs
			close(connfd);
		}
	}

	return 0;
}
