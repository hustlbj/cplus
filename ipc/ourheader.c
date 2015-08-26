/*-
 * Author: LBJ
 *
 * vi:set ts=4 sw=4:
 */
#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* not lint */

/**
 * @file	ourheader.c
 * @brief	
 */

#include <stdio.h>
#include "ourheader.h"
static int fd1[2], fd2[2];

void TELL_WAIT()
{
	if (pipe(fd1) < 0 || pipe(fd2) < 0)
			err_quit("pipe error");
}
void TELL_PARENT(pid_t pid)
{
	if (write(fd1[1], "c", 1) != 1)
		err_quit("TELL_PARENT write error");
}
void WAIT_CHILD()
{
	char c;
	if (read(fd1[0], &c, 1) != 1)
		err_quit("WAIT_CHILD read error");
}
void TELL_CHILD(pid_t pid)
{
	if (write(fd2[1], "p", 1) != 1)
		err_quit("TELL_CHILD write error");
}
void WAIT_PARENT()
{
	char c;
	if (read(fd2[0], &c, 1) != 1)
		err_quit("WAIT PARENT read error");
}

void 
err_quit(const char* message)
{
	perror(message);
	exit(1);
}


int
lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;
	return (fcntl(fd, cmd, &lock));
}

pid_t
lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;
	if (fcntl(fd, F_GETLK, &lock) < 0)
		err_quit("fcntl error");
	if (lock.l_type == F_UNLCK)
		return(0); /* false, region is not looked by another proc */
	return(lock.l_pid); /* true, return pid of lock owner */
}
