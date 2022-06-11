/*
	Use: user space program for the project
	Stage-Commit: first release
	Author: Knighthana
	Date: 2022/06/10
	Copyright (c) 2022 Knighthana 
*/
/*
	sys_customcall(int ttyno, int mode, long stuid);
	ttyno:
		ttyno == 0 : print on /dev/tty1
		ttyno != 0 : print on /dev/pts/0
	mode:
		mode % 2 != 0 : print the last 5 numbers of stuid
		mode % 2 == 0 : print the last 6 numbers of stuid
	stuid:
		the source data for further change
*/

#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define SYS_CUSTOMCALL_NO 451

int main(int argc, char* argv)
{
	printf("This project based on the previous work from kernel.org, and release as GPL2.0.\n");
	syscall(SYS_CUSTOMCALL_NO, 1, 11, 88030120522);
	fflush;
	printf("\n");
	syscall(SYS_CUSTOMCALL_NO, 1, 12, 88030120312);
	fflush;
	return 0;
}
