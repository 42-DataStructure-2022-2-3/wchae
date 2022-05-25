#include "graphlinkedlist.h"

LinkedList* createLinkedList()
{
    LinkedList  *list;

    list = (LinkedList *)calloc(1, sizeof(LinkedList));
    if (!list)
        return (NULL);
    return (list);    
}

int addLLElement(LinkedList* pList, int position, ListNode element)
{
    ListNode    *prev;
    ListNode    *new;
    int         i;

    if (!pList || position < 0 || pList->currentElementCount < position)
        return (FALSE);
    new = (ListNode *)calloc(1, sizeof(ListNode));
    if (!new)
        return (FALSE);
    i = 0;
    new->data = element.data;
    prev = &(pList->headerNode);
    while (i < position)
    {
        prev = prev->pLink;
        i++;        
    }
    new->pLink = prev->pLink;
    prev->pLink = new;
    pList->currentElementCount++;
    return (TRUE);
}

int removeLLElement(LinkedList* pList, int position)
{
    int i;
    ListNode *prev;
    ListNode *current;
    if (!pList || pList->currentElementCount <= position)
        return (FALSE);
    i = 0;
    prev = &(pList->headerNode);
    while (i < position)
    {
        prev = prev->pLink;
        i++;
    }
    current = prev->pLink;
    prev->pLink = current->pLink;
    pList->currentElementCount--;
    free(current);
    return (TRUE);
}
ListNode* getLLElement(LinkedList* pList, int position)
{
    int i;
    ListNode *node;
    if (!pList || pList->currentElementCount <= position)
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

void clearLinkedList(LinkedList* pList)
{
    while (pList->currentElementCount)
        removeLLElement(pList, pList->currentElementCount - 1);
    pList->headerNode.pLink = NULL;
}

int getLinkedListLength(LinkedList* pList)
{
    if (!pList)
        return (FALSE);
    return (pList->currentElementCount);
}

void deleteLinkedList(LinkedList* pList)
{
    ListNode    *tmp;
    clearLinkedList(pList);
    free(pList);
}
void displayLinkedList(LinkedList* pList)
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