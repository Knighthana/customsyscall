/*
	le personnalis√© fonction
*/
#ifndef __KHN____CUSTOM_SYSCALL_STRUCTURES___
#define __KHN____CUSTOM_SYSCALL_STRUCTURES___
typedef struct customcallparamentstructure{
    int ttystrlen;
    char ttystr[16];
    int mode;
    long stuid;
}custompara_t;
#endif
asmlinkage long sys_customcall(custompara_t* paraSp);
/*
	le personnalis√© fonction fin
*/
