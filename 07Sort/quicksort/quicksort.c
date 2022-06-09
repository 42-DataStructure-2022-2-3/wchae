#include <stdio.h>
#include <stdlib.h>

void	print_array(int *arr, int size)
{
	printf("\n");
	int i = 0;
	while (i < size)
	{
		printf(" %d ", arr[i]);
		i++;
	}
}

int		partitionQuickSort(int arr[], int start, int end)
{
	int pivot = 0;
	int tmp = 0, left = 0, right = 0;
	
	left = start;
	right = end;
	pivot = end;
	while (left < right)
	{
		while ((arr[left] < arr[pivot]) && (left < right))
			left++;
		while ((arr[pivot] <= arr[right]) && (left < right))
			right--;
		
		if (left < right)
		{
			tmp = arr[left];
			arr[left] = arr[right];
			arr[right] = tmp;

			printf ("\nstart-[%d], end - [%d], pivot-[%d], in-loop.\n",start, end, arr[pivot]);
			print_array(arr, end-start+1);
		}
	}
	tmp = arr[pivot];
	arr[pivot] = arr[right];
	arr[right] = tmp;
	printf ("\nstart-[%d], end - [%d], pivot-[%d], in-loop.\n",start, end, arr[pivot]);
	print_array(arr, end - start + 1);
	return (right);
}

void 	quickSort(int arr[], int start, int end)
{
	int pivot = 0;
	if (start < end)
	{
		pivot = partitionQuickSort(arr, start, end);
		quickSort(arr, start, pivot - 1);
		quickSort(arr, pivot+1, end);
	}
}