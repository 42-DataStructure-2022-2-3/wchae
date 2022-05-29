#include "dfs.h"

static void recursive(LinkedGraph *pGraph, LinkedStack *stack, int *visited)
{
	StackNode	*node;
	ListNode	*vertex;

	if (isLinkedStackEmpty(stack))
		return ;
	
	node = pop(stack);
	printf(" %d ", node->data);
	visited[node->data] = USED;
	vertex = pGraph->ppAdjEdge[node->data]->headerNode.pLink;
	while (vertex)
	{
		StackNode new;
		if (visited[vertex->data.vertexID] == NOT_USED)
		{
			visited[vertex->data.vertexID] = USED;
			new.data = vertex->data.vertexID;
			push(stack, new);
		}
		vertex = vertex->pLink;
	}
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
	printf(" %d ", startVertexId);
	visited[startVertexId] = USED;
	push(stack, element);
	recursive(pGraph, stack, visited);
	deleteLinkedStack(stack);
	free(visited);
	// system("leaks a.out");
}