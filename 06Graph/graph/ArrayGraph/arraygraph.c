#include "arraygraph.h"

ArrayGraph* createArrayGraph(int maxVertexCount)
{
	ArrayGraph *ag;
	ag = calloc(1, sizeof(ArrayGraph));
	ag->maxVertexCount = maxVertexCount;
	ag->pVertex = calloc(maxVertexCount, sizeof(int));
	ag->ppAdjEdge = calloc(maxVertexCount, sizeof(int *));
	for (int i = 0; i < maxVertexCount; i++)
	{
		ag->ppAdjEdge[i] = calloc(maxVertexCount, sizeof(int));
	}
	ag->graphType = GRAPH_UNDIRECTED;
	return (ag);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
	ArrayGraph *ag;
	ag = createArrayGraph(maxVertexCount);
	ag->graphType = GRAPH_DIRECTED;
	return (ag);
}

int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
	if (!pGraph || vertexID < 0 || pGraph->maxVertexCount < vertexID)
		return (FALSE);
	if (pGraph->pVertex[vertexID])
	{
		printf("이미 사용 중인 노드입니다.\n");
		return (FALSE);
	}
	pGraph->pVertex[vertexID] = USED;
	return (TRUE);
}
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
	if (!pGraph || vertexID < 0 || pGraph->maxVertexCount < vertexID)
		return (FALSE);
	return (pGraph->pVertex[vertexID] == USED);
}

int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
		return (FALSE);
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = USED;
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		pGraph->ppAdjEdge[toVertexID][fromVertexID] = USED;
	return (TRUE);
}

int addEdgeWithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
		return (FALSE);
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
	return (TRUE);
}
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
		return (FALSE);
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = NOT_USED;
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		pGraph->ppAdjEdge[toVertexID][fromVertexID] = NOT_USED;
	return (TRUE);
}


int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
	if (!checkVertexValid(pGraph, vertexID))
		return (FALSE);
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		removeEdgeAG(pGraph, vertexID, i);
		removeEdgeAG(pGraph, i, vertexID);
	}	
	pGraph->pVertex[vertexID] = NOT_USED;
	return (TRUE);
}


void deleteArrayGraph(ArrayGraph* pGraph)
{
	for(int i = 0; i < pGraph->maxVertexCount; i++)
	{
		free(pGraph->ppAdjEdge[i]);
	}
	free(pGraph->ppAdjEdge);
	free(pGraph->pVertex);
}

// ���� �׷��� ���� �Ǵ�
int isEmptyAG(ArrayGraph* pGraph)
{
	return (pGraph->currentVertexCount == 0 ? TRUE : FALSE);
}



void displayArrayGraph(ArrayGraph* pGraph)
{
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		for (int j = 0; j < pGraph->maxVertexCount; j++)
		{
			printf("%d ", pGraph->ppAdjEdge[i][j]);
		}
		printf("\n");
	}
}