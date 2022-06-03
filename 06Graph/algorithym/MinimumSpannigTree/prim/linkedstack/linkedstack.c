#include "linkedstack.h"

LinkedStack* createLinkedStack()
{
	LinkedStack *new = (LinkedStack *)calloc(1, sizeof(LinkedStack));
	if (!new)
		return (FALSE);
	return (new);
}

int isLinkedStackEmpty(LinkedStack* pList)
{
	if (!pList)
		return (-1);
	return (pList->currentElementCount == 0);
}

StackNode *peek(LinkedStack *pList)
{
	if (!pList || pList->currentElementCount == 0)
		return (FALSE);
	return (pList->pTop);
}

int	push(LinkedStack *pList, StackNode element)
{
	StackNode *new;
	StackNode *prev;

	if(!pList)
		return (-1);
	new = (StackNode *)calloc(1, sizeof(StackNode));
	if (!new)
		return (FALSE);
	*new = element;
	prev = peek(pList);
	new->pLink = prev;
	pList->pTop = new;
	pList->currentElementCount++;
	return (TRUE);
}

StackNode *pop(LinkedStack *pList)
{
	StackNode *element;
	element = peek(pList);
	if (!element)
		return (FALSE);
	if (pList->currentElementCount == 1)
		pList->pTop = NULL;
	else
		pList->pTop = element->pLink;
	pList->currentElementCount--;
	return (element);
}

int deleteStackElement(LinkedStack* pList)
{
	if (!pList || pList->currentElementCount == 0)
		return (-1);
	while (pList->currentElementCount)
		free(pop(pList));
	return (TRUE);
}

void deleteLinkedStack(LinkedStack* pList)
{
	deleteStackElement(pList);
	free(pList);
	pList = NULL;
}

void displayLinkedStack(LinkedStack* pList)
{
	StackNode *current;

	if (!pList || isLinkedStackEmpty(pList))
		return ;
	current = pList->pTop;
	if(!current)
		printf("Stack is Empty.\n");
	while (current)
	{
		printf("%d ",current->data);
		current = current->pLink;
	}
	printf("\n");
}

int getLinkedStackLength(LinkedStack* pList)
{
	if(!pList)
		return (-1);
	return (pList->currentElementCount);
}
