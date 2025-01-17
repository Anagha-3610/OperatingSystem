#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<string.h>

struct shared
{
	char chat[100];
	int status;
};
int main()
{
	key_t key=678;
	struct shared *shmptr;
	int shmid=shmget(key,sizeof(struct shared),0666);
	shmptr=shmat(shmid,NULL,0);
	shmptr->status=1;
	while(1)
	{
		while(shmptr->status!=1);
		printf("User1");
		fputs(shmptr->chat,stdout);
		if(strcmp(shmptr->chat,"Stop\n")==0)
		{	exit(1);
		}
		printf("Enter some data:");
		fgets(shmptr->chat,sizeof(shmptr->chat),stdin);
		shmptr->status=0;
		if(strcmp(shmptr->chat,"Stop\n")==0)
                {       exit(1);
                }
	}
	shmdt(shmptr);
	return 0;
}
