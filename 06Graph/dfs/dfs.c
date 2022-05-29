#include "dfs.h"

static void recursive(LinkedGraph *pGraph, LinkedStack *stack, int *visited)
{
	StackNode	*node;
	ListNode	*vertex;

	node = pop(stack);
	while (visited[node->data])
	{
		if(!node)
			break;
		free(node);
		node = pop(stack);
	}
	if (node == NULL)
		return ;

	vertex = pGraph->ppAdjEdge[node->data]->headerNode.pLink;
	// printf("============vertex==============\n");
	// printf(" vertexID_> %d \n", vertex->data.vertexID);
	// printf("============vertex==============\n");
	
	while (vertex)
	{
		StackNode addNode;
		addNode.data = vertex->data.vertexID;
		push(stack, addNode);
		vertex = vertex->pLink;
	}
	displayLinkedStack(stack);
	printf("======================\n");
	printf("%d \n", node->data);
	printf("======================\n");
	
	visited[node->data] = USED;
	free(node);
	recursive(pGraph, stack, visited);
}

void	dfs(LinkedGraph *pGraph, int startVertexId)
{
	LinkedStack *stack = createLinkedStack();
	StackNode element;
	
	int	*visited;
	visited = calloc(pGraph->maxVertexCount, sizeof (int));
	element.data = pGraph->ppAdjEdge[startVertexId]->headerNode.pLink->data.vertexID;
	// printf(" %d ", startVertexId);
	visited[startVertexId] = USED;
	push(stack, element);
	recursive(pGraph, stack, visited);
	// system("leaks a.out");
}