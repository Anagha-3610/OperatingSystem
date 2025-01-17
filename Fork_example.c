#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int pid=fork();
	int childpid,exitStatus;
	if(pid<0)
	{
		printf("Error\n");
	}
        else if(pid==0)
        {
                
                printf("Parent id : %d\n",getppid());
                printf("Child id : %d\n",getpid());
		printf("Child process terminated\n");
		exit(0);
	}
	else
	{
		printf("Start of Parent process\n");
		childpid=wait(&exitStatus);
		printf("Parent process terminated\n");
		printf("Wait :%d\n",childpid);
		printf("Exit status :%d\n",WEXITSTATUS(exitStatus));
	}
	return 0;

}
