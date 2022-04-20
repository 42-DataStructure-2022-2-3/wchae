#include "circularlist.h"

CircularList* createCircularList()
{
	CircularList *list;
	list = (CircularList *)calloc(1,sizeof(CircularList));
	if (!list)
		return (FALSE);
	return (list);
}

int isValidPosition(CircularList* pList, int position)
{
	if (!pList || position < 0 || pList->currentElementCount < position)
		return (FALSE);
	return (TRUE);
}

int addCLElement(CircularList* pList, int position, ListNode element)
{
	ListNode *new;
	ListNode *last;
	ListNode *curr;

	if (!isValidPosition(pList, position))
		return (FALSE);
	new = (ListNode *)calloc(1, sizeof(ListNode));
	*new = element;
	if (position == 0)//0 인덱스의 노드추가인가?
	{
		if (!pList->headerNode.pLink)	//리스트가 비었는가?
		{
			pList->headerNode.pLink = new;
			new->pLink = new;
		}
		else
		{
			last = getCLElement(pList, pList->currentElementCount - 1);
			new->pLink = pList->headerNode.pLink;
			pList->headerNode.pLink = new;
			last->pLink = new;
		}
	}
	else
	{
		curr = &(pList->headerNode);
		for(int i = 0; i < position; i++)
			curr = curr->pLink;
		new->pLink = curr->pLink;
		curr->pLink = new;
	}
	pList->currentElementCount++;
	return (TRUE);
}
int removeCLElement(CircularList* pList, int position)
{
	ListNode	*delNode;
	ListNode	*lastNode;
	ListNode	*prevNode;

	if (!isValidPosition(pList, position))
		return (FALSE);
	if (position == 0)
	{
		if (pList->currentElementCount == 1)
		{
			free(pList->headerNode.pLink);
			pList->headerNode.pLink = NULL;
		}
		else
		{
			delNode = getCLElement(pList, position);
			pList->headerNode.pLink = delNode->pLink;
			lastNode = getCLElement(pList, pList->currentElementCount - 1);
			lastNode->pLink = delNode->pLink;
			free(delNode);
		}
	}
	else
	{
		prevNode = getCLElement(pList, position - 1);
		delNode = prevNode->pLink;
		prevNode->pLink = delNode->pLink;
		free (delNode);
	}
	pList->currentElementCount--;
	return (TRUE);
}
ListNode* getCLElement(CircularList* pList, int position)
{
    ListNode *node;

	if(isValidPosition(pList, position))
    node = &pList->headerNode;
	for (int i = 0; i <= position; i++)
        node = node->pLink;
    return (node);
}

void clearCircularList(CircularList* pList)
{
	if (!pList)
		return ;
	while (pList->currentElementCount)
		removeCLElement(pList, pList->currentElementCount - 1);
}

void deleteCircularList(CircularList* pList)
{
	if (!pList)
		return ;
	clearCircularList(pList);
	free(pList);
	pList = NULL;
}
int getCircularListLength(CircularList* pList)
{
	if (!pList)
		return (FALSE);
	return (pList->currentElementCount);
}
void displayCircularList(CircularList *pList)
{
	ListNode *node;
    if (!pList)
        return ;
    node = pList->headerNode.pLink; 
    for (int i = 0; i < pList->currentElementCount; i++)
    {
        printf("%d\n", node->data);
        node = node->pLink;
    }
}

int	main(void)
{
	CircularList *pList = createCircularList();
	ListNode node;

	node.data = 1;
	addCLElement(pList, 0, node);
	node.data = 2;
	addCLElement(pList, 1, node);
	node.data = 3;
	addCLElement(pList, 2, node);
	node.data = 4;
	addCLElement(pList, 0, node); // 4123
	node.data = 0;
	addCLElement(pList, 3, node); // 4 1 2 0 3
	removeCLElement(pList, 3);
	deleteCircularList(pList);
	displayCircularList(pList);
	while (1)
	{

	}
}