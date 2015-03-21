/**
* socket client
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int connfd;
	int message_len;
	struct sockaddr_in remote_addr;
	char buf[2048];
	memset(&remote_addr, 0, sizeof(remote_addr));
	memset(buf, 0, 2048);
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	remote_addr.sin_port = htons(8888);
	connfd = socket(AF_INET, SOCK_STREAM, 0);
	if (connfd < 0)
	{
		perror("socket error!");
		return -1;
	}
	if (connect(connfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("connect error!");
		return -1;
	}
	message_len = recv(connfd, buf, 2048, 0);
	buf[message_len] = '\0';
	printf("Receive from server: %s\n", buf);
	close(connfd);
	return 0;
}