#include "doublylist.h"

DoublyList* createDoublyList()
{
	DoublyList *list;

	list = (DoublyList *)calloc(1,sizeof(DoublyList));
	if (!list)
		return(NULL);
	return (list);
}

int isValidPosition(DoublyList* pList, int position)
{
	if (!pList || position < 0 || pList->currentElementCount < position)
		return (FALSE);
	return (TRUE);
}

void deleteDoublyList(DoublyList* pList)
{
	if (!pList)
		return ;
	clearDoublyList(pList);
	free(pList);
	pList = NULL;
}

DoublyListNode* createNode(int data)
{
	DoublyListNode *node;
	node = (DoublyListNode *)calloc(1, sizeof(DoublyListNode));
	if (!node)
		return (NULL);
	node->data = data;
	return (node);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
	DoublyListNode *new;
	DoublyListNode *curr;

	if (!isValidPosition(pList, position))
		return (FALSE);
	new = createNode(element.data);
	curr = &(pList->headerNode);
	for(int i = 0; i < position; i++)
		curr = curr->pRLink;
	new->pRLink = curr->pRLink;
	if(new->pRLink)
		new->pRLink->pLLink = new;
	curr->pRLink = new;
	new->pLLink = curr;
	pList->currentElementCount++;
	return (TRUE);
}

int removeDLElement(DoublyList* pList, int position)
{
	DoublyListNode *current;

	if (!isValidPosition(pList, position - 1))
		return (FALSE);
	current = &pList->headerNode;
	for (int i = 0; i <= position; i++)
		current = current->pRLink;
	if (current->pRLink)
		current->pRLink->pLLink = current->pLLink;
	current->pLLink->pRLink = current->pRLink;
	pList->currentElementCount--;
	free(current);
	return(TRUE);
}

void clearDoublyList(DoublyList* pList)
{
	if (!pList)
		return ;
	while (pList->currentElementCount)
		removeDLElement(pList, pList->currentElementCount - 1);
	pList->headerNode.pLLink = NULL;
	pList->headerNode.pRLink = NULL;
}

int getDoublyListLength(DoublyList* pList)
{
	if (!pList)
		return (FALSE);
	return (pList->currentElementCount);
}

DoublyListNode* getDLElement(DoublyList* pList, int position)
{
	DoublyListNode *curr;
	if (!isValidPosition(pList, position - 1))
		return (FALSE);
	curr = &(pList->headerNode);
	for(int i = 0; i <= position; i++)
		curr = curr->pRLink;
	return (curr);
}

void displayDoublyList(DoublyList* pList)
{
	DoublyListNode *current;
	current = pList->headerNode.pRLink;
	while (current)
	{
		printf("%d ", current->data);
		current = current->pRLink;
	}
}

int	main(void)
{
	DoublyList *list = createDoublyList();
	DoublyListNode node;
	node.data = 5;
	addDLElement(list, 0, node);
	node.data = 4;
	addDLElement(list, 0, node);
	node.data = 3;
	addDLElement(list, 0, node);
	node.data = 2;
	addDLElement(list, 0, node);
	node.data = 1;
	addDLElement(list, 0, node);
	node.data = 0;
	addDLElement(list, 3, node);
	displayDoublyList(list);
	removeDLElement(list, 3);
	displayDoublyList(list);
	clearDoublyList(list);
	while(1)
	{}
}