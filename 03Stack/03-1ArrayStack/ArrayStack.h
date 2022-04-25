
#ifndef _ARRAYSTACK_
#define _ARRAYSTACK_

#include <stdlib.h>
#include <stdio.h>

typedef struct StackNodeType
{
	int data;
} StackNode;
typedef struct ArrayStackType
{
	int maxElementCount;	 	//최대 노드 개수	
	int currentElementCount;	//현재 노드 개수
	StackNode *pElement;			//원소 저장을 위한 배열 포인터
} ArrayStack;

ArrayStack* createArrayStack(int maxElementCount);
int isArrayStackFull(ArrayStack* pList);
int	isArrayStackEmpty(ArrayStack *pList);

int	push(ArrayStack *pList, StackNode element);
StackNode *pop(ArrayStack *pList);
StackNode *peek(ArrayStack *pList);

void deleteArrayStack(ArrayStack* pList);
int	isArrayStackEmpty(ArrayStack *pList);
void displayArrayStack(ArrayStack* pList);
int getArrayStackLength(ArrayStack* pList);


#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif