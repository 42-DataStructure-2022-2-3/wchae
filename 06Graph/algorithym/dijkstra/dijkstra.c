#include "dijkstra.h"

int	*shortestPathDijkstra(LinkedGraph *pGraph, int startVertex)
{
	int	*pReturn;
	int *pSelected;
	int	i;

	if (!pGraph)
	{
		printf("Graph is NULL\n");
		return (NULL);
	}
	pReturn = calloc(pGraph->maxVertexCount, sizeof(int));
	pSelected = calloc(pGraph->maxVertexCount, sizeof(int));

	for (i = 0; i < pGraph->maxVertexCount; i++)
	{
		if (i == startVertex)
			pReturn[i] = 0;
		else
		{
			if (pGraph->pVertex[i] == USED)
			{
				pSelected[i] = TRUE;
				pReturn[i] = getEdgeWeight(pGraph, startVertex, i);
			}
			else
			{
				pSelected[i] = FALSE;
				pReturn[i] = MAX_INT;
			}
		}
	}
	for (i = 0; i < pGraph->maxVertexCount; i++)
		printf("(%d, %d) -> %d \n", startVertex, i, pReturn[i]);
	for (i = 0; i < pGraph->currentVertexCount - 1; i++)
	{
		LinkedList *pEdgeList;
		ListNode	*pListNode;
		printf("[%d] - Iteration\n", i + 1);
		//STEP 1
		int vertexId = getMinDistance(pReturn, pSelected, pGraph->maxVertexCount);
		pSelected[vertexId] = FALSE;

		pEdgeList = pGraph->ppAdjEdge[vertexId];
		pListNode = pEdgeList->headerNode.pLink;
		while (pListNode)
		{
			int toVertexId = pListNode->data.vertexID;
			int weight = pListNode->data.weight;
			int y_v;
			int y_w;
			//Yv + Cvw   VS   yW
			y_v = pReturn[vertexId];
			y_w = pReturn[toVertexId];
			if (y_v + weight < y_w)
				pReturn[toVertexId] = y_v + weight;
			pListNode = pListNode->pLink;
			
		}
		for (int j = 0; j < pGraph->maxVertexCount; j++)
			printf("\t(%d, %d) -> %d\n",startVertex, j, pReturn[j]);
	}
	free(pSelected);
	return pReturn;
}
int	getMinDistance(int *distance, int *isSelected, int maxNodeCount)
{
	int pReturn = 0;
	int min_distance = MAX_INT;
	
	for (int i = 0; i < maxNodeCount; i++)
	{
		if (isSelected[i] && distance[i] < min_distance)
		{
			min_distance = distance[i];
			pReturn = i;
		}
	}
	return (pReturn);
}

static int isExistEdge(ListNode *node, int data)
{
	while (node)
	{
		if (node->data.vertexID == data)
			return (TRUE);
		node = node->pLink;
	}
	return (0);
}

int getEdgeWeight(LinkedGraph *pGraph, int fromVertex, int toVertex)
{
	int pReturn = MAX_INT;
	int position = 0;
	LinkedList *pEdgeList;
	ListNode *pListNode;

	if (pGraph)
	{
		pEdgeList = pGraph->ppAdjEdge[fromVertex];
		if (pEdgeList)
		{
			position = findGraphNodePosition(pEdgeList, toVertex);
			if (0 <= position)
			{
				pListNode = getLLElement(pEdgeList, position);
				if (pListNode)
					pReturn = pListNode->data.weight;
			}
		}
	}
	return pReturn;
}