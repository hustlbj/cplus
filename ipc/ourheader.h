/*-
 * Author: LBJ
 *
 * vi:set ts=4 sw=4:
 *
 * $Id$
 */

/**
 * @file	ourheader.h
 * @brief	
 */
#ifndef _MY_HEADER_H
#define _MY_HEADER_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#define MAXLINE 1024
void TELL_WAIT();
void TELL_PARENT(pid_t pid);
void WAIT_PARENT();
void TELL_CHILD(pid_t pid);
void WAIT_CHILD();

void err_quit(const char* message);
int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);
pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len);

#define read_lock(fd,offset,whence,len) \
	lock_reg(fd,F_SETLK,F_RDLCK,offset,whence,len)
#define readw_lock(fd,offset,whence,len) \
	lock_reg(fd,F_SETLKW,F_RDLCK,offset,whence,len)
#define write_lock(fd,offset,whence,len) \
	lock_reg(fd,F_SETLK,F_WRLCK,offset,whence,len)
#define writew_lock(fd,offset,whence,len) \
	lock_reg(fd,F_SETLKW,F_WRLCK,offset,whence,len)
#define un_lock(fd,offset,whence,len) \
	lock_reg(fd,F_SETLK,F_UNLCK,offset,whence,len)
#define is_readlock(fd,offset,whence,len) \
	lock_test(fd,F_RDLCK,offset,whence,len)
#define is_writelock(fd,offset,whence,len) \
	lock_test(fd,F_WRLCK,offset,whence,len)

#endif
