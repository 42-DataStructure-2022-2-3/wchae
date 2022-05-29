#include "gp.h"
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

int	checkVertexVerify(LinkedGraph *pGraph, int vertexId)
{
	if (!isLinkedGraphVerified(pGraph))
		return (FALSE);
	if (pGraph->size < vertexId || vertexId < 0)
	{
		printf("Check vertexId : %s %d %s is Invalid \n", C_RED, vertexId,C_NRML);
		return (FALSE);
	}
	return (TRUE);
}

LinkedGraph *createGraph(int size)
{
	LinkedGraph *pGraph;
	if (size <= 0)
		printError("Size needs at least 1");
	pGraph = calloc(1, sizeof(LinkedGraph));
	pGraph->pVertex = calloc(size, sizeof(int));
	pGraph->ppAdjEdge = calloc (size, sizeof(LinkedList *));
	for (int i = 0; i < size; i++)
		pGraph->ppAdjEdge[i] = createLinkedList();
	pGraph->graphType = GRAPH_UNDIRECTED;
	pGraph->size = size;
	return (pGraph);
}

LinkedGraph	*createDirectedGraph(int size)
{
	LinkedGraph *pGraph;
	if (size <= 0)
		printError("Size needs at least 1");
	pGraph = createGraph(size);
	pGraph->graphType = GRAPH_DIRECTED;
	return (pGraph);
}

int	addVertex(LinkedGraph *pGraph, int vertexId)
{
	if (!isLinkedGraphVerified(pGraph) || !checkVertexVerify(pGraph, vertexId))
		return (FALSE);
	pGraph->pVertex[vertexId] = USED;
	pGraph->currentVertexCount++;
	return (TRUE);
}

int	addEdge(LinkedGraph *pGraph, int fromVertex, int toVertex)
{
	return (addEdgeWithWeight(pGraph, fromVertex, toVertex, 0));
}

int	addEdgeWithWeight(LinkedGraph *pGraph, int fromVertex, int toVertex, int weight)
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

int isEmpty(LinkedGraph *pGraph)
{
	return (pGraph->currentVertexCount == 0 ? TRUE : FALSE);
}

int removeEdge(LinkedGraph *pGraph, int fromVertex, int toVertex)
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

int removeVertex(LinkedGraph *pGraph, int vertex)
{
	if(!isLinkedGraphVerified(pGraph) || 
		isEmpty(pGraph) || 
		!checkVertexVerify(pGraph, vertex))
		return (FALSE);
	for (int i = 0; i < pGraph->size; i++)
	{
		removeEdge(pGraph, vertex, i);
		removeEdge(pGraph, i, vertex);
	}
	pGraph->pVertex[vertex] = NOT_USED;
	return (TRUE);
}

void deleteLinkedGraph(LinkedGraph **pGraph)
{
	if (!isLinkedGraphVerified(*pGraph))
		return (FALSE);
	for (int i = 0; i < (*pGraph)->size; i++)
	{
		deleteLinkedList((*pGraph)->ppAdjEdge[i]);
	}
	free((*pGraph)->pVertex);
	free((*pGraph)->ppAdjEdge);
	pGraph = NULL;
}

void displayLinkedGraph(LinkedGraph *pGraph)
{
	if(!isLinkedGraphVerified(pGraph))
		return ;
	
	for (int i = 0; i < pGraph->size; i++)
	{
		printf("%d ->", i);
		displayLinkedList(pGraph->ppAdjEdge[i]);
		printf("\n");
	}
}