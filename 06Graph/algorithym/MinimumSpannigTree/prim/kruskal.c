#include "kruscal.h"

Heap *orderEdges(LinkedGraph *pGraph)
{
	int i = 0;
	Heap *pHeap = createHeap(pGraph->currentVertexCount);
	while (i < pGraph->maxVertexCount)
	{
		//노드가 존재하고
		if (checkVertexValid(pGraph, i))
		{
			ListNode *vertexs = pGraph->ppAdjEdge[i]->headerNode.pLink;
			//노드가 i 보다 작은것들만 힙에 추가 (양방향그래프시 중복입력 방지)
			while (vertexs)
			{
				if (i < vertexs->data.vertexID)
				{
					HeapNode addNode;
					addNode.data = vertexs->data.weight;
					addNode.toVertexId = vertexs->data.vertexID;
					addNode.fromVertexId = i;
					insertMinHeapNode(pHeap, addNode);
				}
				vertexs = vertexs->pLink;
			}
		}
		i++;
	}
	return pHeap;
}

int	checkCycle_kru(LinkedGraph *pGraph, int fromVertexId, int toVertexId)
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

LinkedGraph *kruskal(LinkedGraph *pGraph)
{
	LinkedGraph	*pReturn = NULL;
	int i = 0;
	int maxNodeCount = 0;
	int currentNodeCount = 0;
	int edgeCount = 0;
	int isCycle = FALSE;
	Heap *pHeap = NULL;

	if (!pGraph)
		return (FALSE);

	maxNodeCount = getMaxVertexCountLG(pGraph);
	currentNodeCount = getVertexCountLG(pGraph);
	edgeCount = getEdgeCountLG(pGraph);
	pReturn = createLinkedGraph(maxNodeCount);
	if (!pReturn)
		return (NULL);

	pHeap = orderEdges(pGraph);
	displayHeap(pHeap);
	printf("\nHEAP====================\n");
	if (!pHeap)
		return (NULL);
	for (int i = 0; i < edgeCount; i++)
	{
		//최소 비용의 간선(from,to,weight) 추출
		HeapNode *pHeapNode;
		pHeapNode = deleteMinHeapNode(pHeap);
		//순환 발생 점검
		isCycle = checkCycle_kru(pReturn, pHeapNode->fromVertexId, pHeapNode->toVertexId);
		if (!isCycle)
		{
			//노드에 추가가 안되어있으면 추가
			if (pReturn->pVertex[pHeapNode->fromVertexId] == NOT_USED)
				addVertexLG(pReturn, pHeapNode->fromVertexId);
			if (pReturn->pVertex[pHeapNode->toVertexId] == NOT_USED)
				addVertexLG(pReturn, pHeapNode->toVertexId);
			addEdgeWithWeightLG(pReturn, pHeapNode->fromVertexId, pHeapNode->toVertexId, pHeapNode->data);
			printf ("[%d], 최소 가중치 : (%d,%d)->%d\n", i, pHeapNode->fromVertexId, pHeapNode->toVertexId, pHeapNode->data);
		}
		free(pHeapNode);
		if (getVertexCountLG(pReturn) == currentNodeCount)
			break;
	}
	return (pReturn);
}
