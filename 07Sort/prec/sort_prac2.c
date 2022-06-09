#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	print_array(int *array, int size)
{
	int i = 0;
	while (i < size)
	{
		printf(" %d ",array[i]);
		i++;
	}
	printf("\n");
}

int	ft_mini_atoi(char *str)
{
	int i = 0;
	int ret = 0;
	while (str[i])
	{
		ret *= 10;
		if ('0' <= str[i] && str[i] <= '9')
			ret += str[i] - '0';
		i++;
	}
	return (ret);
}

void	bubble_sort(int *arr, int arr_len)
{
	int i = 0;
	int j = 0;

	for (i = arr_len - 1; 0 <= i; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (arr[i] <  arr[j])
			{
				int tmp;
				tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp;
			}
		}
		printf("%d 회전 \n", i + 1);
		print_array(arr, arr_len);

	}
}
void	selection_sort(int *arr, int arr_len)
{
	int i, j;
	int min;
	int tmp;
	for (i = 0; i < arr_len - 1; i++)
	{
		min = i;
		for (j = i + 1; j < arr_len; j++)
		{
			if (arr[j] <= arr[min])
				min = j;
		}
		tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
		printf("%d 회전 \n", i + 1);
		print_array(arr, arr_len);
	}
}
static void ft_swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
int		partition(int *arr, int start, int end)
{
	int left = start;
	int right = end;
	int pivot = end;

	while (left < right)
	{
		while ( (arr[left] < arr[pivot]) && (left < right))
			left++;
		while ( (arr[pivot] <= arr[right]) && (left < right))
			right--;
		if (left < right)
			ft_swap(&arr[left], &arr[right]);
	}
	ft_swap(&arr[pivot], &arr[right]);
	print_array(arr, end);
	return (right);
}

void	quick_sort(int *arr, int start, int end)
{
	int pivot = 0;
	if (start < end)
	{
		pivot = partition(arr, start, end);
		quick_sort(arr, start, pivot - 1);
		quick_sort(arr, pivot + 1, end);
	}
}

int	main(int argc, char **argv)
{
	int *arr;
	int *arr2;
	int *arr3;
	int i;
	int arr_len = argc - 1;

	arr = calloc(arr_len, sizeof(int));
	arr2 = calloc(arr_len, sizeof(int));
	arr3 = calloc(arr_len, sizeof(int));
	if (argc <= 2)
	{
		printf("Input at least 3 Arguments. \n");
		return (0);
	}

	for (i = 1; i < argc; i++)
		arr[i - 1] = ft_mini_atoi(argv[i]);
	memcpy(arr2, arr, sizeof(int) * arr_len);
	memcpy(arr3, arr, sizeof(int) * arr_len);

	printf("ORIGINAL\n");
	print_array(arr, arr_len);

	printf("\nBUBBLE\n");
	bubble_sort(arr, arr_len);
	print_array(arr, arr_len);

	printf("\nSELECTION\n");
	selection_sort(arr2, arr_len);
	print_array(arr2, arr_len);

	printf("\nQUICK\n");
	quick_sort(arr3, 0, arr_len - 1);
	print_array(arr3, arr_len);
	free(arr);
	free(arr2);
	free(arr3);
	arr = NULL;
	return (0);
}