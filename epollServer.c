//:epollServer.c
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

/**
 int epoll_create(int size);创建一个epoll的句柄，size用来告诉内核需要建通的数目一共有多大，epoll句柄会占用一个fd值
 int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
 epoll的事件注册函数，第一个参数是创建的epoll句柄，第二个参数表示动作：
 EPOLL_CTL_ADD 注册新的fd到epfd中
 EPOLL_CTL_MOD 修改已经注册的fd的监听事件
 EPOLL_CTL_DEL 从epfd中删除一个fd
 第三个参数是需要监听的fd，第四个参数是告诉内核需要监听什么事
 struct epoll_event {
 	_unit32_t events;
 	epoll_data_t data;
 }
 events可以是一下几个宏的组合
 EPOLLOIN 表示对应的文件描述符可以读，包括对端的socket正常关闭
 EPOLLOUT 可写
 EPOLLPRI 有紧急的数据可读
 EPOLLERR 发生错误
 EPOLLHUP 被挂断
 EPOLLET  将EPOLL设为边缘触发，这是相对于水平触发来说的
 EPOLLONESHOT 只监听一次事件，完了还还需要监听这个fd的话需要重新加入到EPOLL队列里
 int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
 参数events用来从内核得到事件的集合，maxevents告知内核这个events有多大，timeout可以设超时毫秒或立即返回或阻塞，
 该函数返回要处理的事件数目，或者超时无事件0。

 水平触发：LT，默认工作方式，同时支持block和non-block socket，内核通知就绪以后如果不对就绪的fd进行IO操作，内核还是会继续通知你。
 边缘触发：ET，高速工作方式，只支持non-block socket，当描述符从未就绪变为就绪时，内核会通过epoll告诉你，以后不会再为那个文件描述符发送更多的就绪通知，
 直到下次有新的数据进来的时候才会再次触发就绪事件。
*/
#define SERV_PORT 6000
#define MAX_FD 1024
#define BUF_SIZE 1024
#define EVENTS_NUM 20
#define TIMEOUT 1000

void setnonblocking(int sock)
{
	int opts;
	opts = fcntl(sock, F_GETFL);
	if (opts < 0)
	{
		perror("fcntl(sock, GETFL)");
		exit(1);
	}
	opts = opts | O_NONBLOCK;
	if (fcntl(sock, F_SETFL, opts) < 0)
	{
		perror("fcntl(sock, SETFL, opts)");
		exit(1);
	}
}
int main(int argc, char** argv)
{
	int listenfd, connfd, sockfd, epfd, nfds, n = 0;
	char line[BUF_SIZE];
	socklen_t clilen;
	struct epoll_event ev, events[EVENTS_NUM];
	epfd = epoll_create(MAX_FD);
	struct sockaddr_in serveraddr, clientaddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	setnonblocking(listenfd);

	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;
	//注册epoll事件
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERV_PORT);
	bzero(line, BUF_SIZE);

	for (; ;)
	{
		//等待epoll事件的发生
		nfds = epoll_wait(epfd, events, EVENTS_NUM, TIMEOUT);
		for (int i = 0; i < nfds; i ++)
		{
			// 在listenfd上发生读事件，说明有新的客户端连接
			if (events[i].data.fd == listenfd)
			{
				connfd = accept(listenfd, (sockaddr * )&clientaddr, &clien);
				if (connfd < 0)
				{
					perror("accept error, connfd < 0");
				}
				setnonblocking(connfd);
				char *str = inet_ntoa(clientaddr.sin_addr);
				printf("Accept a connection from %s\n", str);
				//注册这个connfd的ev
				ev.data.fd = connfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);

			}
			//已连接的客户，收到数据
			else if (events[i].events & EPOLLIN)
			{
				printf("EPOLLIN\n");
				if ((sockfd = events[i].data.fd) < 0)
					continue;
				if ((n = read(sockfd, line, BUF_SIZE)) < 0)
				{
					if (errno == ECONNREST)
					{
						close(sockfd);
						events[i].data.fd = -1;
					}
					else
					{
						printf("Readline error\n");
					}
				}
				else if (n == 0)
				{
					close(sockfd);
					events[i].data.fd = -1;
				}
				else
				{
					line[n] = '\0';
					printf("Read from %d: %s\n", sockfd, line);

					//注册写操作事件
					ev.data.fd = sockfd;
					ev.events = EPOLLOUT | EPOLLET;
					epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
				}
			}
			//如果有数据要发送
			else if (events[i].events & EPOLLOUT)
			{
				sockfd = events[i].data.fd;
				write(sockfd, line, n);
				ev.data.fd = sockfd;
				ev.events = POLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
		}
	}

	return 0;
}