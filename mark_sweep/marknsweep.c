#include<stdio.h>
#include"marknsweep.h"
void init(object_t *obj,int key,int r)
{
	//printf(" --oid--  %d\n",key);
   obj->ccount=0;
   obj->pcount=0;
   int i;
   obj->oid=key;
   for( i=0;i<10;++i)
   {
	obj->parent[i]=-1;
	obj->child[i]=-1;
   }
   obj->flag=0;
   obj->root=r;
}

void displayobject(object_t obj)
{
	int i;
    	printf("OBJECT ID %d\n",obj.oid);
	printf("PARENT ARRAY ");
     	for(i=0;i<10;++i)
	{
		if(obj.parent[i]!=-1)
		{
			printf("%d ",obj.parent[i]);
		}
	}
	printf("\nFLAG %d\n",obj.flag);
	printf("CHILD ARRAY ");
	for(i=0;i<10;++i)
	{
		if(obj.child[i]!=-1)
		{
			printf("%d ",obj.child[i]);
		}
	}
	printf("\n\n");
}

void linking(object_t heap[],int tempoid,int* count,int size,int parentid)
{
	//int parentid;
	//printf("linking %d %d\n",tempoid,parentid);
	int tempheapid=*count;
	int i=0;
	init(&(heap[*count]),tempoid,0);
	//displayobject(heap[tempheapid]);
	*count = *count + 1;
	//printf("Enter the parent\n");
	//scanf("%d",&parentid);
	for(i=0;i<tempheapid;++i)
	{
		if(heap[i].oid==parentid)
		{
			break;
		}
	}
	if(i<tempheapid)
	{
		heap[tempheapid].parent[heap[tempheapid].pcount++]=parentid;
		heap[i].child[heap[i].ccount++]=tempoid;
	//	printf("pcount %d\n",heap[tempheapid].pcount);
		
	}
	else
	{
		printf("Error..Particular parent OID doesnt exist\n");
	}
	//displayobject(heap[tempheapid]);

}
void displayheap(object_t heap[],int size)
{
	int i=0;
	for(i=0;i<size;++i)
	{
		displayobject(heap[i]);
	}
}

void init_mark(object_t heap[],int size)
{
	int i=0;
	while(i<size)
	{
		if(heap[i].root==1)
		{
			mark(&heap[i],heap,size);
		}
		++i;
	}	
}
void mark(object_t* obj,object_t heap[],int size)
{
	printf("Node marked %d\n",obj->oid);
	obj->flag=1;
	int temp=0;
	int i=0;
	while(temp<(obj->ccount))
	{
		int intermediate=obj->child[temp];
		printf("child selected %d\n",intermediate);
		for(i=0;i<size;++i)
		{
			if(heap[i].oid==intermediate)
			{
				break;
			}
		}
		mark(&heap[i],heap,size);
		++temp;
	}
}
void delete_object(object_t heap[],int count)
{

	int tempid,i,j,k,temp;
	//int var1,var2;
	printf("enter the id of the object you want to delete\n");
	scanf("%d",&tempid);
	for(i=0;i<count;++i)
	{
	    //printf("hi\n");
		if(heap[i].oid==tempid)
		{
	//	    printf("if %d\n",heap[i].oid);
			break;
		}
	}
    if(heap[i].root==1)
    {
        heap[i].root=0;
    }
    else
    {
        temp=heap[i].pcount;
        temp=temp-1;
        //printf("pcount: %d \n",temp);
        //printf("%d\n",heap[i].parent[temp]);
        while(temp>=0)
        {
            //printf("enterd while\n");
            for(j=0;j<count;++j)
            {
          //      printf("j\n");
                //if((heap[i].parent[temp])==(heap[j].oid))
               // var1=heap[i].parent[temp];
               // var2=heap[j].oid;
               // printf("%d\n",var1);
               // printf("%d\n",var2);
                if(heap[j].oid==heap[i].parent[temp])
                {
                   // printf("parent: %d\n",var1);
                    delete_child(tempid,&heap[j],count);
                }
            }
            temp=temp-1;
        }
    }
}
void delete_child(int tempid,object_t * obj,int count)
{
	int i,j;
	//printf("%d\n",obj->oid);
        for(i=0;i<10;++i)
        {
        	if(obj->child[i]==-1)
        	{
          //  		printf("break\n");
            		break;
       		}
        	else if(obj->child[i]==tempid)
        	{
           //		printf("object :%d\n",obj->child[i]);
            		obj->child[i]=-1;
            //		printf("child array\n");
            		obj->ccount=obj->ccount-1;
			modify_array(obj);
        //    		printf("ccount: %d\n",obj->ccount);
            		//break;
        	}
        	else
        	{
            		continue;
        	}
    	}
}
void modify_array(object_t *obj)
{
        int i,j=0;
        int array[10];
	for(i=0;i<10;++i)
	{
		array[i]=-1;
	}
        for(i=0;i<10;++i)
        {
                if(obj->child[i]!=-1)
                {
                        array[j]=obj->child[i];
                        ++j;
                }
        }
	for(i=0;i<10;++i)
	{
		obj->child[i]=array[i];
	}
}

void edit(object_t heap[],int count)
{
	int tempid,ch,i,pid,cid,flag = 0;
	printf("enter the object id you want to edit\n");
	scanf("%d",&tempid);	
	printf("enter 1: edit its parent 2:edit its child\n");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1: for(i=0;i<count;++i)
			{
				if(heap[i].oid==tempid)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				if(heap[i].root==1)
				{
					printf("the particular object is itself a parent object and cannot be edited\n");
				}
				else
				{
					printf("enter another existing parent objectid\n");
					scanf("%d",&pid);
					//heap[i].parent[heap[i].child[heap[i].pcount]]=pid;
					
					heap[i].parent[heap[i].pcount++]=pid;
					//++heap[i].pcount;
					edit_parent(heap,tempid,pid,count);
				}
				
				
			}
			else
			{
				printf("the parent object is not present\n");
			}
			break;

		case 2:
			for(i=0;i<count;++i)
			{
				if(heap[i].oid==tempid)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				printf("\nenter another existing child objectid\n");
				scanf("%d",&cid);
				//heap[i].parent[heap[i].child[heap[i].pcount]]=pid;
				heap[i].child[heap[i].ccount++]=cid;
				//++heap[i].pcount;
				edit_child(heap,tempid,cid,count);
			}
			else
			{
				printf("\nthe child object is not present\n");
			}
			break;
			
	}

}
void edit_parent(object_t heap[],int tempid,int pid,int count)
{
	int i;
	for(i=0;i<count;++i)
	{
		if(heap[i].oid==pid)
		{
			break;	
		}
	}
	heap[i].child[heap[i].ccount++]=tempid;	
	
}
void edit_child(object_t heap[],int tempid,int cid,int count)
{
	int i;
	for(i=0;i<count;++i)
	{
		if(heap[i].oid==cid)
		{
			break;
		}
	}
	heap[i].parent[heap[i].pcount++]=tempid;
}
void sweep(object_t heap[],int freelist[],int* freesize,int size)
{
	int i=0;
	for(i=0;i<size;++i)
	{
		if(heap[i].flag==0)
		{
			printf("The garbage is %d\n",heap[i].oid);
			freelist[(*freesize)++]=i;
		}
		else
		{
			
			heap[i].flag=0;
		}
	}
}
void rootfromfreelist(int freelist[],int *freesize,object_t heap[],int tempoid)
{
	int index=freelist[0];
	printf("The object deleted is %d\n",heap[index].oid);
	shiftarray(freelist,freesize);
	init(&(heap[index]),tempoid,1);
}
	

void shiftarray(int freelist[],int*freesize)
{
	int i=0;
	for(i=0;i<(*freesize);++i)
	{
		freelist[i]=freelist[i+1];
	}
	--(*freesize);
}

void childfromfreelist(int freelist[],int*freesize,object_t heap[],int tempoid,int size)
{
	int index=freelist[0];
	printf("The object deleted is %d\n",heap[index].oid);
	shiftarray(freelist,freesize);
	
	int parentid;
	int i=0;
	init(&(heap[index]),tempoid,0);
	printf("Enter the parent\n");
	scanf("%d",&parentid);
	for(i=0;i<size;++i)
	{
		if(heap[i].oid==parentid)
		{
			break;
		}
	}
	if(i<size)
	{
		heap[index].parent[heap[index].pcount++]=parentid;
		heap[i].child[heap[i].ccount++]=tempoid;
		
	}
	else
	{
		printf("Error..Particular parent OID doesnt exist\n");
	}
}

