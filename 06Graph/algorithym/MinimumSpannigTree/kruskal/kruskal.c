#include "kruscal.h"

Heap *orderEdges(LinkedGraph *pGraph);
int	checkCycle(LinkedGraph *pGraph, int fromVertexId, int toVertexId);
LinkedGraph *kruskal(LinkedGraph *pGraph)
{
	LinkedGraph	*pReturn = NULL;
	int i = 0;
	int maxNodeCount = 0;
	int currentNodeCount = 0;
	int edgeCount = 0;
	int isCycle = FALSE;
	Heap *pHeap = NULL;
	HeapNode *pHeapNode = NULL;

	if (!pGraph)
		return (FALSE);

	maxNodeCount = getMaxVertexCountLG(pGraph);
	currentNodeCount = getVertexCountLG(pGraph);
	edgeCount = getEdgeCountLG(pGraph);
	pReturn = createLinkedGraph(maxNodeCount);
	if (!pReturn)
		return (NULL);
	pHeap = orderEdges(pGraph);
	if (!pHeap)
		return (NULL);
	for (int i = 0; i < edgeCount; i++)
	{
		//
		pHeapNode = deleteMinHeapNode(pHeap);
		//순환 발생 점검
		isCycle = checkCycle(pReturn, pHeapNode->fromVertexId, pHeapNode->toVertexId);
		if (!isCycle)
		{
			//노드에 추가가 안되어있으면 추가
			if (pReturn->pVertex[pHeapNode->fromVertexId] == NOT_USED)
				addVertexLG(pReturn, pHeapNode->fromVertexId);
			if (pReturn->pVertex[pHeapNode->toVertexId] == NOT_USED)
				addVertexLG(pReturn, pHeapNode->toVertexId);
		}
		addEdgeWithWeightLG(pReturn, pHeapNode->fromVertexId, pHeapNode->toVertexId, pHeapNode->weight);

		printf ("[%d], 최소 가중치 : (%d,%d)->%d\n", i, pHeapNode->fromVertexId, pHeapNode->toVertexId, pHeapNode->weight);
		free(pHeapNode);
		if (getVertexCountLG(pReturn) == currentNodeCount)
			break;
	}
	return (pReturn);
}
