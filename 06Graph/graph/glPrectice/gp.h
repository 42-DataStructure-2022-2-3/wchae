#ifndef _GP_H
#define _GP_H

#include <stdio.h>
#include <stdlib.h>
#include "graphlinkedlist.h"

typedef struct LinkedGraphType
{
	int			size;
	int			*pVertex;
	LinkedList	**ppAdjEdge;
	int			graphType;

	int			currentEdgeCount;
	int			currentVertexCount;
} LinkedGraph;

LinkedGraph *createGraph(int size);
LinkedGraph	*createDirectedGraph(int size);
int	checkVertexVerify(LinkedGraph *pGraph, int vertexId);
int	addVertex(LinkedGraph *pGraph, int vertexId);
int	addEdge(LinkedGraph *pGraph, int fromVertex, int startVertex);
int	addEdgeWithWeight(LinkedGraph *pGraph, int fromVertex, int startVertex, int weight);
int isEmpty(LinkedGraph *pGraph);
int removeEdge(LinkedGraph *pGraph, int fromVertex, int startVertex);
int removeVertex(LinkedGraph *pGraph, int vertex);
void displayLinkedGraph(LinkedGraph *pGraph);
void deleteLinkedGraph(LinkedGraph **pGraph);
#endif