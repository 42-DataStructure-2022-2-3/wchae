#include "../dijkstra.h"

// from 노드에서 to 노드로 연결이 되었는지 확인한 후, 그 노드의 가중치를 가져오는 로직
int	getEdgeWeight(LinkedGraph *pGraph, int fromVertexId, int toVertexId)
{
	int pReturn = MAX_INT;
	int position = 0;
	LinkedList *pEdgeList = NULL;
	ListNode *pListNode = NULL;

	pEdgeList = pGraph->ppAdjEdge[fromVertexId];
	if (pEdgeList)
	{
		position = findGraphNodePosition(pEdgeList, toVertexId);
		if (0 <= position)
		{
			pListNode = getLLElement(pEdgeList, position);
			if (pListNode)
				pReturn = pListNode->data.weight;
		}
	}
}
int getMinDistance(int *distance, int *pSelected, int maxNodeCount)
{
	int min_dis_vertex = 0;
	int min_distance = MAX_INT;
	int i = 0;

	for (i = 0; i < maxNodeCount; i++)
	{
		if (pSelected[i] && distance[i] < min_distance)
		{
			min_distance = distance[i];
			min_dis_vertex = i;
		}
	}
	return min_dis_vertex;
}
int	*shortestPathDijkstra(LinkedGraph *pGraph, int startVertexId)
{
	int *pReturn;
	int *pSelected;
	int i,j,weight;
	int vertexId, y_w, y_v;
	int maxNodeCount = pGraph->maxVertexCount;

	pReturn = calloc(maxNodeCount, sizeof(int));
	pSelected = calloc(maxNodeCount, sizeof(int));

	//그래프의 모든 노드를 순회
	for(i = 0; i < maxNodeCount; i++)
	{
		if (i == startVertexId)
			pReturn[i] = 0;
		else
		{
			// 그래프에 노드 i 가 있으면 Selected 체크, 
			// 가중치를 가져와 pReturn에 넣음
			if (pGraph->pVertex[i] == USED)
			{
				pSelected[i] = TRUE;
				//pGraph 에 시작노드랑 i 가 연결되어있는지 확인
				// 연결되어있으면 가중치 셋팅
				pReturn[i] = getEdgeWeight(pGraph, startVertexId, i);
			}
			// 만약 i 번째 노드가 pGraph 에 없으면 연결이 안되어있는것임
			// 따라서 가중치를 MAx INT 로 설정, Selected 는 FALSE
			else
			{
				pSelected[i] = FALSE;
				pReturn[i] = MAX_INT;
			}
		}
	}
	//시작노드로부터 거리 리스트 순회
	for (i = 0; i < maxNodeCount; i++)
		printf("(%d, %d) -> %d\n", startVertexId, pReturn[i]);
	for (i = 0; i < pGraph->currentVertexCount - 1; i++)
	{
		printf("[%d]-Iteration\n", i + 1);
			// 시작노드로부터 가중치가 최소인 노드를 찾아 리턴
		vertexId = getMinDistance(pReturn, pSelected, maxNodeCount);
		pSelected[vertexId] = FALSE;
		//시작노드로부터 가중치가 가장 짧은 노드와 연결된 다음 노드들을 가져옴
		LinkedList *pEdgeList;
		ListNode	*pListNode;
		pEdgeList = pGraph->ppAdjEdge[vertexId];
		pListNode = pEdgeList->headerNode.pLink;
		// 두번째노드와 연결된 노드들 탐색
		while (pListNode)
		{
			int toVertexId = pListNode->data.vertexID;
			int weight = pListNode->data.weight;
			//시작노드->가중치가 가장짧은 두번째노드
			//까지의 가중치 (0->1 ---2)
			y_v = pReturn[vertexId];
			//시작노드->가중치가 가장짧은 두번째노드와 연결된 그다음노드
			// 까지의 가중치 (0->2)
			y_w = pReturn[toVertexId];
			if (y_v + weight < y_w)
				pReturn[toVertexId] = y_v + weight;
		}
	}

	
}