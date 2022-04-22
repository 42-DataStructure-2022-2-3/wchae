#include "arraylist.h"

ArrayList* createArrayList(int maxElementCount)
{
    ArrayList* ret;

    if (maxElementCount < 1)
        return (NULL);
    ret = (ArrayList*)malloc(sizeof(ArrayList));
    if (!ret)
        return (NULL);
    ret->pElement = (ArrayListNode*)malloc(sizeof(ArrayListNode) * maxElementCount);
    if (!ret->pElement)
    {
        free(ret);
        return (NULL);
    }
    ret->maxElementCount = maxElementCount;
    ret->currentElementCount = 0;
    
    return (ret);
}
void deleteArrayList(ArrayList* pList)
{
    free(pList->pElement);
    free(pList);
}

int isArrayListFull(ArrayList* pList)
{
    if (pList->maxElementCount == pList->currentElementCount)
        return (TRUE);
    return (FALSE);
}
int addALElement(ArrayList* pList, int position, ArrayListNode element)
{
    int i;
    int j;
    if (!pList || position < 0 || position > pList->maxElementCount)
        return (FALSE);
    if (isArrayListFull(pList))
    {
        ArrayListNode *newPList = (ArrayListNode*)malloc(sizeof(ArrayListNode) * pList->maxElementCount * 2);
        i = 0;
        while (i < pList->currentElementCount)
        {
            newPList[i] = pList->pElement[i];
            i++;
        }
        free(pList->pElement);
        pList->pElement = newPList;
        pList->maxElementCount *= 2;
    }
    i = pList->currentElementCount;
    while (position <= i)
    {
        pList->pElement[i + 1] = pList->pElement[i];
        i--; 
    }
    pList->currentElementCount++;
    pList->pElement[position] = element;
    return (TRUE);
}
int removeALElement(ArrayList* pList, int position)
{
    int i;
    if (!pList || position < 0 || pList->currentElementCount <= position)
        return (FALSE);
    i = position;
    pList->currentElementCount--;
    while (i < pList->currentElementCount)
    {
        pList->pElement[i] = pList->pElement[i + 1];
        i++;
    }
    return (TRUE);
}
ArrayListNode* getALElement(ArrayList* pList, int position)
{
    if (!pList || position < 0 || pList->currentElementCount <= position)
        return (FALSE);
    return (&(pList->pElement[position]));
}

void displayArrayList(ArrayList* pList)
{
    int i;
    if (!pList)
        return ;
    i = 0;
    while (i < pList->currentElementCount)
    {
        printf("%d\n", pList->pElement[i++].data);
    }
}
void clearArrayList(ArrayList* pList)
{
    int i;

    i = 0;
    if (!pList)
        return ;
    while (i < pList->currentElementCount)
        pList->pElement[i++].data = 0;
    pList->currentElementCount = 0;
}

int getArrayListLength(ArrayList* pList)
{
    if (!pList)
        return (FALSE);
    return (pList->currentElementCount);
}

int main()
{
    ArrayList *list;
    ArrayListNode node;

    node.data = 42;
    list = createArrayList(5);
    addALElement(list, 0, node);
    node.data = 32;
    addALElement(list, 1, node);
    node.data = 22;
    addALElement(list, 2, node);
    node.data = 12;
    addALElement(list, 3, node);
    node.data = 2;
    addALElement(list, 4, node);
    node.data = 0;
    addALElement(list, 2, node);
    displayArrayList(list);
    printf("===================\n");
    printf("del 6\n");
    removeALElement(list, 5);
    displayArrayList(list);
    printf("del 4\n");
    removeALElement(list, 3);
    displayArrayList(list);
    clearArrayList(list);
    displayArrayList(list);
}