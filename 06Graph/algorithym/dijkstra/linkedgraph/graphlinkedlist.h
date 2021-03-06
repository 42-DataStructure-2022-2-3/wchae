#ifndef _GRAPH_LINKEDLIST_
#define _GRAPH_LINKEDLIST_
#include "../linkedlist/linkedlist.h"

#define C_RED  "\033[31m"
#define C_NRML "\033[0m"

typedef struct LinkedGraphType
{
	int maxVertexCount;
	int currentVertexCount;
	int currentEdgeCount;
	int graphType;
	int	*pVertex;
	LinkedList **ppAdjEdge;
} LinkedGraph;

typedef struct GraphEdgeType
{
	int vertexIdFrom;
	int vertexIdTo;
	int weight;

} GraphEdge;
/* LinkedGraph */

LinkedGraph* createLinkedGraph(int maxVertexCount);
LinkedGraph* createLinkedDirectedGraph(int maxVertexCount);
int isEmptyLG(LinkedGraph* pGraph);
int addVertexLG(LinkedGraph* pGraph, int vertexID);
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID);
int addEdgeWithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight);
int checkVertexValid(LinkedGraph* pGraph, int vertexID);
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID);
int removeVertexLG(LinkedGraph* pGraph, int vertexID);
void deleteLinkedGraph(LinkedGraph* pGraph);
void displayLinkedGraph(LinkedGraph* pGraph);
void displayBFSLinkedGraph(LinkedGraph *pGraph);

/* Additional */
int	getMaxVertexCountLG(LinkedGraph *pGraph);
int	getVertexCountLG(LinkedGraph *pGraph);
int	getEdgeCountLG(LinkedGraph *pGraph);
int findGraphNodePosition(LinkedList *edgeList, int toVertexId);


#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define USED				1
#define NOT_USED			0

#define SUCCESS				1
#define FAIL				0

#define TRUE				1
#define FALSE				0

#define GRAPH_UNDIRECTED	1
#define GRAPH_DIRECTED		2

#endif