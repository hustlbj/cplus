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

void err_quit(const char* message)
{
	perror(message);
	exit(1);
}

