
#ifndef _STACK_
#define _STACK_

#include <stdlib.h>
#include <stdio.h>
typedef struct StackNodeType
{
	int data;
} StackNode;

typedef struct StackType
{
	int maxElementCount;		
	int currentElementCount;	
	Stack *pElement;	
} Stack;

ArrayList* createArrayList(int maxElementCount);
void deleteArrayList(ArrayList* pList);
int isArrayListFull(ArrayList* pList);
int addALElement(ArrayList* pList, int position, ArrayListNode element);
int removeALElement(ArrayList* pList, int position);
ArrayListNode* getALElement(ArrayList* pList, int position);
void displayArrayList(ArrayList* pList);
void clearArrayList(ArrayList* pList);
int getArrayListLength(ArrayList* pList);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif