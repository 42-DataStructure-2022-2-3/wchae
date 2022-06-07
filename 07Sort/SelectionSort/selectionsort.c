#include <stdio.h>
#include <stdlib.h>

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

void	selectionSort(int	arr[], int arr_len)
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

int		main(void)
{
	int	arr[8] = {80, 50, 70, 10, 60, 20, 40, 30};
	int	min = 99999999;
	printArray(arr, 8);
	selectionSort(arr, 8);
	printArray(arr, 8);

}