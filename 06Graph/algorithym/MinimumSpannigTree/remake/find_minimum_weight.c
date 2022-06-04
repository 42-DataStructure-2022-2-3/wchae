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
 int checkEdge(int ver)

void    getMinWeight(LinkedGraph *pGraph, LinkedGraph *minWeightTree, int from, GraphEdge *minWeightEdge)
{
    int isCycle;
    int isExist;
    LinkedList *edgeList;
    ListNode *vertex;

     edgeList = pGraph->ppAdjEdge[from];
     vertex = edgeList->headerNode.pLink;
     while (vertex)
     {
         if (vertex->data.weight < minWeightEdge->weight)
         {
             //checkEdge
             isExist = checkEdge(minWeightTree, from, vertex->data.vertexID);
             isCycle = checkCycle(minWeightTree, from, vertex->data.vertexID);
             if (!isCycle && !isExist)
             {
                 minWeightEdge->vertexIdFrom = from;
                 minWeightEdge->vertexIdTo = vertex->data.vertexID;
                 minWeightEdge->weight = vertex->data.weight;
             }

         }
         vertex = vertex->pLink;
     }
}


 LinkedGraph    *mstPrim(LinkedGraph *pGraph, int startVertex)
 {
     LinkedGraph *minWeightTree;

     if (!pGraph)
        return (NULL);

    minWeightTree = createLinkedGraph(pGraph->maxVertexCount);
    addVertexLG(minWeightTree, startVertex);

    while (getVertexCountLG(minWeightTree) < pGraph->maxVertexCount)
    {
        GraphEdge minWeightEdge;
        int i;

        minWeightEdge.vertexIdFrom = 0;
        minWeightEdge.vertexIdTo = 0;
        minWeightEdge.weight = INT32_MAX;
        i = 0;
        while (i < pGraph->maxVertexCount)
        {
            if (minWeightTree->pVertex[i] == USED)
                getMinWeight(pGraph, minWeightTree, i, &minWeightEdge);
            i++;
        }
		printf("[%d], 최소 가중치: (%d, %d)-> %d\n", getVertexCountLG(minWeightTree), minWeightEdge.vertexIdFrom, minWeightEdge.vertexIdTo, minWeightEdge.weight);
        addVertexLG(minWeightTree, minWeightEdge.vertexIdTo);
        addEdgeWithWeightLG(minWeightTree, minWeightEdge.vertexIdFrom, minWeightEdge.vertexIdTo, minWeightEdge.weight);
    }
    return (minWeightTree);
 }