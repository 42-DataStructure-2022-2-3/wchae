#include "linkedstack.h"
#include "mapdef.h"

int pushLSMapPosition(LinkedStack *pStack, MapPosition data)
{
	StackNode *new;
	new = calloc(1, sizeof(StackNode));
	new->data.x = data.x;
	new->data.y = data.y;
	new->data.direction = data.direction;
	new->pLink = pStack->pTop;
	pStack->currentElementCount++;
	return (TRUE);
}

static	int is_inrange(int x, int y)
{
	if(0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
		return (TRUE);
	return (FALSE);
}

void recursion(int **mazeArray, LinkedStack *stack,MapPosition endPos, int *exit)
{
	StackNode *node;
	int x;
	int y;

	if (exit || isLinkedStackEmpty(stack))
		return ;
	node = pop(stack);
	if (3 < node->data.direction)
		return;
	x = node->data.x + DIRECTION_OFFSETS[node->data.direction][0];
	y = node->data.y + DIRECTION_OFFSETS[node->data.direction][1];
	if (!is_inrange(x, y))
		node->data.direction++;
	else
	{
	MapPosition data = {0,};
		if (x == endPos.x && y == endPos.y)
			exit = TRUE;
		data.x = x;
		data.y = y;
		pushLSMapPosition(stack,data);
	}
	recursion(mazeArray, stack, endPos, exit);
}

void findPath(int mazeArray[HEIGHT][WIDTH], 
MapPosition startPos, 
MapPosition endPos, 
LinkedStack *pStack)
{
	int x;
	int y;
	int exit = FALSE;

	StackNode node;
	pushLSMapPosition(pStack, startPos);
	recursion(mazeArray, pStack, endPos, &exit);
	x = node->data.x;
	y = node->data.y;

	x = startPos.x + DIRECTION_OFFSETS[startPos.direction][0];
	y = startPos.y + DIRECTION_OFFSETS[startPos.direction][1];

}

int main()
{
    LinkedStack *pStack;
    // y, x
    pStack = createLinkedStack();

    int mazeArray[8][8] = {
        {0, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0}
    };
    MapPosition startpos;
    startpos.y = 0;
    startpos.x = 0;
    startpos.direction = 0;

    MapPosition endpos;
    endpos.y = 7;
    endpos.x = 7;
    endpos.direction = 0;

    printMaze(mazeArray);
    findPath(mazeArray, startpos, endpos, pStack);
	showPath(pStack, mazeArray);
	deleteLinkedStack(pStack);

    return 0;
}