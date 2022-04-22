#include "stack.h"

ArrayStack* createArrayStack(int maxElementCount)
{
	if (maxElementCount <= 0)
		return NULL;
	ArrayStack	*new = (ArrayStack *)calloc(1, sizeof(ArrayStack));
	if (!new)
		return FALSE;
	new->pElement = calloc(maxElementCount, sizeof(ArrayStackNode));
	if (!new->pElement)
	{
		free(new);
		new = NULL;
		return FALSE;
	}
	new->maxElementCount = maxElementCount;
	return new;
}
int isArrayStackFull(ArrayStack* pList)
{
	if(!pList)
		return (-1);
	return (pList->currentElementCount == pList->maxElementCount);
}

int	push(ArrayStack *pList, ArrayStackNode element)
{
	if (!pList|| isArrayStackFull(pList))
		return (-1);
	pList->pElement[pList->currentElementCount] = element;
	pList->currentElementCount++;
	return (TRUE);
}

int	isArrayStackEmpty(ArrayStack *pList)
{
	if(!pList)
		return (-1);
	return (pList->currentElementCount == 0);
}

ArrayStackNode *peek(ArrayStack *pList)
{
	if (!pList || isArrayStackEmpty(pList))
		return (FALSE);
	return (&pList->pElement[pList->currentElementCount - 1]);
}

//data 만 주어야하는가?
//포인터 타입 반환을 위해 새로운 값을 할당해서 주는가
//그냥 주소값을 주고 카운트만-- 한다면?
ArrayStackNode *pop(ArrayStack *pList)
{
	ArrayStackNode	*duplicated;
	ArrayStackNode	*original;

	if (!original)
		return (FALSE);
	duplicated = (ArrayStackNode*)malloc(sizeof(ArrayStackNode));
	if (!duplicated)	
		return (FALSE);
	*duplicated = *original;
	pList->currentElementCount--;
	return (duplicated);
}

void deleteArrayStack(ArrayStack* pList)
{
	if (!pList)
		return ;
	free(pList->pElement);
	free(pList);
	pList = NULL;
}

void displayArrayStack(ArrayStack* pList)
{
	if (!pList)
		return ;
	if (pList->currentElementCount == 0)
		printf("Stack is Empty \n");
	for (int i = pList->currentElementCount - 1; 0 <= i; i--)
		printf("%c\n",pList->pElement[i].data);
}

int getArrayStackLength(ArrayStack* pList)
{
	if (!pList)
		return (-1);
	return (pList->currentElementCount);
}

int main()
{
	ArrayStack *pList = createArrayStack(4);
	ArrayStackNode node;
	node.data ='A';
	push(pList, node);
	node.data ='B';
	push(pList, node);
	node.data ='C';
	push(pList, node);
	node.data ='D';
	push(pList, node);
	displayArrayStack(pList);
	pop(pList);
	printf("=======after pop========\n");
	displayArrayStack(pList);
	peek(pList);
}