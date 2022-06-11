/*
	le personnalisé fonction
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
SYSCALL_DEFINE1(customcall, custompara_t*, paraSp)
{
	struct file* fp;
	loff_t pos = 0;
	int  i = 0, j = 0, onenum;
	int mode;
	long stuid;
	char tempstr[16];
	char stunstr[16];
	/*
		all declare check.
	*/
	mode = paraSp->mode;
	stuid = paraSp->stuid;
	fp = filp_open(paraSp->ttystr, O_RDWR, 0);
	printk(KERN_ALERT"Choosed to print on %s\n", paraSp->ttystr);
	do{
		onenum = (int)(stuid % 10);
		tempstr[i] = (char)onenum + '0';
		stuid /= 10;
		i++;
	}
	while(stuid > 0 && i < 15);
	/*
		if stuid is larger than 1x10^15, the numbers larger will be cut and out of think
		(so why not only take max-to-6 numbers? cause we only need 5 or 6 numbers) - lazy to do it
	*/
	tempstr[15] = '\0';
	if(mode % 2 != 0){ /* situation odd number */
		i = 5 - 1; /* if mode is odd, need to printf 5 numbers as char string */
	}
	else{ /* situation even number */
		i = 6 - 1;
	}
	for(; i>-1; i--, j++){ /* 'i' indicate the pos in tempstr to read, and 'j' indicate the pos in stunstr to write */
		stunstr[j] = tempstr[i];
	}
	stunstr[j] = '\0'; /* éviter de débordement de tableau */
	printk(KERN_ALERT"The String should be shown on tty will be %s.\n", stunstr);
	kernel_write(fp, stunstr, j+1, &pos);
	filp_close(fp, NULL);
	return 0;
}
/*
	le personnalisé fonction fin
*/
