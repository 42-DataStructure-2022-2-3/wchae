#include "../commonheader.h"

void	selectionsort(int	arr[], int arr_len)
{
	int min;
	int tmp;
	int i,j;

	for (i = 0; i < arr_len - 1; i++)
	{
		min = i;
		for (j = i + 1; j < arr_len; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
		printf("%d 번째 \n",i + 1);
		printArray(arr, arr_len);
	}
}