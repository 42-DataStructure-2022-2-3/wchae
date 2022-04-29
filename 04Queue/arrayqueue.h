#ifndef _ARRAY_QUEUE_
#define _ARRAY_QUEUE_

#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayQueueNodeType
{
	char data;
} ArrayQueueNode;

typedef struct ArrayQueueType
{
	int maxElementCount;		// �ִ� ���� ����
	int currentElementCount;	// ���� ������ ����
	int front;					// front ��ġ
	int rear;					// rear ��ġ
	ArrayQueueNode *pElement;	// ��� ������ ���� 1���� �迭 ������
} ArrayQueue;

ArrayQueue* createArrayQueue(int maxElementCount);
int enqueueCAQ(ArrayQueue* pQueue, ArrayQueueNode element);
int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element);
ArrayQueueNode *dequeueCAQ(ArrayQueue* pQueue);
ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue);
ArrayQueueNode *peekAQ(ArrayQueue* pQueue);
void deleteArrayQueue(ArrayQueue* pQueue);
int isArrayQueueFull(ArrayQueue* pQueue);
int isArrayQueueEmpty(ArrayQueue* pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif