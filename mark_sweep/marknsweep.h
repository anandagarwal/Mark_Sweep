#ifndef MARKSWEEP_H
#define MARKSWEEP_H

struct object
{
	int pcount;
	int parent[10];
	int oid;
	int flag;
	int root;
	int child[10];
        int ccount;
};
typedef struct object object_t;

void init(object_t *obj,int key,int r);
void displayobject(object_t obj);
void linking(object_t heap[],int tempoid,int*count,int size,int parentid);
void displayheap(object_t heap[],int count);
void delete_object(object_t heap[],int count);
void delete_child(int tempid,object_t * obj,int count);
void init_mark(object_t heap[],int size);
void mark(object_t * obj,object_t heap[],int size);
void edit(object_t heap[],int count);
void edit_parent(object_t heap[],int tempid,int pid,int count);
void edit_child(object_t heap[],int tempid,int cid,int count);
void sweep(object_t heap[],int freelist[],int*freesize,int size);
void rootfromfreelist(int freelist[],int *freesize,object_t heap[],int tempoid);
void shiftarray(int freelist[],int*freesize);
void modify_array(object_t *obj);
void childfromfreelist(int freelist[],int *freesize,object_t heap[],int tempoid,int size);
#endif
