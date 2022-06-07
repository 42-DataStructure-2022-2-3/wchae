#include "../commonheader.h"

void	bubblesort(int arr[], int arr_len)
{
	int i = 0, j = 0;
	int tmp = 0;

	for (i = arr_len - 1; 0 <= i; i--)
	{
		for (j = 1; j <= i; j++)
		{
			if (arr[j] < arr[j - 1])
			{
				tmp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = tmp;
			}
		}
		printf("%d 회전 \n", arr_len - 1);
		printArray(arr, arr_len);
	}
}