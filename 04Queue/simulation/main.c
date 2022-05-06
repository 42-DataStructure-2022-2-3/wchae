#include "linkeddeque.h"

void	add_customer(LinkedDeque *queue, int arrivalTime, int serviceTime)
{
	int i = 0;
	DequeNode node;
	if (!queue)
		return ;
	node.data->status = arrival;
	node.data->arrivalTime = arrivalTime;
	node.data->serviceTime = serviceTime;
	node.data->startTime = 0;
	node.data->endTime= 0;
	insertFrontLD(queue, node);
}

void processArrival(int currentTime, LinkedDeque *arrivalQueue, LinkedDeque *waitQueue)
{
	DequeNode	*arrivalNode = NULL;
	int	isEmpty = FALSE;
	
	isEmpty = isLinkedDequeEmpty(arrivalQueue);
	while (isEmpty == FALSE)
	{
		arrivalNode = peekRearLD(arrivalQueue);
		if (arrivalNode->data->arrivalTime == currentTime)
		{
			insertFrontLD(waitQueue, *arrivalNode);
			free(deleteRearLD(arrivalQueue));
		}
		else
			break;
		isEmpty = isLinkedDequeEmpty(arrivalQueue);
	}
}
DequeNode	*processServiceNodeEnd(int currentTime, DequeNode *serviceNode, int *serviceUserCount, int *totalWaitTime)
{
	int	endTime;
	int	waitTime;
	DequeNode	*ret;

	if (!serviceNode || !serviceUserCount || !totalWaitTime)
		return (NULL);
	
	endTime = serviceNode->data->startTime + serviceNode->data->serviceTime;
		if (endTime <= currentTime)
		[
			waitTime = serviceNode->data.startTime - serviceNode->data.arrivalTime;
		]
}

int	main(int argc, char **argv)
{
	int	systemTime;
	int	endTime;
	int	userCount;
	int	totalWaitingTime;

	LinkedDeque	*arrivalQueue = createLinkedDeque();
	LinkedDeque	*waitQueue = createLinkedDeque();
	
	// 예외 처리



}