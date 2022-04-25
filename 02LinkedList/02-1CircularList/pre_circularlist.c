#include "circularlist.h"

CircularList* createCircularList()
{
	CircularList *createdList;

	createdList = (CircularList *)calloc(1, sizeof(CircularList));
	if (!createdList)
		return (FALSE);
	return createdList;
}

ListNode *createNode(ListNode element)
{
	ListNode *node = (ListNode *)calloc(1, sizeof(ListNode));
	if (!node)
		return (FALSE);
	return node;
}

int addCLElement(CircularList* pList, int position, ListNode element)
{
	ListNode *node;

	node = createNode(element);
	*node = element;
	//맨앞 노드 추가일때
	if (position == 0)
	{
		//비어있는 리스트일때
		if (!pList->headerNode.pLink)
		{
			pList->headerNode.pLink = node;
			node->pLink = node;
		}
		//리스트가 비어있지않을때
		else
		{
			ListNode *lastNode;
			lastNode = getCLElement(pList, pList->currentElementCount - 1);
			printf("ln : %d \n",lastNode->data);
			lastNode->pLink = node;
			node->pLink = pList->headerNode.pLink;
			pList->headerNode.pLink = node;
		}
	}
	//맨앞 노드 추가가 아닐때
	else
	{
		ListNode *prev;
		prev = &pList->headerNode;
		for (int i = 0; i < position; i++)
			prev = prev->pLink;
		node->pLink = prev->pLink;
		prev->pLink = node;
	}
	pList->currentElementCount++;
	return (TRUE);
}

int removeCLElement(CircularList* pList, int position);
ListNode* getCLElement(CircularList* pList, int position)
{
	int i;
    ListNode *node;
    if (!pList || pList->currentElementCount < position)
        return (FALSE);
    i = 0;
    node = pList->headerNode.pLink;
    while (i < position)
    {
        node = node->pLink;
        i++;
    }
    return (node);
}

void clearCircularList(CircularList* pList);
void deleteCircularList(CircularList* pList);
int getCircularListLength(CircularList* pList);

void displayCircularList(CircularList* pList)
{
    ListNode *node;
    int i;
    if (!pList)
        return ;
    i = 0;
    node = pList->headerNode.pLink;
    while (i < pList->currentElementCount)
    {
        printf("%d\n", node->data);
        node = node->pLink;
        i++;
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
	addCLElement(pList, 0, node);
	node.data = 0;
	addCLElement(pList, 3, node);
	displayCircularList(pList);
}