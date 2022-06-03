#include "graphlinkedlist.h"

#define C_RED  "\033[31m"
#define C_NRML "\033[0m"
/**
 * LINKED_LIST FUNC
 * 
 */

LinkedList* createLinkedList()
{
    LinkedList  *list;

    list = (LinkedList *)calloc(1, sizeof(LinkedList));
    if (!list)
        return (NULL);
    return (list);    
}

int addLLElement(LinkedList* pList, int position, ListNode element)
{
    ListNode    *prev;
    ListNode    *new;
    int         i;

    if (!pList || position < 0 || pList->currentElementCount < position)
        return (FALSE);
    new = (ListNode *)calloc(1, sizeof(ListNode));
    if (!new)
        return (FALSE);
    i = 0;
    new->data = element.data;
    prev = &(pList->headerNode);
    while (i < position)
    {
        prev = prev->pLink;
        i++;        
    }
    new->pLink = prev->pLink;
    prev->pLink = new;
    pList->currentElementCount++;
    return (TRUE);
}

int removeLLElement(LinkedList* pList, int position)
{
    int i;
    ListNode *prev;
    ListNode *current;
    if (!pList || pList->currentElementCount <= position)
        return (FALSE);
    i = 0;
    prev = &(pList->headerNode);
    while (i < position)
    {
        prev = prev->pLink;
        i++;
    }
    current = prev->pLink;
    prev->pLink = current->pLink;
    pList->currentElementCount--;
    free(current);
    return (TRUE);
}
ListNode* getLLElement(LinkedList* pList, int position)
{
    int i;
    ListNode *node;
    if (!pList || pList->currentElementCount <= position)
        return (FALSE);
    i = 0;
    node = pList->headerNode.pLink;
    while (i < position)
    {
        node = node->pLink;
        i++;
    }
    return (node);
}

void clearLinkedList(LinkedList* pList)
{
    while (pList->currentElementCount)
        removeLLElement(pList, pList->currentElementCount - 1);
    pList->headerNode.pLink = NULL;
}

int getLinkedListLength(LinkedList* pList)
{
    if (!pList)
        return (FALSE);
    return (pList->currentElementCount);
}

void deleteLinkedList(LinkedList* pList)
{
    ListNode    *tmp;
    clearLinkedList(pList);
    free(pList);
}
void displayLinkedList(LinkedList* pList)
{
    ListNode *node;
    int i;
    if (!pList)
        return ;
    i = 0;
    node = pList->headerNode.pLink;
    while (i < pList->currentElementCount)
    {
        printf("%d ", node->data.vertexID);
        node = node->pLink;
        i++;
    }
}


/**
 * GRAPH_FUNC
 */
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

LinkedGraph *createLinkedGraph(int maxVertexCount)
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
	pGraph = createLinkedGraph(maxVertexCount);
	pGraph->graphType = GRAPH_DIRECTED;
	return (pGraph);
}

int	addVertexLG(LinkedGraph *pGraph, int vertexId)
{
	if (!isLinkedGraphVerified(pGraph) || !checkVertexValid(pGraph, vertexId))
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
		||!checkVertexValid(pGraph, fromVertex)
		||!checkVertexValid(pGraph, toVertex)
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
		isEmptyLG(pGraph) || 
		!checkVertexValid(pGraph, fromVertex) || 
		!checkVertexValid(pGraph, toVertex))
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
		isEmptyLG(pGraph) || 
		!checkVertexValid(pGraph, vertex))
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
		return ;
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

int findGraphNodePosition(LinkedList *edgeList, int toVertexId)
{
	ListNode *node;
	int i;

	i = 0;
	node = edgeList->headerNode.pLink;
	while (node)
	{
		if (node->data.vertexID == toVertexId)
			return (i);
		node = node->pLink;
		i++;
	}
	return (-1);
}
