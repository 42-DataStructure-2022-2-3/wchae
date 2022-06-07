#include "../commonheader.h"

void	printArray(int *arr, int arr_len)
{
	int i = 0;
	while (i < arr_len)
	{
		printf(" %d ", arr[i]);
		i++;
	}
	printf("\n");
}

int		main(void)
{
	int	arr[8] = {80, 50, 70, 10, 60, 20, 40, 30};
	int	min = 99999999;
	printf("\n\n ===========ORIGINAL=============\n\n");
	printArray(arr, 8);
	printf("\n\n ===========BUBBLE=============\n\n");
	bubblesort(arr, 8);
	printArray(arr, 8);
}