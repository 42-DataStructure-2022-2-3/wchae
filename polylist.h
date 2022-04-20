#ifndef _POLYLIST_
#define _POLYLIST_
#include <stdlib.h>
#include <stdio.h>
typedef struct ListNodeType
{
	int coef;
    int degree;
	struct ListNodeType* pLink;
} ListNode;

typedef struct PolyListType
{
	int currentElementCount;	
	ListNode headerNode;		
} PolyList;

PolyList* createLinkedList();
int addLLElement(PolyList* pList, int position, ListNode element);
int removeLLElement(PolyList* pList, int position);
PolyList* getLLElement(PolyList* pList, int position);
PolyList* sumPolyList(PolyList* aList, PolyList* bList);

void clearLinkedList(PolyList* pList);
int getLinkedListLength(PolyList* pList);
void deleteLinkedList(PolyList* pList);
#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif