/*-
 * Author: LBJ
 *
 * vi:set ts=4 sw=4:
 */
#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* not lint */

/**
 * @file	pipeTest.c
 * @brief	
 */

#include <stdio.h>
#include <unistd.h>
#include "ourheader.h"

int
main(void)
{
	int n, fd[2];
	pid_t pid;
	char line[MAXLINE];

	if (pipe(fd) < 0)
	{
		perror("pipe error");
	}
	if ( (pid = fork()) < 0 )
	{
		perror("foek error");
	}
	else if (pid > 0) //parent
	{
		close(fd[0]);
		write(fd[1], "hello world\n", 12);
	}
	else  //child
	{
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
	}
	exit(0);
}

