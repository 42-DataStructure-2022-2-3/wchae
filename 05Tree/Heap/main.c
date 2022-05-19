#include "heap.h"

int main()
{
	Heap *pMinHeap;
	Heap *pMaxHeap;
	HeapNode element;

	// pMaxHeap
/*
	pMaxHeap = createHeap(7);
	element.data = 20;
	insertMaxHeapNode(pMaxHeap, element);
	element.data = 6;
	insertMaxHeapNode(pMaxHeap, element);
	element.data = 12;
	insertMaxHeapNode(pMaxHeap, element);
	element.data = 2;
	insertMaxHeapNode(pMaxHeap, element);
	element.data = 4;
	insertMaxHeapNode(pMaxHeap, element);
	element.data = 10;
	insertMaxHeapNode(pMaxHeap, element);
	element.data = 80;
	insertMaxHeapNode(pMaxHeap, element);

	printf("Original pMaxHeap => ");
	displayHeap(pMaxHeap);
	
	// deleteMaxHeapNode(pMaxHeap);
	// printf("After deleteMaxHeapNode pMaxHeap => ");
	// displayHeap(pMaxHeap);
	displayHeapByLevel(pMaxHeap);
*/
	// pMinHeap

	pMinHeap = createHeap(11);
	element.data = 2;
	insertMinHeapNode(pMinHeap, element);
	element.data = 8;
	insertMinHeapNode(pMinHeap, element);
	element.data = 4;
	insertMinHeapNode(pMinHeap, element);
	element.data = 12;
	insertMinHeapNode(pMinHeap, element);
	element.data = 10;
	insertMinHeapNode(pMinHeap, element);
	element.data = 7;
	insertMinHeapNode(pMinHeap, element);
	element.data = 5;
	insertMinHeapNode(pMinHeap, element);
	element.data = 20;
	insertMinHeapNode(pMinHeap, element);
	element.data = 1;
	insertMinHeapNode(pMinHeap, element);

	printf("Original pMinHeap => ");
	displayHeap(pMinHeap);

	deleteMinHeapNode(pMinHeap);
	printf("After deleteMinHeapNode pMinHeap => ");
	displayHeap(pMinHeap);

	// deleteHeap(pMaxHeap);
	deleteHeap(pMinHeap);
	displayHeap(pMinHeap);
	
	return (0);
}