#ifndef _HEAP_
#define _HEAP_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct HeapNodeType
{
	int fromVertexId;
	int toVertexId;
	int data;
} HeapNode;

typedef struct HeapType
{
	int maxElementCount;
	int currentElementCount;
	HeapNode *pElement;
} Heap;

Heap* createHeap(int maxElementCount);
void deleteHeap(Heap* pHeap);
int isHeapFull(Heap* pHeap);
void insertMaxHeapNode (Heap* pHeap, HeapNode element);
void insertMinHeapNode (Heap* pHeap, HeapNode element);
HeapNode* deleteMaxHeapNode (Heap* pHeap);
HeapNode* deleteMinHeapNode (Heap* pHeap);
void displayHeap(Heap* pHeap);
void displayHeapByLevel(Heap *pHeap);

HeapNode* deleteMinHeapAH(Heap* pHeap);


#endif

#ifndef _COMMON_HEAP_DEF_
#define _COMMON_HEAP_DEF_

#define TRUE		1
#define FALSE		0

#endif