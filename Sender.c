#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>

struct shared
{
	char chat[100];
	int status;
};
int main()
{
	key_t key=678;
	struct shared *shmptr;
	int shmid=shmget(key,sizeof(struct shared),IPC_CREAT|0666);
	shmptr=shmat(shmid,NULL,0);
	shmptr->status=0;
	while(1)
	{
		while(shmptr->status!=0);
		printf("User 2:");
		fputs(shmptr->chat,stdout);
		if(strcmp(shmptr->chat,"Stop\n")==0)
		{	exit(1);
		}
		printf("Enter some data\n");
		fgets(shmptr->chat,sizeof(shmptr->chat),stdin);
		shmptr->status=1;
		if(strcmp(shmptr->chat,"Stop\n")==0)
                {       exit(1);
		}
	}
	shmdt(shmptr);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
