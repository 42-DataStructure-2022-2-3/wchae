#include <stdio.h>
#include <stdlib.h>

void	ft_swap_element(int *arr, int pos_a, int pos_b)
{
	int tmp;

	tmp = arr[pos_a];
	arr[pos_a] = arr[pos_b];
	arr[pos_b] = tmp;
	return ;
}

void	print_arr(int *arr, int arr_size)
{
	for(int i = 0; i < arr_size; i++)
		printf(" %d ", arr[i]);
	printf("\n");
	return ;
}
void	bubble_sort(int *arr, int arr_size)
{
	int i, j;

	printf("ORIGINAL \n");
	print_arr(arr, arr_size);
	printf("BUBBLE SORT \n");
	for (i = arr_size - 1;  0 < i; i--)
	{
		for (j = 1; j <= i; j++)
		{
			if (arr[j] < arr[j - 1])
			{
				ft_swap_element(arr, j, j - 1);
			}
		}
		printf("Rotation %d =  ", i);
		print_arr(arr, arr_size);
	}
}

void	selection_sort(int *arr, int arr_size)
{
	int i, j, min;
	
	printf("ORIGINAL \n");
	print_arr(arr, arr_size);
	printf("SELECTION SORT \n");
	for (i = 0; i < arr_size - 1; i++)
	{
		min = i;
		for (j = i + 1; j < arr_size; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		ft_swap_element(arr, i, min);
		printf("Rotaion %d =  ", i);
		print_arr(arr, arr_size);
	}
}

int		main(void)
{
	int arr_size = 8;
	int arr1[] = {90,80,70,30,60,50,20,10};
	int arr2[] = {90,80,70,30,60,50,20,10};

	selection_sort(arr1, arr_size);
	bubble_sort(arr2, arr_size);
}