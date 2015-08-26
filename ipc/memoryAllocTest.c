/*-
 * Author: LBJ
 *
 * vi:set ts=4 sw=4:
 */
#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* not lint */

/**
 * @file	memoryAllocTest.c
 * @brief	
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "ourheader.h"

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE (SHM_R | SHM_W) 
char array[ARRAY_SIZE]; /*uninitialized global data -> bss*/

int 
main(void)
{
	int shmid;
	char *ptr, *shmptr;
	printf("array[] from %x to %x\n", &array[0], &array[ARRAY_SIZE]);
	printf("stack around %x\n", &shmid);
	if ((ptr = malloc(MALLOC_SIZE)) == NULL)
		err_quit("malloc error");
	printf("malloced from %x to %x \n", ptr, ptr+MALLOC_SIZE);
	if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
		err_quit("shmget error");
	if ((shmptr = shmat(shmid, 0, 0)) == (void *) -1)
		err_quit("shmat error");
	printf("shared memory attached from %x to %x \n",
			shmptr, shmptr+SHM_SIZE);
	if (shmctl(shmid, IPC_RMID, 0) < 0)
		err_quit("shmctl error");
	exit(0);
}
