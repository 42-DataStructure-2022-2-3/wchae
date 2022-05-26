#include "arraygraph.h"

int	main(void)
{
	int i = 0;
	ArrayGraph *ag1;
	ArrayGraph *ag2;
	ArrayGraph *ag3;

	ag1 = createArrayGraph(6);
	ag2 = createArrayDirectedGraph(6);
	ag3 = createArrayDirectedGraph(6);
	
	for (i = 0; i < 6; i++) 
	{
		addVertexAG(ag1, i);
		addVertexAG(ag2, i);
		addVertexAG(ag3, i);
	}
	addEdgeAG(ag1, 0, 1);
	addEdgeAG(ag1, 0, 2);
	addEdgeAG(ag1, 1, 2);
	addEdgeAG(ag1, 2, 3);
	addEdgeAG(ag1, 3, 4);
	addEdgeAG(ag1, 3, 5);
	addEdgeAG(ag1, 4, 5);

	addEdgeAG(ag2, 0, 1);
	addEdgeAG(ag2, 1, 2);
	addEdgeAG(ag2, 2, 0);
	addEdgeAG(ag2, 2, 1);
	addEdgeAG(ag2, 2, 3);
	addEdgeAG(ag2, 3, 2);
	addEdgeAG(ag2, 3, 4);
	addEdgeAG(ag2, 4, 5);
	addEdgeAG(ag2, 5, 3);

	addEdgeWithWeightAG(ag3, 0, 1, 4);
	addEdgeWithWeightAG(ag3, 1, 2, 1);
	addEdgeWithWeightAG(ag3, 2, 0, 2);
	addEdgeWithWeightAG(ag3, 2, 1, 3);
	addEdgeWithWeightAG(ag3, 2, 3, 2);
	addEdgeWithWeightAG(ag3, 3, 2, 1);
	addEdgeWithWeightAG(ag3, 3, 4, 1);
	addEdgeWithWeightAG(ag3, 4, 5, 1);
	addEdgeWithWeightAG(ag3, 5, 3, 2);

	printf("G1: \n");
	displayArrayGraph(ag1);
	printf("\nG2: \n");
	displayArrayGraph(ag2);
	printf("\nG3: \n");
	displayArrayGraph(ag3);

	deleteArrayGraph(ag1);
	deleteArrayGraph(ag2);
	deleteArrayGraph(ag3);
	free(ag1);
	free(ag2);
	free(ag3);
	system("leaks a.out");
	return 0;

}