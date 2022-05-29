#include "gp.h"

int main(void)
{
	int size = 8;
	LinkedGraph *lg = createGraph(size);

	for (int i = 0 ; i < size; i++)
		addVertex(lg, i);
	addEdge(lg, 0, 1);
	addEdge(lg, 1, 3);
	addEdge(lg, 1, 4);
	addEdge(lg, 2, 5);
	addEdge(lg, 2, 6);
	addEdge(lg, 3, 7);
	addEdge(lg, 4, 5);
	//ERROR TEST
	addEdge(lg, -1, 99);	
	addEdge(lg, 100, 99);

	displayLinkedGraph(lg);
	printf("==============\n");
	//REMOVE EDGE
	// removeEdge(lg, 0, 1);
	removeEdge(lg, 1, 7);
	// removeEdge(lg, 2, 5);
	removeVertex(lg, 4);

	displayLinkedGraph(lg);
	
}