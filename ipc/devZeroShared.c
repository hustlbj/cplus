/*-
 * Author: LBJ
 *
 * vi:set ts=4 sw=4:
 */
#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* not lint */

/**
 * @file	devZeroShared.c
 * @brief	
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h> //pipe
#include "ourheader.h"

#define NLOOPS 1000
#define SIZE sizeof(long) /*size of shared memory area*/
/*
static int pfd1[2], pfd2[2];
void TELL_WAIT()
{
	if (pipe(pfd1) < 0 || pipe(pfd2) < 0)
		err_quit("pipe error");
}
void TELL_PARENT(pid_t pid)
{
	if (write(pfd2[1], "c", 1) != 1)
		err_quit("write pipe error");
}
void WAIT_PARENT()
{
	char c;
	if (read(pfd1[0], &c, 1) != 1)
		err_quit("read pipe error");
	if (c != 'p')
		printf("WAIT_PARENT: incorrect data\n");
}
void TELL_CHILD(pid_t pid)
{
	if (write(pfd1[1], "p", 1) != 1)
		err_quit("write pipe error");
}
void WAIT_CHILD()
{
	char c;
	if (read(pfd2[0], &c, 1) != 1)
		err_quit("read pipe error");
	if (c != 'c')
		printf("WAIT_CHILD: incorrect data: %c\n", &c);
}
*/
static int update(long *);

int 
main()
{
	int fd, i, counter;
	pid_t pid;
	caddr_t area; /*in types.h, char * */
	if ((fd = open("/dev/zero", O_RDWR)) < 0)
	{
		err_quit("open error");
	}
	//在/dev/zero处映射long这么大的空间，初始化成0
	if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == (caddr_t) -1)
	{
		err_quit("mmap error");
	}
	close(fd);

	TELL_WAIT();
	if ((pid = fork()) < 0)
		err_quit("fork error");
	else if (pid > 0) /*parent*/
	{
		for (i = 0; i < NLOOPS; i +=2)
		{
			//对共享存储区中的值不断更新
			if ((counter = update((long *) area)) != i)
			{
				err_quit("parent: counter error" );
			}
			//通知child进程对共享存储区中的值更新
			TELL_CHILD(pid);
			WAIT_CHILD();
		}
	}
	else /*child*/
	{
		for(i = 1; i < NLOOPS + 1; i += 2)
		{
			WAIT_PARENT();
			if ((counter = update((long *) area)) != i)
				err_quit("child: counter error");
			TELL_PARENT(getppid());
		}
	}
	printf("counter: %d\n", counter);
	exit(0);
}

static int
update(long * ptr)
{
	return ((*ptr)++);
}

