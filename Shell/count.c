#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void count (char c,char*fn)
{
	int lc=0,wc=0,cc=0,fd;
	char ch;
	fd=open(fn,O_RDONLY);
	if(fd==-1)
	{
		printf("file%snot found\n");
		return;
	}
	while(read(fd,&ch,1)!=0)
	{
		if(ch==' '|| ch=='\t')
		{
			wc++;
		}
		else if(ch=='\n')
		{
			lc++;
			wc++;
		}
		else 
		{	cc++;
		}
 	}
        close(fd);
	switch(c)
	{
		case 'c':
			printf("Total No, of Characters%d\n",cc);
			break;
		case 'w':
			printf("Total No.of Words%d\n",wc);
			break;
		case 'l':
			printf("Total No.of Line%d\n",lc);
			break;
	}
}
main()	
{
	char buff [80],t1[20],t2[20],t3[20],t4[20];
	int n,pid,k=0,status;
	system("clear");
	while(1)
	{
		printf("my shell$");
		fflush(stdin);
		fgets(buff,80,stdin);
		t1[0]=t2[0]=t3[0]=t4[0]='\0';
		n=sscanf(buff,"%s%s%s%s",t1,t2,t3,t4);
		if(strcmp(t1,"exit")==0)
			exit(0);
		if(strcmp(t1,"count")==0)
        {
                count(t2[0],t3);
        }

		else if (pid=fork()==0)
			switch(n)
			{
				case 1:execlp(t1,t1,(char *)0);
				       break;
				case 2:execlp(t1,t1,t2,(char *)0);
				       break;
				case 3:execlp(t1,t1,t2,t3,(char *)0);
				       break;
		   	}
	 	else
			waitpid(-1,&status,0);
	}
}
