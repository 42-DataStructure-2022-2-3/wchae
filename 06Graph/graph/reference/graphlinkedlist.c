#include "graphlinkedlist.h"

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
        printf("%d\n", node->data);
        node = node->pLink;
        i++;
    }
}

/**
 *	LinkedGraph
 */

LinkedGraph* createLinkedGraph(int maxVertexCount)
{
    LinkedGraph *lg;

    lg = calloc(1, sizeof(LinkedGraph));
    lg->maxVertexCount = maxVertexCount;
    lg->graphType = GRAPH_UNDIRECTED;
    lg->pVertex = calloc(maxVertexCount, sizeof(int));
    lg->ppAdjEdge = calloc(maxVertexCount, sizeof(LinkedList *));
    for (int i = 0; i < maxVertexCount; i++)
    {
        lg->ppAdjEdge[i] = createLinkedList();
    }
    return (lg);
}

LinkedGraph* createLinkedDirectedGraph(int maxVertexCount)
{
	LinkedGraph *lg;
	lg = createLinkedGraph(maxVertexCount);
	lg->graphType = GRAPH_DIRECTED;
	return (lg);
}

int isEmptyLG(LinkedGraph* pGraph)
{
    return (pGraph->currentElementCount == 0 ? TRUE : FALSE);
}

int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
    if (!pGraph || vertexID < 0 || pGraph->maxVertexCount < vertexID)
        return (FALSE);
    pGraph->pVertex[vertexID] = USED;
    pGraph->currentElementCount++;
    return (TRUE);
}

int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    ListNode node;
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    node.data.vertexID = toVertexID;
    node.data.weight = 0;
    addLLElement(pGraph->ppAdjEdge[fromVertexID], pGraph->ppAdjEdge[fromVertexID]->currentElementCount, node);
    if (pGraph->graphType == GRAPH_UNDIRECTED)
    {
        node.data.vertexID = fromVertexID;
        addLLElement(pGraph->ppAdjEdge[toVertexID], pGraph->ppAdjEdge[toVertexID]->currentElementCount, node);
    }
    return (TRUE);
}

int addElementForVertex(LinkedList *pList, int position, GraphVertex vertex)
{
	ListNode node = {0,};
	node.data = vertex;
	return (addLLElement(pList, position, node));
}

int addEdgeWithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    GraphVertex toNode;
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
	toNode.vertexID = toVertexID;
	toNode.weight = weight;
	addElementForVertex(pGraph->ppAdjEdge[fromVertexID], 0, toNode);
	pGraph->currentElementCount++;

	if (pGraph->graphType == GRAPH_UNDIRECTED)
	{
    	GraphVertex fromNode;
		fromNode.vertexID = fromVertexID;
		fromNode.weight = weight;
		addElementForVertex(pGraph->ppAdjEdge[toVertexID], 0, fromNode);
		pGraph->currentElementCount++;
	}
    return (TRUE);
}

int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
    if (!pGraph || vertexID < 0 || pGraph->maxVertexCount < vertexID)
        return (FALSE);
    return (pGraph->pVertex[vertexID]);
}

int	findGraphNodePosition(LinkedList *pList, int vertexID)
{
	ListNode *pNode;
	int position;
	
	position = 0;
	if (pList)
	{
		pNode = pList->headerNode.pLink;
		while (pNode)
		{
			if (pNode->data.vertexID == vertexID)
				return position;
			pNode = pNode->pLink;
			position++;
		}
	}
	return (-1);
}

void deleteLinkedGraphNode(LinkedList* pList, int delVertexID)
{
	ListNode *pNode;
	int position;

	position = findGraphNodePosition(pList, delVertexID);
	if (0 <= position)
		removeLLElement(pList, position);
}

int removeEdgeLG2(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
	deleteLinkedGraphNode(pGraph->ppAdjEdge[fromVertexID], toVertexID);
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		deleteLinkedGraphNode(pGraph->ppAdjEdge[toVertexID], fromVertexID);
	return (TRUE);
}



int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    int delPos;
    ListNode *element;
    element = &(pGraph->ppAdjEdge[fromVertexID]->headerNode);
    for (delPos = 0; delPos < pGraph->ppAdjEdge[fromVertexID]->currentElementCount; delPos++)
    {
        if (element->data.vertexID == toVertexID)
            break ;
        element = element->pLink;
    }
    removeLLElement(pGraph->ppAdjEdge[fromVertexID], delPos);
}

int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	if (!pGraph || !checkVertexValid(pGraph, vertexID))
		return (FALSE);
	for (int i = 0; i< pGraph->maxVertexCount; i++)
	{
		removeEdgeLG(pGraph, vertexID, i);
		removeEdgeLG(pGraph, i, vertexID);
	}
	pGraph->pVertex[vertexID] = NOT_USED;
	return (TRUE);
}


void deleteLinkedGraph(LinkedGraph* pGraph);
void displayLinkedGraph(LinkedGraph* pGraph);