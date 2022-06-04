#include "find_minimum_weight.h"
 
 Heap   *orderEdges(LinkedGraph *pGraph)
 {
     Heap       *pMinHeap;
     int        i;
     pMinHeap = createHeap(pGraph->maxVertexCount);
     if (!pMinHeap)
        return (NULL);
    i = 0;
    while (i < pGraph->maxVertexCount)
    {
        if (checkVertexValid(pGraph, i))
        {
            ListNode    *vertexInfo = pGraph->ppAdjEdge[i]->headerNode.pLink;
            while (vertexInfo)
            {
                if (i < vertexInfo->data.vertexID)
                {
                HeapNode   element;
                element.data = vertexInfo->data.weight;
                element.toVertexId = vertexInfo->data.vertexID;
                element.fromVertexId = i;
                insertMinHeapNode(pMinHeap, element);
                }
                vertexInfo = vertexInfo->pLink;        
            }
        }
        i++;
    }
    return (pMinHeap);
 }
int checkCycle(LinkedGraph *pMinWeightTree, int fromVertex, int toVertex)
{
    LinkedStack *pStack;
    StackNode   stackElement;
    int         *pVisited;
    int         i;
    
    pStack = createLinkedStack();
    pVisited = calloc(pStack->currentElementCount, sizeof(int));
    pVisited[fromVertex] = TRUE;
    stackElement.data = fromVertex;
    push(pStack, stackElement);
    while (!isLinkedStackEmpty(pStack))
    {
        ListNode    *edgeList;
        StackNode   *vertex = pop(pStack);
    
        if (vertex && vertex->data == toVertex)
        {
            printf("%d -> %d is Cycle \n", fromVertex, toVertex);
            return (TRUE);
        }
        edgeList = pMinWeightTree->ppAdjEdge[vertex->data]->headerNode.pLink;
        while (edgeList)
        {
            if (pVisited[edgeList->data.vertexID] == NOT_USED)
            {
                stackElement.data = edgeList->data.vertexID;
                pVisited[edgeList->data.vertexID] = USED;
                push(pStack, stackElement);
            }
            edgeList = edgeList->pLink;
        }
    }
    free(pVisited);
    deleteLinkedStack(pStack);
    return (FALSE);
}

 LinkedGraph    *kruskal(LinkedGraph *pGraph)
 {
     LinkedGraph    *pMinWeightTree;
     Heap           *pMinHeap;
     int            i;
     int            isCycle;

     pMinWeightTree = createLinkedGraph(pGraph->maxVertexCount);
     if (!pMinWeightTree)
        return (NULL);
     pMinHeap = orderEdges(pGraph);
    i = 1;
    while (i < pGraph->currentEdgeCount)
    {
        HeapNode *minWeightEdge = deleteMinHeapNode(pMinHeap);
        int from = minWeightEdge->fromVertexId;
        int to = minWeightEdge->toVertexId;
        isCycle = checkCycle(pMinWeightTree,from, to);
        if (!isCycle)
        {
            if (pMinWeightTree->pVertex[from] == NOT_USED)
                addVertexLG(pMinWeightTree, from);
            if (pMinWeightTree->pVertex[to] == NOT_USED)
                addVertexLG(pMinWeightTree, to);
            addEdgeWithWeightLG(pMinWeightTree, from, to, minWeightEdge->data);
        }
        i++;
        free(minWeightEdge);
        if (pMinWeightTree->currentVertexCount == pGraph->currentVertexCount)
            break;
    }
    deleteHeap(pMinHeap);
    return (pMinWeightTree);
 }