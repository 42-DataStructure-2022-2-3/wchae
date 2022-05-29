#include "dfs.h"

static void recursive(LinkedGraph *pGraph, LinkedStack *stack, int *visited)
{
	StackNode	*node;
	ListNode	*vertex;

	if (isLinkedStackEmpty(stack))
		return ;
	
	node = pop(stack);
	if (!visited[node->data])
		printf(" %d ", node->data);
	visited[node->data] = USED;
	vertex = pGraph->ppAdjEdge[node->data]->headerNode.pLink;
	while (vertex)
	{
		StackNode new;
		if (visited[vertex->data.vertexID] == NOT_USED)
		{

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
	StackNode 	element;
	int			*visited;

	visited = calloc(pGraph->maxVertexCount, sizeof (int));
	// element.data = pGraph->ppAdjEdge[startVertexId]->headerNode.pLink->data.vertexID;
	element.data = startVertexId;
	printf(" %d ", startVertexId);
	visited[startVertexId] = USED;
	push(stack, element);
	recursive(pGraph, stack, visited);
	deleteLinkedStack(stack);
	free(visited);
}

void	dfsNoRecursive(LinkedGraph *pGraph, int startVertexId)
{
	LinkedStack	*stack = createLinkedStack();
	StackNode	element;
	int			*visited;

	visited = calloc(pGraph->currentVertexCount, sizeof(int));
	element.data = startVertexId;
	push(stack, element);
	while (!isLinkedStackEmpty(stack))
	{
		StackNode	*top;
		ListNode	*vertexs;
	
		top = pop(stack);
		if (!visited[top->data])
			printf(" %d ",top->data);
		visited[top->data] = USED;
		vertexs = pGraph->ppAdjEdge[top->data]->headerNode.pLink;
		while (vertexs)
		{
			if (visited[vertexs->data.vertexID] == NOT_USED)
			{
				StackNode pushElement;
				pushElement.data = vertexs->data.vertexID;
				push(stack, pushElement);
			}
			vertexs = vertexs->pLink;
		}
		free(top);
	}
	deleteLinkedStack(stack);
	free(visited);
}