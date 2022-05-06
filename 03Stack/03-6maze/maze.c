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

void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, MapPosition endPos, LinkedStack *pStack)
{
	StackNode	*node;

	int is_empty = FALSE;
	int is_found = FALSE;
	int markArray[HEIGHT][WIDTH];
	int i = 0;

	if (!pStack)
		return ;
	MapPosition new = startPos;
	new.direction = 0;
	pushLSMapPosition(pStack, new);
	while (!is_found && !is_empty)
	{
		node = pop(pStack);
		if (!node)
			break;
		int x = node->data.x;
		int y = node->data.y;
		int dir = node->data.direction;
		while (!is_found && dir < NUM_DIRECTIONS)
		{
			int moveX = x + DIRECTION_OFFSETS[dir][0];
			int moveY = y + DIRECTION_OFFSETS[dir][1];
			if (is_inrange(moveX, moveY) && markArray[moveY][moveX] == NOT_VISIT && mazeArray[moveY][moveX] == NOT_VISIT)
			{
				MapPosition newPosition;
				newPosition.x = x;
				newPosition.y = y;
				newPosition.direction = dir + 1;
				pushLSMapPosition(pStack, newPosition);
				markArray[y][x] = VISIT;

				x = moveX;
				y = moveY;
				dir = 0;

				if (moveX == endPos.x && moveY == endPos.y)
				{
					is_found = TRUE;
					newPosition.x = moveX;
					newPosition.y = moveY;
					newPosition.direction = 0;
					pushLSMapPosition(pStack, newPosition);
					markArray[moveY][moveX] = VISIT;
				}
			}
			else
				dir++;
		}
		free(node);
		is_empty = isLinkedStackEmpty(pStack);
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