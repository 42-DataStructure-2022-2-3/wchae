
#ifndef _LINKEDSTACK_
#define _LINKEDSTACK_

#include <stdlib.h>
#include <stdio.h>

typedef struct MapPositionType
{
	int x;				// ���� ��ġ x��ǥ.
	int y;				// ���� ��ġ y��ǥ.
	int direction;		// ���� ��ġ�� �̵� ����.
} MapPosition;

typedef struct StackNodeType
{
	MapPosition data;
	struct StackNodeType *pLink;
} StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;	//현재 노드 개수
	StackNode *pTopElement;			//원소 저장을 위한 배열 포인터
} LinkedStack;

LinkedStack* createLinkedStack();
int isLinkedStackEmpty(LinkedStack* pList);
void deleteLinkedStack(LinkedStack* pList);

int	pushLS(LinkedStack *pList, StackNode element);
StackNode *popLS(LinkedStack *pList);
StackNode *peek(LinkedStack *pList);

void displayLinkedStack(LinkedStack* pList);
int getLinkedStackLength(LinkedStack* pList);
int checkBracketMatching(LinkedStack* pStack, char *expression);



#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif