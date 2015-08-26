/*-
 * Author: LBJ
 *
 * vi:set ts=4 sw=4:
 */
#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* not lint */

/**
 * @file	udpClient.cpp
 * @brief	
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 6001
#define BUF_LEN 128*1024

using namespace std;

int main(int argc, char ** argv)
{
	int socketfd;
	char buf[BUF_LEN];
	struct sockaddr_in address;
	int send_size = 0, max_size=65536;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("172.31.11.211");
	address.sin_port = htons(SERVER_PORT);
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	//while (1)
//	{
		memset(buf, 63, BUF_LEN);
		//fgets(buf, BUF_LEN, stdin);
		send_size = sendto(socketfd, buf, sizeof(buf), 0, (struct sockaddr *)&address, sizeof(address));
		while (send_size == -1)
		{
			fprintf(stderr, "Error: %s\n", strerror(errno));
			send_size = sendto(socketfd, buf, max_size, 0, (struct sockaddr *) &address, sizeof(address));
			printf("retry size: %d\n", max_size);
			max_size --;
		}
		if (send_size > 0)
			printf("Send size: %d\n", send_size);
		//if (strncmp(buf, "exit", 4) == 0)
	//	{
	//		printf("Exit...\n");
	//		break;
	//	}
	//}
	close(socketfd);
	return EXIT_SUCCESS;
}
