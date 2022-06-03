#ifndef _KRUSKAL_H
# define _KRUSKAL_H

# include "graphlinkedlist.h"
# include "heap.h"
# include "linkedstack/linkedstack.h"


//오름차순 정렬
Heap *orderEdges(LinkedGraph *pGraph);
int	checkCycle_kru(LinkedGraph *pGraph, int fromVertexId, int toVertexId);
LinkedGraph *kruskal(LinkedGraph *pGraph);

#endif