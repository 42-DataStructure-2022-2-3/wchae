#include "linkedqueue.h"

LinkedQueue* createLinkedQueue()
{
	LinkedQueue *pQueueLinkedQueue;
	pQueueLinkedQueue = calloc(1, sizeof(LinkedQueue));
	if (!pQueueLinkedQueue)
		return (FALSE);
	return pQueueLinkedQueue;
}

int	enqueueLQ(LinkedQueue *pQueue, QueueNode element)
{
	QueueNode	*new;
	if (!pQueue)
		return FALSE;
	new = (QueueNode *)calloc(1, sizeof(QueueNode));
	*new = element;
	new->pLink = NULL;
	if (isLinkedQueueEmpty(pQueue))
	{
		pQueue->pRearNode = new;
		pQueue->pFrontNode = new;
	}
	else
	{
		pQueue->pRearNode->pLink = new;
		pQueue->pRearNode = new;
	}
	pQueue->currentElementCount++;
	return (TRUE);
}

QueueNode *dequeueLQ(LinkedQueue *pQueue)
{
	QueueNode *node;
	if (!pQueue || pQueue->currentElementCount == 0)
		return (NULL);
	node = pQueue->pFrontNode;
	pQueue->pFrontNode = node->pLink;
	node->pLink = NULL;
	pQueue->currentElementCount--;
	if (isLinkedQueueEmpty(pQueue))
		pQueue->pFrontNode = NULL;
	return (node);
}

QueueNode *peekLQ(LinkedQueue *pQueue) 
{
	if (!pQueue || pQueue->currentElementCount == 0)
		return (NULL);
	return (pQueue->pFrontNode);
}

void deleteLinkedQueue(LinkedQueue *pQueue) 
{
	QueueNode	*node;
	if (!pQueue) return;
	while (!isLinkedQueueEmpty(pQueue))
	{
		node = dequeueLQ(pQueue);
		free(node);
	}
	free(pQueue);
}

int isLinkedQueueFull(LinkedQueue* pQueueLinkedQueue)
{
	return FALSE;
}
int isLinkedQueueEmpty(LinkedQueue* pQueueLinkedQueue)
{
	if (!pQueueLinkedQueue)
		return FALSE;
	return (pQueueLinkedQueue->currentElementCount == 0);
}