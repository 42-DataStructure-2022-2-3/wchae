#include "bfs.h"

void bfs(LinkedGraph *pGraph, int startVertex)
{
	LinkedDeque *pDeque = createLinkedDeque();
	DequeNode element;
	int	*pVisited = calloc(pGraph->maxVertexCount, sizeof(int));

	element.data.vertexID = startVertex;
	insertFrontLD(pDeque, element);
	pVisited[startVertex] = USED;

	while (!isLinkedDequeEmpty(pDeque))
	{
		DequeNode *current;
		current = deleteRearLD(pDeque);
		//여기에서 체크를 해 줄  경우 2번 노드를 방문했을때 2번과 연결된 5번 노드를 enqueue
		// 이후, 4번 노드까지 진행되었을때, 4번도 5번과 연결되어있으므로 5번 노드가 한번 더 enqueue됨
		// 따라서, enqueue하기 전에 방문을 했다고 체크를 해주어야 함

		// pVisited[current->data.vertexID] = USED;
		printf(" %d ", current->data.vertexID);
		if (current)
		{
			ListNode *vertexs = pGraph->ppAdjEdge[current->data.vertexID]->headerNode.pLink;
			while (vertexs)
			{
				if (pVisited[vertexs->data.vertexID] == NOT_USED)
				{
					DequeNode add;
					add.data = vertexs->data;
					pVisited[vertexs->data.vertexID] = USED;
					insertFrontLD(pDeque, add);
				}
				vertexs = vertexs->pLink;
			}
			free(current);
		}
	}
	deleteLinkedDeque(pDeque);
	free(pVisited);
}