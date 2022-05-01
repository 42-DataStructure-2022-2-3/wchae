#include "arrayqueue.h"
/*
malloc 한 pElement에서, max 값이 5일때,
pElement[6].data 에 접근해도 segfalut가 나지않음
 */

ArrayQueue* createArrayQueue(int maxElementCount)
{
	ArrayQueue *new;

	new = calloc(1, sizeof(ArrayQueue));
	new->pElement = calloc(1, sizeof(ArrayQueueNode) * maxElementCount);
	if (!new)
		return FALSE;
	new->maxElementCount = maxElementCount;
	return (new);
}

int enqueueCAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
	if (!pQueue || isArrayQueueFull(pQueue))
		return FALSE;
	pQueue->pElement[pQueue->rear] = element;
	pQueue->rear = (pQueue->rear + 1) % pQueue->maxElementCount;
	pQueue->currentElementCount++;
	return (TRUE);
}

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
	if (!pQueue || pQueue->rear == pQueue->maxElementCount)
		return FALSE;
	pQueue->pElement[pQueue->rear] = element;
	pQueue->rear = (pQueue->rear + 1);
	pQueue->currentElementCount++;
	return (TRUE);
}

ArrayQueueNode *dequeueCAQ(ArrayQueue* pQueue)
{
	//deque 로 node 사용 후 free()
	if (!pQueue || isArrayQueueEmpty(pQueue))
		return FALSE;
	ArrayQueueNode *pReturn = calloc(1, sizeof(ArrayQueueNode));
	*pReturn = pQueue->pElement[pQueue->front];
	pQueue->pElement[pQueue->front].data = 0;
	pQueue->currentElementCount--;
	pQueue->front = (pQueue->front + 1) % pQueue->maxElementCount;
	return pReturn;
}

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{
	if (!pQueue || isArrayQueueEmpty(pQueue))
		return FALSE;
	ArrayQueueNode *pReturn = calloc(1, sizeof(ArrayQueueNode));
	*pReturn = pQueue->pElement[pQueue->front];
	pQueue->pElement[pQueue->front].data = 0;
	pQueue->currentElementCount--;
	pQueue->front = (pQueue->front + 1);
	return pReturn;
}

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
	if (!pQueue || isArrayQueueEmpty(pQueue))
		return FALSE;
	return &(pQueue->pElement[pQueue->front]);
}

void deleteArrayQueue(ArrayQueue* pQueue)
{
	if (!pQueue)
		return ;
	free(pQueue->pElement);
	free(pQueue);
	pQueue = NULL;
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
	if (!pQueue)
		return (FALSE);
	return (pQueue->currentElementCount==pQueue->maxElementCount);
}

int isArrayQueueEmpty(ArrayQueue* pQueue)
{
	if (!pQueue)
		return (FALSE);
	return	(pQueue->currentElementCount == 0);
}
void displayArrayQueue(ArrayQueue *pQueue)
{
	if (!pQueue)
		return ;
	for (int i = 0; i < pQueue->maxElementCount; i++)
	{
		printf("[%d] : %d\n", i, pQueue->pElement[i].data);
	}
	// printf("{%d} : %d\n", pQueue->maxElementCount, pQueue->pElement[pQueue->maxElementCount].data);
}

int main (void)
{
	ArrayQueue *pQueue;
	ArrayQueueNode element;
	ArrayQueueNode	*dequed;
	pQueue = createArrayQueue(5);
	for (int i = 0; i <= 5 ; i++)
	{
		element.data = i;
		enqueueCAQ(pQueue, element);
	}
	displayArrayQueue(pQueue);
	for (int i = 0; i < 2; i++)
	{
		dequed= dequeueCAQ(pQueue);
		printf("deque = %d \n", dequed->data);
		free(dequed);
	}
	displayArrayQueue(pQueue);

	for (int i = 0; i < 3 ; i++)
	{
		element.data = i * 5;
		enqueueCAQ(pQueue, element);
		printf("peek = %d \n", peekAQ(pQueue)->data);
	}
	displayArrayQueue(pQueue);

	system("leaks a.out");

}