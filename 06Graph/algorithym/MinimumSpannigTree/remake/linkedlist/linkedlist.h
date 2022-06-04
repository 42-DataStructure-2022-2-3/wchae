#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define C_RED  "\033[31m"
#define C_NRML "\033[0m"

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

typedef struct LinkedGraphType
{
	int maxVertexCount;
	int currentVertexCount;
	int currentEdgeCount;
	int graphType;
	int	*pVertex;
	LinkedList **ppAdjEdge;
} LinkedGraph;

/* LinkedList */
LinkedList* createLinkedList();
int addLLElement(LinkedList* pList, int position, ListNode element);
int removeLLElement(LinkedList* pList, int position);
ListNode* getLLElement(LinkedList* pList, int position);
void clearLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);
void deleteLinkedList(LinkedList* pList);
void displayLinkedList(LinkedList *pList);


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