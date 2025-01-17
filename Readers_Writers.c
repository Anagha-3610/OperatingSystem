#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int readCount=0;
int w=1;
int m=1;
void RWwait(int *s)
{
	while(*s<=0);
	(*s)--;
}
void RWsignal(int *s)
{
	(*s)++;
}
void writer(int n)
{	{	RWwait(&w);
		printf("Writing by writer %d\n",n);
		sleep(2);
		RWsignal(&w);
	}
}

void reader(int n)
{
		RWwait(&m);
		readCount++;
		if(readCount==1)
		{	RWwait(&w);
		}
		RWsignal(&m);

		printf("Reading by reader %d\n",n);
		sleep(1);

		RWwait(&m);
                readCount--;
                if(readCount==0)
                {       RWsignal(&w);
                }
                RWsignal(&m);
		
	
}

int main()
{	int i,pid;
	for(i=1;i<=2;i++)
	{	if((pid=fork())==0)	
		{	writer(i);
			exit(0);
		}
	}
	for(i=1;i<=5;i++)
	{	if((pid=fork())==0)
		{	reader(i);
			exit(0);
		}
	}
	for(i=1;i<=7;i++)
	{	wait(NULL);
	}
	return 0;
}
