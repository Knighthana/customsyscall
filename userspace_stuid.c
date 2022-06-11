/*
	Use: user space program for the project
	Stage-Commit: second commit
	Author: Knighthana
	Date: 2022/06/11
	Copyright (c) 2022 Knighthana 
*/
/*
	sys_customcall(struct customcallparamentstructure* paraSp);
	paraSp->ttystrlen:
		the length of ttyname string
    paraSp->ttystr:
        the ttyname in string. end with a '\0'
	paraSp->mode:
		mode % 2 != 0 : print the last 5 numbers of stuid
		mode % 2 == 0 : print the last 6 numbers of stuid
	paraSp->stuid:
		the source data for further change
*/


#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>
#include "userspace_stuid.h"

#define SYS_CUSTOMCALL_NO 451

int main(int argc, char* argv)
{
    int i;
    int len;
    char* ch_p;
    custompara_t paraS;
    for(i=0; i<16; i++){
        paraS.ttystr[i] = '\0';
    }
    if((ch_p = ttyname(STDOUT_FILENO)) == NULL){ /* if don't get the tty-name then quit */
        fprintf(stderr, "E: Invalid ttyname.\n");
        return 1;
    }
    else{ /* if get the tty-name, set its length and itself into the parament Structure */
        len = strlen(ch_p);
        paraS.ttystrlen = len;
        /* paraS.ttystr[len] = '\0'; */ /* might not needed anymore? */
        strncpy(paraS.ttystr, ch_p, len);
    }
    paraS.mode = 10;
    paraS.stuid = 88030120522;
    syscall(SYS_CUSTOMCALL_NO, &paraS);
    printf("\n");
    fflush;
    paraS.mode = 11;
    paraS.stuid = 88030120312;
    syscall(SYS_CUSTOMCALL_NO, &paraS);
    printf("\n");
    fflush;
    paraS.mode = 20;
    paraS.stuid = 20170198830;
    syscall(SYS_CUSTOMCALL_NO, &paraS);
    printf("\n");
    fflush;
    paraS.mode = 21;
    paraS.stuid = 20170198830;
    syscall(SYS_CUSTOMCALL_NO, &paraS);
    printf("\n");
    fflush;
    return 0;
}
