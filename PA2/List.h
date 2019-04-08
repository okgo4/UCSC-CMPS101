//Roy Wang #1636195 hwang167 PA2#
//################################
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
typedef struct ListObj* List;
typedef struct NodeObj* Node;
List newList(void);  
void freeList(List* pL); 
int length(List L);  
int frontValue(List L); 
int backValue(List L); 
int getValue(Node N);
int equals(List A, List B); 
void clear(List L);  
Node getFront(List L); 
Node getBack(List L); 
Node getPrevNode(Node N);
Node getNextNode(Node N);
void prepend(List L, int data); 
void append(List L, int data); 
void insertBefore(List L, Node N, int data);
void insertAfter(List L, Node N, int data);
void deleteFront(List L);  
void deleteBack(List L); 
void printList(FILE* out, List L);
Node getnumNode(List L, int n);
void deleten(List L, Node N);
#endif
