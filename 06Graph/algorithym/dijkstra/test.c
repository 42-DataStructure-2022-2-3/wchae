#include "dijkstra.h"
#include "commonheader.h"

int main(void)
{
	int size = 6;
	LinkedGraph *lg = createLinkedGraph(size);

	for (int i = 0 ; i < size; i++)
		addVertexLG(lg, i);
	addEdgeWithWeightLG(lg, 1, 0, 4);
	addEdgeWithWeightLG(lg, 1, 2, 2);
	addEdgeWithWeightLG(lg, 0, 2, 3);
	addEdgeWithWeightLG(lg, 2, 3, 1);
	addEdgeWithWeightLG(lg, 3, 4, 1);
	addEdgeWithWeightLG(lg, 3, 5, 5);
	addEdgeWithWeightLG(lg, 4, 5, 6);

	displayLinkedGraph(lg);
	printf("\n========kruskal=============\n");
	int *path = shortestPathDijkstra(lg, 0);
	for (int i = 0; i < size; i++)
	{
		printf("%d -> ", path[i]);
		i++;
	}
}