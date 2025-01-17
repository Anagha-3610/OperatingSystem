#include <stdio.h>
#include <stdlib.h>
int n,f,i,j,k,p,fault=0,flag;
void printframe(int frames[],int f)
{	int i;
	for(i=0;i<f;i++)
	{	printf("|%d|\t",frames[i]);
	}
	printf("\n");
}
int is_at_frames(int p,int frames[],int f)
{	for(int j=0;j<f;j++)
	{	if(p==frames[j])
		{	return j;
		}
	}
	return -1;
}
void fifo(int pages[],int n,int realframes[],int f)
{	int frames[f],k=0,fault=0;
	for(int j=0;j<f;j++)
	{	frames[j]=realframes[j];
	}
	printf("FIFO replacement algo:\n");
	for(int i=0;i<n;i++)
	{	int p=pages[i];
		if(is_at_frames(p,frames,f)==-1)
		{	fault++;
			frames[k]=p;
			k=(k+1)%f;
		}
		printframe(frames,f);
	}
	printf("Page fault in FIFO:%d\n",fault);

}
void lru(int pages[],int n,int realframes[],int f)
{	int min,frames[f],recent[f],k=1,fault=0;
	for(int j=0;j<f;j++)
	{	frames[j]=realframes[j];
		recent[j]=0;
	}
	printf("LRU Replacement Algo: \n");
	for(int i=0;i<n;i++)
	{	int p=pages[i];
		int index=is_at_frames(p,frames,f);
		if(index==-1)
		{	fault++;
			min=0;
			for(int j=1;j<f;j++)
			{	if(recent[j]<recent[min])
				{	min=j;	}
			}
			frames[min]=p;
			recent[min]=k;
		}
		else
		{	recent[index]=k;
		}
		k++;
		printframe(frames,f);
	}
	printf("Page fault in LRU:%d\n",fault);
}
void lfu(int pages[],int n,int realframes[],int f)
{	int frames[f],freq[f],order[f],fault=0;
	for(int j=0;j<f;j++)
	{	frames[j]=realframes[j];
		freq[j]=0;
		order[j]=-1;
	}
	printf("LFU Replacement Algo: \n");
	for(int i=0;i<n;i++)
        {       int p=pages[i];
                int index=is_at_frames(p,frames,f);
                if(index==-1)
                {       fault++;
                        int min=0;
                        for(int j=1;j<f;j++)
                        {	if(freq[j]<freq[min] || (freq[j]==freq[min] && order[j]<order[min]))
				{       min=j;  }
			}
			frames[min]=p;
			freq[min]=1;
			order[min]=i;
		}
		else
		{	freq[index]++;
		}
		printframe(frames,f);
	}
	printf("Page fault in LFU:%d\n",fault);
}

int main()
{	int n,f;
	printf("enter the number of pages: ");
	scanf("%d",&n);
	printf("enter the number of frames: ");
	scanf("%d",&f);
	int pages[n],realframes[f];
	printf("Enter the page sequence\n");
	for(int i=0;i<n;i++)
	{	scanf("%d",&pages[i]);
	}
	for(int j=0;j<f;j++)
	{	realframes[j]=-1;
	}
	fifo(pages,n,realframes,f);
	lru(pages,n,realframes,f);
	lfu(pages,n,realframes,f);
	return 0;
}
