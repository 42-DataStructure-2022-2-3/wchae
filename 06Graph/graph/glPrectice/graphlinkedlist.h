#ifndef _GRAPH_LINKEDLIST_
#define _GRAPH_LINKEDLIST_

#include <stdio.h>
#include <stdlib.h>

typedef struct GraphVertexType
{
	int vertexID;
	int weight;	
} GraphVertex;

typedef struct ListNodeType
{
	GraphVertex data;
	struct ListNodeType* pLink;
} ListNode;

typedef struct LinkedListType
{
	int currentElementCount;	
	ListNode headerNode;		
} LinkedList;


LinkedList* createLinkedList();
int addLLElement(LinkedList* pList, int position, ListNode element);
int removeLLElement(LinkedList* pList, int position);
ListNode* getLLElement(LinkedList* pList, int position);
void clearLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);
void deleteLinkedList(LinkedList* pList);
void displayLinkedList(LinkedList* pList);
#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define USED				1
#define NOT_USED			0

#define SUCCESS				1
#define FAIL				0

#define TRUE				1
#define FALSE				0

#define GRAPH_UNDIRECTED	1
#define GRAPH_DIRECTED		2

#endif