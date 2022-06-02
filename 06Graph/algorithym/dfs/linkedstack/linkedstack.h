
#ifndef _LINKEDSTACK_
#define _LINKEDSTACK_

#include <stdlib.h>
#include <stdio.h>
#include "../graphlinkedlist.h"

typedef struct StackNodeType
{
	int data;
	struct StackNodeType *pLink;
} StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;	//현재 노드 개수
	StackNode *pTop;			//원소 저장을 위한 배열 포인터
} LinkedStack;

LinkedStack* createLinkedStack();
int isLinkedStackEmpty(LinkedStack* pList);
void deleteLinkedStack(LinkedStack* pList);

int	push(LinkedStack *pList, StackNode element);
StackNode *pop(LinkedStack *pList);
StackNode *peek(LinkedStack *pList);

void displayLinkedStack(LinkedStack* pList);
int getLinkedStackLength(LinkedStack* pList);


#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif