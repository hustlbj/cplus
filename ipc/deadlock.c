/*-
 * Author: LBJ
 *
 * vi:set ts=4 sw=4:
 */
#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* not lint */

/**
 * @file	deadlock.c
 * @brief	
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ourheader.h"

static void lockabyte(const char*, int, off_t);

int
main(void)
{
	int fd;
	pid_t pid;

	if ((fd = open("templock", O_RDWR | O_CREAT)) < 0)
		err_quit("create error");
	if (write(fd, "ab", 2) != 2)
		err_quit("write error");
	TELL_WAIT();
	if ((pid = fork()) < 0)
		err_quit("fork error");
	else if (pid == 0)
	{
		lockabyte("child", fd, 0);
		TELL_PARENT(getppid());
		WAIT_PARENT();
		lockabyte("child", fd, 1);
	}
	else
	{
		lockabyte("parent", fd, 1);
		TELL_CHILD(pid);
		WAIT_CHILD();
		lockabyte("parent", fd, 0);
	}
	exit(0);
}

static void
lockabyte(const char *name, int fd, off_t offset)
{
	if (writew_lock(fd, offset, SEEK_SET, 1) < 0)
		err_quit("writew_lock error");
	printf("%s: got the lock, byte %d\n", name, offset);
}

