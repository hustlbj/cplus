/*-
 * Author: LBJ
 *
 * vi:set ts=4 sw=4:
 */
#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* not lint */

/**
 * @file	coprocessTest.c
 * @brief	
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "ourheader.h"

static void sig_pipe(int); /*our signal handler*/

int
main(void)
{
	int n, fd1[2], fd2[2];
	pid_t pid;
	char line[MAXLINE];
	if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_quit("signal error");
	// 创建两个管道
	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		err_quit("pipe error");
	if ( (pid = fork()) < 0)
		err_quit("fork error");
	//父、子进程各自关闭他们不需要的端口
	//创建两个管道的理由是：一个用作协同进程的标准输入，另一个则用作它的标准输出。
	else if (pid > 0) //parent
	{
		close(fd1[0]);
		close(fd2[1]);
		while (fgets(line, MAXLINE, stdin) != NULL)
		{
			n = strlen(line);
			if (write(fd1[1], line, n) != n)
				err_quit("write error to pipe");
			if ((n = read(fd2[0], line, MAXLINE)) < 0)
				err_quit("read error from pipe");
			if (n == 0)
			{
				err_quit("child closed pipe");
			}
			line[n] = 0;
			if (fputs(line, stdout) == EOF)
				err_quit("fputs error");
			if (ferror(stdin))
				err_quit("fgets error on stdin");
			exit(0);
		}
	}
	else //child
	{
		close(fd1[1]);
		close(fd2[0]);
		if (fd1[0] != STDIN_FILENO)
		{
			//子进程调用dup2使管道描述符移至其标准输入和输出
			if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				err_quit("sup2 error to stdin");
			close(fd1[0]);
		}
		if (fd2[1] != STDOUT_FILENO)
		{
			if (dup2(fd2[0], STDOUT_FILENO) != STDOUT_FILENO)
				err_quit("sup2 error to stdin");
			close(fd2[0]);
		}
		if (execl("./add2", "add2", (char *) 0) < 0)
			err_quit("execl error");
	}
}

static void
sig_pipe(int signo)
{
	printf("SIGPIPE cought\n");
	exit(1);
}
