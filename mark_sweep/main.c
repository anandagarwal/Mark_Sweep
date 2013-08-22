#include<stdio.h>
#include"marknsweep.h"

int main()
{
	FILE *fp;
	fp=fopen("inputfile.txt","r");
	char c=fgetc(fp);
	while(c!=' ')
	{
		c=fgetc(fp);
	}
	c=fgetc(fp);
	//printf("%c",c);
	
	int i=0;
	int size=(int)(c)-48;
	c=fgetc(fp);
	c=fgetc(fp);
	//c=fgetc(fp);
	//c=fgetc(fp);
	//printf("%c",c);
	//printf("Enter the size of the heap\n");
	//scanf("%d",&size);
	object_t heap[size];
	int breakcount;
	int count=0;
	int parentid;
	int ch=0;
	int tempoid;
	int tempheapid;
	int flag=0;
	int freelist[size],freesize=0,rootid;
	//printf("Enter a ROOT id first\n");
	//scanf("%d",&rootid);	
	//init(&(heap[count++]),rootid,1);
	breakcount=0;
		//printf("%c",c);
		
	while(c!=EOF && !breakcount && !flag)
	{		
		while(c!='.' && !breakcount)
		{
			if(c=='R')
			{
				ch=1;
				breakcount=1;
			}
			else if(c=='C')
			{
				ch=2;
				breakcount=1;		
			}
			c=fgetc(fp);
		}
		if(c=='.')
		{
			flag=1;
		}
		c=fgetc(fp);
			
			//printf("%d",ch);
			
	
		//printf("Enter the choice 1.Insert ROOT 2.Insert CHILD 3.EDIT 4.DELETE 5.Exit 6.Display\n");
		//scanf("%d",&ch);
		if(flag==0)
		{
			switch(ch)
			{
					
			case 1: if(count<size&&freesize==0)
				{
					//printf("Enter the Root id\n");
					//scanf("%d",&tempoid);
					tempoid=(int)(c)-48;
					init(&(heap[count++]),tempoid,1);
					break;
				}
				else if(freesize!=0)
				{
					printf("Enter the Root id\n");
					scanf("%d",&tempoid);
					rootfromfreelist(freelist,&freesize,heap,tempoid);
					break;
				
				}
				else
				{
					
					printf("Memory is full\n");
					printf("Checking if mark and sweep can help in clearing space\n");
					init_mark(heap,size);
					sweep(heap,freelist,&freesize,size);
					break;
				}
			case 2: 
				//printf("kot %d\n",count);
				if(count<size)
				{
					//printf("Enter the Object id\n");
					//scanf("%d",&tempoid);
					tempoid=(int)(c)-48;
					c=fgetc(fp);
					c=fgetc(fp);
					parentid=(int)(c)-48;
					linking(heap,tempoid,&count,size,parentid);
					//printf("count %d\n",count);
					break;
				}	
			}
		}
	breakcount=0;
	}
	fclose(fp);
	while(ch!=5)
	{
		printf("Enter the choice 1.Insert ROOT 2.Insert CHILD 3.EDIT 4.DELETE 5.Exit 6.Display\n");
		scanf("%d",&ch);

			switch(ch)
			{
					
			case 1: if(count<size&&freesize==0)
				{
					printf("Enter the Root id\n");
					scanf("%d",&tempoid);
					init(&(heap[count++]),tempoid,1);
					break;
				}
				else if(freesize!=0)
				{
					printf("Enter the Root id\n");
					scanf("%d",&tempoid);
					rootfromfreelist(freelist,&freesize,heap,tempoid);
					break;
				
				}
				else
				{
					
					printf("Memory is full\n");
					printf("Checking if mark and sweep can help in clearing space\n");
					init_mark(heap,size);
					sweep(heap,freelist,&freesize,size);
					break;
				}
			case 2: 
				//printf("kot %d\n",count);
				if(count<size)
				{
					printf("Enter the Object id\n");
					scanf("%d",&tempoid);
					printf("Enter parentid\n");
					scanf("%d",&parentid);
					linking(heap,tempoid,&count,size,parentid);
					//printf("count %d\n",count);
					break;
				}
				else if(freesize!=0)
				{
					printf("Enter Object id\n");
					scanf("%d",&tempoid);
					childfromfreelist(freelist,&freesize,heap,tempoid,size);
					break;
					
				}
				else
				{
					//printf("sfd");
					printf("Memory is full\n");
					printf("Checking if mark and sweep can help in clearing space\n");
					init_mark(heap,size);
					sweep(heap,freelist,&freesize,size);
					break;
				}
			case 3: edit(heap,count);
				break;
					
			case 4:
				delete_object(heap,count);
				break;
		
			case 5:
						return 0;
			case 6:
				displayheap(heap,count);
				break;
			
					
					
			}
		}
}
		

