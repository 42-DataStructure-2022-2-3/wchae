#include "prim.h"

int	checkEdge(LinkedGraph *pReturn, int fromVertexId, int toVertexId)
{
	LinkedList *edgeList;

	edgeList = pReturn->ppAdjEdge[fromVertexId];
	if (0 < findGraphNodePosition(edgeList, toVertexId))
		return TRUE;
	return FALSE;
}

int	checkCycle(LinkedGraph *pGraph, int fromVertexId, int toVertexId)
{
	LinkedStack *stack;
	StackNode element;
	int	*pVisited;
	if (!pGraph || !checkVertexValid(pGraph,fromVertexId) || !checkVertexValid(pGraph, toVertexId) || isEmptyLG(pGraph))
		return FALSE;
	stack = createLinkedStack();
	pVisited = calloc(pGraph->maxVertexCount, sizeof(int));

	pVisited[fromVertexId] = TRUE;
	element.data = fromVertexId; 
	push(stack, element);
	while (!isLinkedStackEmpty(stack))
	{
		ListNode	*edgeList;
		StackNode *poped = pop(stack);
		if (poped && poped->data == toVertexId)
		{
			printf("From : %d	To: %d 순환 발생 \n",fromVertexId, toVertexId);
			return (TRUE);
		}
		edgeList = pGraph->ppAdjEdge[poped->data]->headerNode.pLink;
		while (edgeList)
		{
			if (pVisited[edgeList->data.vertexID] == NOT_USED){
				element.data = edgeList->data.vertexID;
				pVisited[edgeList->data.vertexID] = USED;
				push(stack, element);
			}
			edgeList = edgeList->pLink;
		}
	}
	free(pVisited);
	deleteLinkedStack(stack);

	return (FALSE);
}


void getMinWeight(LinkedGraph *pGraph, LinkedGraph *pReturn, int fromVertexId, GraphEdge *minWeightEdge)
{
	int isCycle = FALSE;
	int isExist = FALSE;
	LinkedList *pList = pGraph->ppAdjEdge[fromVertexId];
	ListNode *curr = pList->headerNode.pLink;

	while (curr)
	{
		int toVertexId = curr->data.vertexID;
		int weight = curr->data.weight;
		if (curr->data.weight < minWeightEdge->weight)
		{
			isExist = checkEdge(pReturn, fromVertexId, toVertexId);
			// printf("isExist = %d\n",isExist);
			isCycle = checkCycle(pReturn, fromVertexId, toVertexId);
			// printf("isCycle = %d\n",isCycle);

			if (!isCycle && !isExist)
			{
				minWeightEdge->vertexIdFrom = fromVertexId;
				minWeightEdge->vertexIdTo = toVertexId;
				minWeightEdge->weight = weight;
			}
		}
		curr = curr->pLink;
	}
}

LinkedGraph *mstPrim(LinkedGraph *pGraph, int startVertexId)
{
	LinkedGraph *pReturn = NULL;
	int i = 0;
	int nodeCount = 0;
	int mstNodeCount = 0;
	int maxNodeCount = 0;
	int fromVertexId = 0;
	GraphEdge minWeightEdge = {0,};

	if (!pGraph)
		return pReturn;

	nodeCount = pGraph->currentVertexCount;
	maxNodeCount = pGraph->maxVertexCount;
	//신장트리 생성
	pReturn = createLinkedGraph(maxNodeCount);

	//첫번째 노드 추가
	addVertexLG(pReturn, startVertexId);
	//모든 노드를 확인할때까지 loop
	while ((mstNodeCount = getVertexCountLG(pReturn)) < nodeCount)
	{
		minWeightEdge.vertexIdFrom = 0;
		minWeightEdge.vertexIdTo = 0;
		minWeightEdge.weight = INT32_MAX;

		for (i = 0; i < maxNodeCount; i++)
		{
			if(pReturn->pVertex[i] == USED)
			{
				fromVertexId = i;
				getMinWeight(pGraph, pReturn, fromVertexId, &minWeightEdge);
			}
		}
		printf("[%d], 최소 가중치: (%d, %d)-> %d\n", mstNodeCount, minWeightEdge.vertexIdFrom, minWeightEdge.vertexIdTo, minWeightEdge.weight);
		addVertexLG(pReturn, minWeightEdge.vertexIdTo);
		addEdgeWithWeightLG(pReturn, minWeightEdge.vertexIdFrom, minWeightEdge.vertexIdTo, minWeightEdge.weight);
	}
	return pReturn;
}