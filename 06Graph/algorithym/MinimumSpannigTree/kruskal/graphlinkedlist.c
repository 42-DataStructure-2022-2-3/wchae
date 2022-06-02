#include "linkedgraph.h"
#define C_RED  "\033[31m"
#define C_NRML "\033[0m"

static void	printError(char *str)
{
	printf("%s %s %s \n",C_RED, str, C_NRML);
}

static int	isLinkedGraphVerified(LinkedGraph *pGraph)
{
	if (!pGraph)
	{
		printError("LinkedGraph is undifined");
		return (FALSE);
	}
	return (TRUE);
}

int	checkVertexValid(LinkedGraph *pGraph, int vertexId)
{
	if (!isLinkedGraphVerified(pGraph))
		return (FALSE);
	if (pGraph->maxVertexCount < vertexId || vertexId < 0)
	{
		printf("Check vertexId : %s %d %s is Invalid \n", C_RED, vertexId,C_NRML);
		return (FALSE);
	}
	return (TRUE);
}

LinkedGraph *createGraph(int maxVertexCount)
{
	LinkedGraph *pGraph;
	if (maxVertexCount <= 0)
		printError("Size needs at least 1");
	pGraph = calloc(1, sizeof(LinkedGraph));
	pGraph->pVertex = calloc(maxVertexCount, sizeof(int));
	pGraph->ppAdjEdge = calloc (maxVertexCount, sizeof(LinkedList *));
	for (int i = 0; i < maxVertexCount; i++)
		pGraph->ppAdjEdge[i] = createLinkedList();
	pGraph->graphType = GRAPH_UNDIRECTED;
	pGraph->maxVertexCount = maxVertexCount;
	return (pGraph);
}

LinkedGraph	*createDirectedGraph(int maxVertexCount)
{
	LinkedGraph *pGraph;
	if (maxVertexCount <= 0)
		printError("Size needs at least 1");
	pGraph = createGraph(maxVertexCount);
	pGraph->graphType = GRAPH_DIRECTED;
	return (pGraph);
}

int	addVertexLG(LinkedGraph *pGraph, int vertexId)
{
	if (!isLinkedGraphVerified(pGraph) || !checkVertexVerify(pGraph, vertexId))
		return (FALSE);
	pGraph->pVertex[vertexId] = USED;
	pGraph->currentVertexCount++;
	return (TRUE);
}

int	addEdgeLG(LinkedGraph *pGraph, int fromVertex, int toVertex)
{
	return (addEdgeWithWeightLG(pGraph, fromVertex, toVertex, 0));
}

int	addEdgeWithWeightLG(LinkedGraph *pGraph, int fromVertex, int toVertex, int weight)
{
	if (!isLinkedGraphVerified(pGraph)
		||!checkVertexVerify(pGraph, fromVertex)
		||!checkVertexVerify(pGraph, toVertex)
		|| weight < 0)
		return (FALSE);
	
	GraphVertex data;
	data.vertexID = toVertex;
	data.weight = weight;

	ListNode node;
	node.data = data;

	addLLElement(pGraph->ppAdjEdge[fromVertex], 
				pGraph->ppAdjEdge[fromVertex]->currentElementCount, 
				node);
	
	/* 무방향 그래프일경우, 대칭 추가 */
	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
		data.vertexID = fromVertex;
		node.data = data;
		addLLElement(pGraph->ppAdjEdge[toVertex], pGraph->ppAdjEdge[toVertex]->currentElementCount, node);
	}
	pGraph->currentEdgeCount++;
	return (TRUE);
}

int isEmptyLG(LinkedGraph *pGraph)
{
	return (pGraph->currentVertexCount == 0 ? TRUE : FALSE);
}

int removeEdgeLG(LinkedGraph *pGraph, int fromVertex, int toVertex)
{
	int			delPos;
	ListNode	*element;
	
	if(!isLinkedGraphVerified(pGraph) || 
		isEmpty(pGraph) || 
		!checkVertexVerify(pGraph, fromVertex) || 
		!checkVertexVerify(pGraph, toVertex))
		return (FALSE);

	element = &(pGraph->ppAdjEdge[fromVertex]->headerNode);
	for (delPos = 0; delPos < pGraph->ppAdjEdge[fromVertex]->currentElementCount; delPos++)
	{
		element = element->pLink;
		if (element->data.vertexID == toVertex)
			break;
	}
	removeLLElement(pGraph->ppAdjEdge[fromVertex], delPos);

	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
	element = &(pGraph->ppAdjEdge[toVertex]->headerNode);
		for (delPos = 0; delPos < pGraph->ppAdjEdge[toVertex]->currentElementCount; delPos++)
		{
			element = element->pLink;
			if (element->data.vertexID == fromVertex)
				break;
		}
		removeLLElement(pGraph->ppAdjEdge[toVertex], delPos);
	}
	return (TRUE);
}

int removeVertexLG(LinkedGraph *pGraph, int vertex)
{
	if(!isLinkedGraphVerified(pGraph) || 
		isEmpty(pGraph) || 
		!checkVertexVerify(pGraph, vertex))
		return (FALSE);
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		removeEdgeLG(pGraph, vertex, i);
		removeEdgeLG(pGraph, i, vertex);
	}
	pGraph->pVertex[vertex] = NOT_USED;
	return (TRUE);
}

void deleteLinkedGraph(LinkedGraph *pGraph)
{
	if (!isLinkedGraphVerified(pGraph))
		return (FALSE);
	for (int i = 0; i < pGraph->maxVertexCount; i++)
		deleteLinkedList(pGraph->ppAdjEdge[i]);
	free(pGraph->pVertex);
	free(pGraph->ppAdjEdge);
}

void displayLinkedGraph(LinkedGraph *pGraph)
{
	if(!isLinkedGraphVerified(pGraph))
		return ;
	
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		printf("%d ->", i);
		displayLinkedList(pGraph->ppAdjEdge[i]);
		printf("\n");
	}
}

int	getMaxVertexCountLG(LinkedGraph *pGraph)
{
	return (pGraph->maxVertexCount);
}

int	getVertexCountLG(LinkedGraph *pGraph)
{
	return (pGraph->currentVertexCount);
}
int	getEdgeCountLG(LinkedGraph *pGraph)
{
	return (pGraph->currentEdgeCount);
}