#include "mapdef.h"
#include "linkedstack.h"

void printMaze(int mazeArray[HEIGHT][WIDTH])
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if(mazeArray[i][j] == WALL)
				printf("X");
			else if (mazeArray[i][j] == VISIT)
				printf("V");
			else
				printf(" ");
		}
		printf("\n");
	}
}

int pushLSMapPosition(LinkedStack *pStack, MapPosition data)
{
    StackNode node;

    if (!pStack) 
		return FALSE;
    node.data = data;
    return push(pStack, node);
}
void showPath(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH])
{
	StackNode	*pNode;
	int	resultArray[HEIGHT][WIDTH];
	int isEmpty;

	isEmpty = FALSE;
	int i = 0;
	for (i = 0 ; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			resultArray[i][j] = mazeArray[i][j];
	}
	i = 0;
	while (!isEmpty)
	{
		pNode = pop(pStack);
		if (pNode)
		{
			int	x = pNode->data.x;
			int y = pNode->data.y;
			resultArray[y][x] = VISIT;
			if (0 < i)
				printf("<-");
			printf("(%d, %d) ", x, y);
			i++;
			free(pNode);
		}
		isEmpty = isLinkedStackEmpty(pStack);
	}
	printf("\n");
	printMaze(resultArray);
}

static	int is_inrange(int x, int y)
{
	if(0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
		return (TRUE);
	return (FALSE);
}

static	int is_valid_move(MapPosition nextMove, int **mazeArray)
{
	if (!is_inrange(nextMove.x, nextMove.y) ||
		mazeArray[nextMove.y][nextMove.x] == WALL ||
		mazeArray[nextMove.y][nextMove.x] == VISIT )
		return FALSE;
	return TRUE;
}

void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, MapPosition endPos, LinkedStack *pStack)
{
	StackNode	node;
	StackNode	*poped;

	int	is_found;
	int dir;

	is_found = FALSE;
	dir = 0;
	while (!is_found)
	{
		node.data = startPos;
		push(pStack, node);

		startPos.x += DIRECTION_OFFSETS[dir][0];
		startPos.y += DIRECTION_OFFSETS[dir][1];

		if (is_inrange(startPos.x, startPos.y) && is_valid_move(startPos, mazeArray))
		{
			
		}
		else
		{

		}
	}
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