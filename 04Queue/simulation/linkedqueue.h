#ifndef _LINKEDQUEUE_
#define _LINKEDQUEUE_

#include <stdio.h>
#include <stdlib.h>

typedef enum StatusType
{
	arrival,
	start,
	end
} 	Status;

typedef struct s_customer
{
	int	status;
	int	arrivalTime;
	int	serviceTime;
	int	startTime;
	int	endTime;
}	Customer;

typedef struct QueueNodeType
{
	Customer			data;
	struct QueueNodeType* pLink;
} QueueNode;

typedef struct LinkedQueueType
{
	int currentElementCount;
	QueueNode* pFrontNode;
	QueueNode* pRearNode;	
} LinkedQueue;

LinkedQueue* createLinkedQueue();
int enqueueLQ(LinkedQueue* pQueue, QueueNode element);
QueueNode* dequeueLQ(LinkedQueue* pQueue);
QueueNode	*peekLQ(LinkedQueue *pQueue);
void deleteLinkedQueue(LinkedQueue* pQueue);
int isLinkedQueueFull(LinkedQueue* pQueue);
int isLinkedQueueEmpty(LinkedQueue* pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif