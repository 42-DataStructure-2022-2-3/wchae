#ifndef _PRIM_H
# define _PRIM_H

# include "graphlinkedlist.h"
# include "heap.h"
# include "linkedstack/linkedstack.h"

typedef struct GraphEdgeType
{
	int vertexIdFrom;
	int vertexIdTo;
	int weight;

} GraphEdge;
LinkedGraph *mstPrim(LinkedGraph *pGraph, int startVertexId);

#endif