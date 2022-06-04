#include "linkeddeque.h"
#include "../commonheader.h"

LinkedDeque* createLinkedDeque()
{
	LinkedDeque *pDeque;
	pDeque = calloc(1, sizeof(LinkedDeque));
	if (!pDeque)
		return FALSE;
	return pDeque;
}
DequeNode *createNode(DequeNode element)
{
	DequeNode *new;
	new = calloc(1, sizeof(DequeNode));
	if (!new)
		return (FALSE);
	*new = element;
	return (new);
}
int insertFrontLD(LinkedDeque* pDeque, DequeNode element)
{
	DequeNode *new;
	DequeNode *prev;

	if (!pDeque)
		return FALSE;
	new = createNode(element);
	if (pDeque->currentElementCount == 0)
	{
		pDeque->pFrontNode = new;
		pDeque->pRearNode = new;
	}
	else
	{
		prev = pDeque->pFrontNode;
		prev->pLLink = new;
		new->pRLink = prev;
		pDeque->pFrontNode = new;
	}
	pDeque->currentElementCount++;
	return TRUE;
}
int insertRearLD(LinkedDeque* pDeque, DequeNode element)
{
	DequeNode *new;
	DequeNode *post;

	if (!pDeque)
		return FALSE;
	new = createNode(element);
	if (pDeque->currentElementCount == 0)
	{
		pDeque->pFrontNode = new;
		pDeque->pRearNode = new;
	}
	else
	{
		post = pDeque->pRearNode;
		post->pRLink = new;
		new->pLLink = post;
		pDeque->pRearNode = new;
	}
	pDeque->currentElementCount++;
	return TRUE;
}

DequeNode* deleteFrontLD(LinkedDeque* pDeque)
{
	DequeNode* new;
	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return FALSE;
	new = pDeque->pFrontNode;
	if (new->pRLink)
		new->pRLink->pLLink = NULL;
	pDeque->pFrontNode = new->pRLink;
	new->pRLink = NULL;
	pDeque->currentElementCount--;
	if (pDeque->currentElementCount == 0)
		pDeque->pRearNode = NULL;
	return (new);
}

DequeNode* deleteRearLD(LinkedDeque* pDeque)
{
	DequeNode *new;
	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return FALSE;
	new = pDeque->pRearNode;
	// if (new->pLLink)
	// 	new->pLLink->pRLink = NULL;
	if (1 < pDeque->currentElementCount)
		pDeque->pRearNode = new->pLLink;
	else if (pDeque->currentElementCount == 1)
		pDeque->pRearNode = NULL;
	new->pLLink = NULL;
	pDeque->currentElementCount--;
	if (pDeque->currentElementCount == 0)
		pDeque->pFrontNode = NULL;
	return (new);
}

DequeNode* peekFrontLD(LinkedDeque* pDeque)
{
	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return FALSE;
	return pDeque->pFrontNode;
}

DequeNode* peekRearLD(LinkedDeque* pDeque)
{
	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return FALSE;
	return pDeque->pRearNode;
}

void deleteLinkedDeque(LinkedDeque* pDeque)
{
	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return ;
	while (peekFrontLD(pDeque))
		free(deleteFrontLD(pDeque));
	free(pDeque);
	pDeque = NULL;
}

int isLinkedDequeFull(LinkedDeque* pDeque)
{
	return FALSE;
}
int isLinkedDequeEmpty(LinkedDeque* pDeque)
{
	if (!pDeque)
		return FALSE;
	return (pDeque->currentElementCount == 0);
}
void displayDequeue(LinkedDeque* pDeque)
{
	DequeNode *next;

	if (!pDeque || isLinkedDequeEmpty(pDeque))
		return ;
	next = pDeque->pFrontNode;
	while (next)
	{
		printf("data = %d \n", next->data.vertexID);
		next = next->pRLink;
	}
}
