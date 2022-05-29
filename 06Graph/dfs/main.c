#include "dfs.h"

// void testSet(void)
// {
// 		LinkedGraph *lg = createLinkedGraph(size);

// }

int main(void)
{
	int size = 8;
	LinkedGraph *lg = createLinkedGraph(size);

	for (int i = 0 ; i < size; i++)
		addVertexLG(lg, i);
	addEdgeLG(lg, 0, 1);
	addEdgeLG(lg, 0, 2);
	addEdgeLG(lg, 1, 3);
	addEdgeLG(lg, 1, 4);
	addEdgeLG(lg, 2, 5);
	addEdgeLG(lg, 2, 6);
	addEdgeLG(lg, 3, 7);
	addEdgeLG(lg, 4, 5);
	//ERROR TEST
	// addEdgeLG(lg, -1, 99);	
	// addEdgeLG(lg, 100, 99);

	displayLinkedGraph(lg);
	printf("\n==============\n");
	dfs(lg, 0);

}