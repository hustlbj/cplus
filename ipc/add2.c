/*-
 * Author: LBJ
 *
 * vi:set ts=4 sw=4:
 */
#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* not lint */

/**
 * @file	add2.c
 * @brief	
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ourheader.h"
int 
main(void)
{
	int n, int1, int2;
	char line[MAXLINE];
	while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0)
	{
		line[n] = 0;
		if (sscanf(line, "%d%d", &int1, &int2) == 2)
		{
			sprintf(line, "%d\n", int1 + int2);
			n = strlen(line);
			if (write(STDOUT_FILENO, line, n) != n)
				err_quit("write error");
		}
		else
		{
			if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
				err_quit("write error");
		}
	}
	exit(0);
}


