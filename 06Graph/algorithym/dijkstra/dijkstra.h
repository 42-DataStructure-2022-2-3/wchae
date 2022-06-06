#ifndef _DIJKSTRA_H_

# define _DIJKSTRA_H_

# include "commonheader.h"
# include "linkedlist/linkedlist.h"
# include "linkedgraph/graphlinkedlist.h"
# define MAX_INT 99999

int	*shortestPathDijkstra(LinkedGraph *pGraph, int startVertex);
int	getMinDistance(int *distance, int *isSelected, int maxNodeCount);
int getEdgeWeight(LinkedGraph *pGraph, int fromVertex, int toVertex);

#endif
