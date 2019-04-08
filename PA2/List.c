//#Roy Wang #1636195 hwang167 PA2#
//################################ 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
#include "List.h"
typedef struct NodeObj{
	int value;
	struct NodeObj* pre;
	struct NodeObj* next;
}NodeObj;

typedef struct NodeObj* Node;

Node newNode(int v)
{
	Node N=malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->value=v;
	N->pre=NULL;
	N->next=NULL;
	return N;
}

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
typedef struct ListObj{
   Node head;
   int num;
} ListObj;

typedef struct ListObj* List;

List newList(void){
	List L=malloc(sizeof(ListObj));
	assert(L!=NULL);
	L->num=0;
	L->head=NULL;
	//memset(L->head,NULL,sizeof(L->head));
	return L;
}

void makeEmpty(List L){
	
	while(L!=NULL && L->head!=NULL)
	{
		Node temp=L->head;
		L->head=L->head->next;
		freeNode(&temp);
		
	}
	L->num=0;
}

void freeList(List* pL){
	if( pL!=NULL && *pL!=NULL ){
		makeEmpty(*pL);
      	free(*pL);
      	*pL = NULL;
   }
}
int length(List L)
{
	return L->num;
}
int frontValue(List L)
{
	if(L->num>=1)
	{
		return L->head->value;
	}
	return 0;
}
int backValue(List L)
{
	if(L->num>=1)
	{
		Node t=L->head;
		while(t->next!=NULL)
		{
			t=t->next;
		}
		return t->value;
	}
	return 0;
}
int getValue(Node N)
{
	if(N!=NULL)
	{
		return N->value;
	}
	return 0;
	
}
int equals(List A, List B)
{
	Node a=A->head;
	Node b=B->head;
	while(a!=NULL)
	{
		if(b==NULL)
		{
			return 0;
		}
		else
		{
			if(a->value!=b->value)
			{
				return 0;
			}
			a=a->next;
			b=b->next;
		}
	}
	if(b==NULL)
	{
		return 1;
	}
	return 0;
}
void clear(List L)
{
	freeList(&L);
	L->num=0;
	L->head=NULL; 
}

Node getFront(List L)
{
	if(L->num>=1)
	{
		return L->head;
	}
	return NULL;
}

Node getBack(List L)
{
	if(L->num>=1)
	{
		Node t=L->head;
		while(t->next!=NULL)
		{	
			t=t->next;
		}
		return t;
	}
	return NULL;
}

Node getPrevNode(Node N)
{
	////
	return N->pre;
}

Node getNextNode(Node N)
{
	////
	return N->next;
}


void prepend(List L, int data)
{
	Node temp=newNode(data);
	if(L->num==0)
	{
		L->head=temp;
	}
	else
	{
		temp->next=L->head;
		L->head->pre=temp;
		L->head=temp; 
	} 
	L->num++; 
	
} 

void append(List L, int data)
{
	Node temp=newNode(data);
	Node t=L->head;
	if(L->num==0)
	{
		L->head=temp;
	} 
	else
	{
		while(t->next!=NULL)
		{
			t=t->next;
		}
		t->next=temp;
		temp->pre=t;
	}
	
	L->num++; 
	
}

void insertBefore(List L, Node N, int data)
{
	Node t=newNode(data);
	if(N!=NULL)
	{
		if(N==L->head)
		{
			L->head=t;
			t->next=N;
			N->pre=t; 
			L->num++; 
		} 
		else
		{
			t->next=N;
			N->pre->next=t;
			t->pre=N->pre;
			N->pre=t;
			L->num++; 
		}
		
	}
	
}

void insertAfter(List L, Node N, int data)
{
	Node t=newNode(data);
	if(N!=NULL)
	{
		if(N->next==NULL)
		{
			N->next=t;
			t->pre=N;
			L->num++;
		} 
		else
		{
		
			t->pre=N;
			N->next->pre=t;
			t->next=N->next;
			N->next=t;
			L->num++; 
		}
	}

} 

void deleteFront(List L)
{
	if(L->num>0)
	{
		Node t=L->head;
		L->head=L->head->next;
		L->head->pre=NULL;
		L->num--; 
		freeNode(&t);
	} 
}
void deleteBack(List L)
{
	if(L->num>0)
	{
	Node t=L->head;
	while(t->next!=NULL)
	{
		t=t->next;
	}
	t->pre->next=NULL;
	freeNode(&t);
	L->num--;
}
}

void printList(FILE* out, List L)
{
	Node t=L->head;
		while(t!=NULL)
		{
			fprintf(out,"%d ",t->value);
			t=t->next;
		}
}
void deleten(List L, Node N)
{
	if(N->pre==NULL)
	{
		deleteFront(L);
	}
	else if(N->next==NULL)
	{
		deleteBack(L);
	}
	else
	{
		N->pre->next=N->next;
		N->next->pre=N->pre;
		freeNode(&N);
	
	}
	
}


Node getnumNode(List L, int n)
{
	
	Node temp=L->head;
	for(int i=1;i<n;i++)
	{
		temp=temp->next;
	}
	
	return temp;
}


#endif
