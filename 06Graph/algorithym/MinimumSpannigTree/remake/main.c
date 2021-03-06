
#include "find_minimum_weight.h"
#include "commonheader.h"

int	main(void)
{
	int size = 6;
	LinkedGraph *lg = createLinkedGraph(size);
	LinkedGraph *kru_tree;
	LinkedGraph *prim_tree;

	for (int i = 0 ; i < size; i++)
		addVertexLG(lg, i);
	addEdgeWithWeightLG(lg, 1, 0, 4);
	addEdgeWithWeightLG(lg, 1, 2, 2);
	addEdgeWithWeightLG(lg, 0, 2, 3);
	addEdgeWithWeightLG(lg, 2, 3, 1);
	addEdgeWithWeightLG(lg, 3, 4, 1);
	addEdgeWithWeightLG(lg, 3, 5, 5);
	addEdgeWithWeightLG(lg, 4, 5, 6);
	
	printf("\n========GRAPH=============\n");
	displayLinkedGraph(lg);
	
	printf("\n========PRIM_RESULT=============\n");
	prim_tree = mstPrim(lg,0);
	displayLinkedGraph(prim_tree);

	printf("\n========KRUSKAL_RESULT=============\n");
	kru_tree = kruskal(lg);
	displayLinkedGraph(kru_tree);
}