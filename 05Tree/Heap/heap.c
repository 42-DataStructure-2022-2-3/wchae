#include "heap.h"
#include <math.h>

Heap* createHeap(int maxElementCount)
{
    Heap *pHeap = calloc(sizeof(Heap), 1);
    pHeap->pElement = calloc(sizeof(HeapNode), maxElementCount + 1);
    pHeap->maxElementCount = maxElementCount;
    return (pHeap);
}

int isHeapFull(Heap* pHeap)
{
    return (pHeap->currentElementCount == pHeap->maxElementCount);
}

// TODO realloc시, + 1이 필요한가? 
Heap *reallocHeap(Heap *pHeap)
{
    Heap *newHeap;

    if (!isHeapFull(pHeap))
        return (pHeap);
    newHeap = realloc(pHeap, (pHeap->maxElementCount * 2) + 1);
    newHeap->maxElementCount = newHeap->maxElementCount * 2 + 1;
    return (newHeap);
}

void insertMaxHeapNode (Heap* pHeap, HeapNode element)
{
    int i;
    HeapNode *parentNode;

    if (isHeapFull(pHeap))
        pHeap = reallocHeap(pHeap);
    i = pHeap->currentElementCount + 1;
    pHeap->pElement[i] = element;
    pHeap->currentElementCount++;
    while(i != 1)
    {
        parentNode = &pHeap->pElement[i / 2];
        if ((*parentNode).data < pHeap->pElement[i].data)
        {
            HeapNode tmp = *parentNode;
            *parentNode = pHeap->pElement[i];
            pHeap->pElement[i] = tmp;
            i = i / 2;
        }
        else
            break;
    }
}

void insertMinHeapNode (Heap* pHeap, HeapNode element)
{
    int i;
    HeapNode *parentNode;

    if (isHeapFull(pHeap))
        pHeap = reallocHeap(pHeap);
    i = pHeap->currentElementCount + 1;
    pHeap->pElement[i] = element;
    pHeap->currentElementCount++;
    while(i != 1)
    {
        parentNode = &pHeap->pElement[i / 2];
        if ((*parentNode).data > pHeap->pElement[i].data)
        {
            HeapNode tmp = *parentNode;
            *parentNode = pHeap->pElement[i];
            pHeap->pElement[i] = tmp;
            i = i / 2;
        }
        else
            break;
    }
}

HeapNode* deleteMaxHeapNode (Heap* pHeap)
{
    HeapNode* retMaxNode;
    int i;
    int bigIndex;

    retMaxNode = calloc(1, sizeof(HeapNode));
    *retMaxNode = pHeap->pElement[1];
    i = pHeap->currentElementCount;
    pHeap->currentElementCount--;
    pHeap->pElement[1] = pHeap->pElement[i];
    memset(&pHeap->pElement[i], 0, sizeof(HeapNode));
    i = 1; 
    while (1)
    {
        if (pHeap->pElement[i * 2].data < pHeap->pElement[i * 2 + 1].data)
            bigIndex = i * 2 + 1; //rightChild
        else
            bigIndex = i * 2; // leftChild
        if (pHeap->pElement[bigIndex].data > pHeap->pElement[i].data)
        {
            HeapNode tmp;
            tmp = pHeap->pElement[bigIndex];
            pHeap->pElement[bigIndex] = pHeap->pElement[i];
            pHeap->pElement[i] = tmp;
            i = bigIndex;
        }
        else
            break;
    }
    return (retMaxNode);
}

HeapNode* deleteMinHeapNode (Heap* pHeap)
{
    HeapNode* retMinNode;
    int i;
    int minIndex;

    retMinNode = calloc(1, sizeof(HeapNode));
    *retMinNode = pHeap->pElement[1];
    i = pHeap->currentElementCount;
    pHeap->currentElementCount--;
    pHeap->pElement[1] = pHeap->pElement[i];
    memset(&pHeap->pElement[i], 0, sizeof(HeapNode));
    i = 1; 
    while (1)
    {
		// printf("i = %d\n", i);
		if (pHeap->currentElementCount < i)
			break;
        if (pHeap->pElement[i * 2].data > pHeap->pElement[i * 2 + 1].data)
            minIndex = i * 2 + 1; //rightChild
        else
            minIndex = i * 2; // leftChild
        if (pHeap->pElement[minIndex].data < pHeap->pElement[i].data)
        {
            HeapNode tmp;
            tmp = pHeap->pElement[minIndex];
            pHeap->pElement[minIndex] = pHeap->pElement[i];
            pHeap->pElement[i] = tmp;
            i = minIndex;
        }
        else
            break;
    }
    return (retMinNode);
}
void deleteHeap(Heap* pHeap)
{
    free(pHeap->pElement);
    pHeap->pElement = NULL;
    free(pHeap);
	memset(pHeap, 0, sizeof(Heap));

}

void displayHeap(Heap* pHeap)
{
    // 어떻게 출력해야할까?
    // 1. 같은 레벨 출력
    // 2. 배열 순서대로 출력
	for (int i = 1; i <= pHeap->currentElementCount; i++)
	{
		printf("[%d : %d] ", i, pHeap->pElement[i].data);
	}
	printf("\n");
}
static int calcTopLevel(int max)
{
	int cnt = 1;
	while (0 < max)
	{
		max /= 2;
		cnt++;
	}
	return cnt;
}
/*미완성*/

void displayHeapByLevel(Heap *pHeap)
{
	int i = 1;
	int	topLevel = calcTopLevel(pHeap->maxElementCount);
	// printf("%d \n",(int)pow(2,0));
	printf("topLevel = %d \n",topLevel);
	for (i = 1; i <= topLevel;){
		for (int j = i + 1; j < topLevel; j++)
			printf(" ");
		int k = (int)pow(2, i - 1);
		// printf("i == %d k==%d\n",i ,k);
		for(; 0 < k; k--)
		{
			if(pHeap->pElement[i].data == 0)
				continue;
			printf("%d ", pHeap->pElement[i++].data);
		}
		printf("\n");
	}
	printf("\n");
}
