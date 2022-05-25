#include "arraygraph.h"

ArrayGraph* createArrayGraph(int maxVertexCount)
{
	if (maxVertexCount <= 0)
		return FALSE;
	ArrayGraph *arrayGraph = calloc(1, sizeof(ArrayGraph));
	arrayGraph->maxVertexCount = maxVertexCount;
	arrayGraph->graphType = GRAPH_UNDIRECTED;
	arrayGraph->pVertex = calloc(maxVertexCount, sizeof(int));
	arrayGraph->ppAdjEdge = calloc(maxVertexCount, sizeof(int *));
	for (int i = 0; i < maxVertexCount; i++)
	{
		arrayGraph->ppAdjEdge[i] = calloc(1, sizeof(int));
		//할당하다가 용량초과시 처리
		if (arrayGraph->ppAdjEdge[i] == NULL)
		{
			for (int j = 0; j < i - 1; j++)
				if (arrayGraph->ppAdjEdge[j]) free(arrayGraph->ppAdjEdge[j]);
			if (arrayGraph->pVertex) free(arrayGraph->pVertex);
			if (arrayGraph) free(arrayGraph);
			return FALSE;
		}
	}
	return (arrayGraph);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
	ArrayGraph	*arrayGraph;
	arrayGraph = createArrayGraph(maxVertexCount);
	arrayGraph->graphType = GRAPH_DIRECTED;
	return (arrayGraph);
}

int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
	if (!pGraph || pGraph->maxVertexCount < vertexID)
		return (FALSE);
	if (pGraph->pVertex[vertexID] == NOT_USED)
	{
		pGraph->pVertex[vertexID] = USED;
		pGraph->currentVertexCount++;
	}
	else
	{
		printf("초과\n");
		return (FALSE);
	}
	return (TRUE);
	
}
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
	if (!pGraph || pGraph->maxVertexCount <= vertexID
	|| pGraph->pVertex[vertexID] == NOT_USED)
	{
		printf("노드 에러 = %d\n", vertexID);
		return (FALSE);
	}
	return (TRUE);
}

int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, fromVertexID))
		return FALSE;
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = USED;	
	pGraph->ppAdjEdge[toVertexID][fromVertexID] = USED;
	return (TRUE);	
}

int addEdgeWithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, fromVertexID))
		return FALSE;
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
	return (TRUE);
}
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
		return (FALSE);
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = 0;
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		pGraph->ppAdjEdge[toVertexID][fromVertexID] = 0;
	return (TRUE);
}


int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
	if (!checkVertexValid(pGraph, vertexID))
		return (FALSE);
	for(int i = 0; i < pGraph->maxVertexCount; i++)
	{
		removeEdgeAG(pGraph, vertexID, i);
		removeEdgeAG(pGraph, i, vertexID);
	}
	pGraph->pVertex[vertexID] = NOT_USED;
	return (TRUE);
}


void deleteArrayGraph(ArrayGraph* pGraph)
{
	if (!pGraph)
		return ;
	for (int i = 0; i < pGraph->maxVertexCount; i++)
		free(pGraph->ppAdjEdge[i]);
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
	if (!pGraph)
		return;
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		for (int j = 0; j < pGraph->maxVertexCount; j++)
			printf("%d ",pGraph->ppAdjEdge[i][j]);
		printf("\n");
	}
}