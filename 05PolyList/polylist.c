#include "polylist.h"

PolyList* createLinkedList()
{
    PolyList * created;
    created = (PolyList *)calloc(1, sizeof(PolyList));
    if (!created)
        return (FALSE);
    return created;
}

int addPLElement(PolyList* pList, int position, ListNode element)
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
    *new = element;
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

int removePLElement(PolyList* pList, int position)
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

ListNode *getPLElement(PolyList* pList, int position)
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

void clearPolyList(PolyList* pList)
{
    while (pList->currentElementCount)
        removePLElement(pList, pList->currentElementCount - 1);
    pList->headerNode.pLink = NULL;
}

int getPolyListLength(PolyList* pList)
{
    if (!pList)
        return (FALSE);
    return (pList->currentElementCount);
}

void deletePolyList(PolyList* pList)
{
    ListNode    *tmp;
    clearPolyList(pList);
    free(pList);
}

void displayPolyList(PolyList* pList)
{
    ListNode *node;
    int i;

    if (!pList)
        return ;
    i = 0;
    node = pList->headerNode.pLink;
    while (i < pList->currentElementCount)
    {
        printf("%d ^ %d \n", node->coef, node->degree);
        node = node->pLink;
        i++;
    }
}
int addPolyNodeLast(PolyList* pList, float coef, int degree)
{
    int ret = FALSE;
    ListNode node;

    node.coef = coef;
    node.degree = degree;

    if (pList)
    {
        int len = getPolyListLength(pList);
        ret = addPLElement(pList, len, node);
    }

    return (ret);
}

PolyList* sumPolyList(PolyList* aList, PolyList* bList)
{
    PolyList* sumList;
    ListNode* aNode;
    ListNode* bNode;

    if (!aList || !bList)
        return (FALSE);
    sumList = (PolyList *)calloc(1, sizeof(PolyList));
    if (!sumList)
        return (FALSE);
    aNode = aList->headerNode.pLink;
    bNode = bList->headerNode.pLink;
    while (aNode && bNode)
    {
        if (aNode->degree == bNode->degree)
        {
            addPolyNodeLast(sumList, aNode->coef + bNode->coef, aNode->degree);
            aNode = aNode->pLink;
            bNode = bNode->pLink;
        }
        else if (aNode->degree > bNode->degree)
        {
            addPolyNodeLast(sumList, aNode->coef, aNode->degree);
            aNode = aNode->pLink;
        }
        else
        {
            addPolyNodeLast(sumList, bNode->coef, bNode->degree);
            bNode = bNode->pLink;
        }
    }
    while (aNode)
    {
        addPolyNodeLast(sumList, aNode->coef, aNode->degree);
        aNode = aNode->pLink;
    }
    while (bNode)
    {
        addPolyNodeLast(sumList, bNode->coef, bNode->degree);
        bNode = bNode->pLink;
    }
    return (sumList);  
}

int main(void)
{
   PolyList *a = createLinkedList();
   PolyList *b = createLinkedList();
   PolyList *c;

   ListNode node;
   node.coef = 6;
   node.degree = 6;
   addPLElement(a, 0, node);

   node.coef = 4;
   node.degree = 5;
   addPLElement(a, 1, node);

   node.coef = -4;
   node.degree = 2;
   addPLElement(a, 2, node);

   node.coef = 1;
   node.degree = 5;
   addPLElement(b, 0, node);

   node.coef = 2;
   node.degree = 4;
   addPLElement(b, 1, node);

   node.coef = 3;
   node.degree = 2;
   addPLElement(b, 2, node);


   node.coef = 4;
   node.degree = 0;
   addPLElement(b, 3, node);
//========setting ===============
    displayPolyList(a);
    displayPolyList(b);

    c = sumPolyList(a, b);
    printf("-------c------\n");
    displayPolyList(c);
}
