/*-
 * Copyright (C), 1988-2012, mymtom
 *
 * vi:set ts=4 sw=4:
 */
#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* not lint */

/**
 * @file	udpServer.c
 * @brief	
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define SERVER_PORT 6001
#define BUF_LEN 128*1024
int main(int argc, char ** argv)
{
	int socketfd;
	char buf[BUF_LEN];
	struct sockaddr_in address;
	socklen_t sock_len;
	int message_len = 0;
	
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("172.31.11.211");
	address.sin_port = htons(SERVER_PORT);
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(socketfd, (struct sockaddr *)&address, sizeof(address) );
	while(1)
	{
		memset(buf, 0, BUF_LEN);
		message_len = recvfrom(socketfd, buf, BUF_LEN, 0, (struct sockaddr *)&address, &sock_len);
	  	if (message_len > 0)
		{
			printf("Received: %d\n", message_len);
			if (strncmp(buf, "exit", 4) == 0)
			{
				printf("Closed..\n");
				break;
			}
		}
	}
	close(socketfd);
	return EXIT_SUCCESS;
}

