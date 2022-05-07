#include "linkedqueue.h"

void	printCustomer(int currentTime, Customer customer)
{
	printf("[%d],", currentTime);
	if (customer.status == arrival)
		printf("도착\n");
	else if (customer.status == start)
		printf("시작 \n");
	else
	{
		printf("종료 ");
		printf("arrivalTime : %d, startTime : %d, waitTime : %d, totalTime : %d \n",
		customer.arrivalTime, customer.startTime, 
		customer.startTime - customer.arrivalTime,
		customer.endTime - customer.startTime);
	}	
}


void	add_customer(LinkedQueue *queue, int arrivalTime, int serviceTime)
{
	int i = 0;
	QueueNode node;
	Customer customer;
	if (!queue)
		return ;
	customer.status = arrival;
	customer.arrivalTime = arrivalTime;
	customer.serviceTime = serviceTime;
	customer.startTime = 0;
	customer.endTime= 0;
	node.data = customer;
	enqueueLQ(queue, node);
}

void processArrival(int currentTime, LinkedQueue *arrivalQueue, LinkedQueue *waitQueue)
{
	QueueNode	*node;
	int	isEmpty;
	if (!arrivalQueue || !waitQueue)
		return;
	isEmpty = isLinkedQueueEmpty(arrivalQueue);
	while (!isEmpty)
	{
		node = peekLQ(arrivalQueue);
		if (node->data.arrivalTime == currentTime)
		{
			node = dequeueLQ(arrivalQueue);
			enqueueLQ(waitQueue, *node);
			printCustomer(currentTime, node->data);
			free(node);
		}
		else
			break;
		isEmpty = isLinkedQueueEmpty(arrivalQueue);
	}
}

QueueNode	*processServiceNodeStart(int currentTime, LinkedQueue *waitQueue)
{
	QueueNode *node = NULL;
	if (waitQueue == NULL) return NULL;
	if (isLinkedQueueEmpty(waitQueue) == TRUE) return NULL;
	node = dequeueLQ(waitQueue);
	if (node->data.status == arrival){
		node->data.status = start;
		node->data.startTime = currentTime;
		printCustomer(currentTime, node->data);
	}
	return node;
}

QueueNode	*processServiceNodeEnd(int currentTime, QueueNode *serviceNode, int *serviceUserCount, int *totalWaitTime)
{
	int	endTime = 0;
	int	waitTime = 0;
	QueueNode	*ret = NULL;

	if (!serviceNode || !serviceUserCount || !totalWaitTime)
		return (NULL);
	
	endTime = serviceNode->data.startTime + serviceNode->data.serviceTime;
	if (endTime <= currentTime)
	{
		waitTime = serviceNode->data.startTime - serviceNode->data.arrivalTime;
		(*serviceUserCount)++;
		(*totalWaitTime) += waitTime;
		
		serviceNode->data.status = end;
		serviceNode->data.endTime = currentTime;
		printCustomer(currentTime, serviceNode->data);
		free(serviceNode);
		ret = NULL;
	}
	else
		ret = serviceNode;
	return ret;
}

void printWaitQueueStatus(int currentTime, LinkedQueue *waitQueue) {
    printf("[%d],WaitQueueStatus: %d\n",
           currentTime,
           waitQueue->currentElementCount);
}

void printReport(LinkedQueue *waitQueue,
                 int serviceUserCount,
                 int totalWaitTime) {
    printf("REPORT\n");
    printf("serviceUserCount : %d\n", serviceUserCount);
    if (serviceUserCount > 0) {
        printf("Avg WaitTime : %f\n",
               ((float) totalWaitTime / (float) serviceUserCount));
    }
    printf("WaitQueueStatus : %d\n",
           waitQueue->currentElementCount);
}

int	main(int argc, char **argv)
{
	int	currentTime = 0;
	int	endTime = 10;
	int	userCount = 0;
	int	totalWaitingTime = 0;

	LinkedQueue	*arrivalQueue = createLinkedQueue();
	LinkedQueue	*waitQueue = createLinkedQueue();
	QueueNode	*serviceNode = NULL;

	add_customer(arrivalQueue, 0, 3);
	add_customer(arrivalQueue, 1, 1);
	add_customer(arrivalQueue, 2, 1);
	add_customer(arrivalQueue, 2, 2);
	add_customer(arrivalQueue, 3, 2);
	add_customer(arrivalQueue, 3, 1);
	add_customer(arrivalQueue, 4, 5);
	add_customer(arrivalQueue, 6, 2);
	add_customer(arrivalQueue, 8, 3);

	for (currentTime = 0; currentTime < endTime; currentTime++)
	{
		processArrival(currentTime, arrivalQueue, waitQueue);

		if (serviceNode)
			serviceNode = processServiceNodeEnd(currentTime
	, serviceNode, &userCount, &totalWaitingTime);
		if (!serviceNode)
			serviceNode = processServiceNodeStart(currentTime
	, waitQueue);
	}
	printReport(waitQueue, userCount, totalWaitingTime);
	
	if (serviceNode)
		free(serviceNode);
	deleteLinkedQueue(arrivalQueue);
	deleteLinkedQueue(waitQueue);
}