#include "bfs.h"

void bfs(LinkedGraph *pGraph, int startVertex)
{
	LinkedDeque *pDeque = createLinkedDeque();
	DequeNode element;
	int	*pVisited = calloc(pGraph->currentVertexCount, sizeof(int));

	element.data.vertexID = startVertex;
	insertFrontLD(pDeque, element);

	while (!isLinkedDequeEmpty(pDeque))
	{
		DequeNode *current;
		current = deleteRearLD(pDeque);
		printf(" %d ", current->data.vertexID);
		ListNode *vertexs = pGraph->ppAdjEdge[current->data.vertexID]->headerNode.pLink;
		while (vertexs)
		{
			if (!pVisited[vertexs->data.vertexID])
			{
				DequeNode add;
				add.data = vertexs->data;
				insertFrontLD(pDeque, add);
			}
			vertexs = vertexs->pLink;
		}
		free(current);
	}

	deleteLinkedDeque(pDeque);
	free(pVisited);
}