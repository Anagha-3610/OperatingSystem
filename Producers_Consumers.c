#include<stdio.h>
#include<stdlib.h>

int semaphore=1,full=0,empty,limit,x=0;

void producer();
void consumer();
int wait(int);
int signal(int);

void main()
{
  printf("Enter the production limit : ");
  scanf("%d",&limit);
  empty=limit;
  while (1)
  {
    if (x < limit)
       producer();
    if (x > limit)
       break; // Exit the loop if production limit is reached
    if (x > 0)
       consumer();
  }
}
int wait(int s)
{
  while(s<=0)
  {
  }
  return (--s);
}

int signal(int s)
{
   return (++s); 
}
void producer()
{
    semaphore=wait(semaphore);
    if(x<limit)
    {
     full=signal(full);
     empty=wait(empty);
     x++;
     printf("producer produced %d\n",x);
    }
    semaphore=signal(semaphore);

}
void consumer()
{
  semaphore=wait(semaphore);
  if(x>0)
  {
    empty=signal(empty);
    full=wait(full);
    printf("consumer consumed %d\n",x);
  }
  semaphore=signal(semaphore);

}
