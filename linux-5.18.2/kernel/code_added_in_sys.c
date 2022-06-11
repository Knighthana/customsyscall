/*
	le personnalisé fonction
*/
SYSCALL_DEFINE3(customcall, int, chotty, int, mode, long, stunum)
{
	struct file* fp;
	loff_t pos = 0;
	int  i = 0, j = 0, onenum;
	char tempstr[16];
	char stunstr[16];
	tempstr[15] = 0;
	stunstr[15] = 0;
	if(chotty == 0){
		fp = filp_open("/dev/tty1", O_RDWR, 0);
		printk(KERN_ALERT"Choosed to print on /dev/tty1\n");
	}
    else{
        fp = filp_open("/dev/pts/0", O_RDWR, 0);
		printk(KERN_ALERT"Choosed to print on /dev/pts/0\n");
    }
	do{
		onenum = (int)(stunum % 10);
		tempstr[i] = (char)onenum + '0';
		stunum /= 10;
		i++;
	}
	while(stunum != 0 && i < 15);
	if(mode % 2 != 0){ /* situation odd number */
		i = 5 - 1;
	}
	else{ /* situation even number */
		i = 6 - 1;
	}
	if(i + 1 < 16){ /* éviter de débordement de tableau */
		stunstr[i+1] = '\0';
	}
	for(; i>-1; i--, j++){ /* 'i' indicate the pos in tempstr to read, and 'j' indicate the pos in stunstr to write */
		stunstr[j] = tempstr[i];
	}
	stunstr[j] = '\0';
	printk(KERN_ALERT"The String should be shown on tty will be %s.\n", stunstr);
	kernel_write(fp, stunstr, j+1, &pos);
	filp_close(fp, NULL);
	return 0;
}

