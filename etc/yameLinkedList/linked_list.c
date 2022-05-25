#include <stdio.h>

const int MAX = 1000005;
int data[MAX], prev[MAX], next[MAX];
int unused = 1;

void insert(int addr, int num){
	data[unused] = num;
	prev[unused] = addr;
	next[unused] = next[addr];
	if (next[addr] != -1)
		prev[next[addr]] = unused;
	next[addr] = unused;
	unused++;
}

void erase(int addr){
	next[prev[addr]] = next[addr];
	next[addr] = -1;
	prev[addr] = -1;
	data[addr] = -1;
}

void traverse(){
	int cur = next[0];
	while(cur != -1){
		printf("%d ", data[cur]);
		cur = next[cur];
	}
  printf("\n\n");
}

void insert_test(){
	printf("========inserttest===========\n");
	insert(0, 10); // 10(address=1)
  traverse();
  insert(0, 30); // 30(address=2) 10
  traverse();
  insert(2, 40); // 30 40(address=3) 10
  traverse();
  insert(1, 20); // 30 40 10 20(address=4)
  traverse();
  insert(4, 70); // 30 40 10 20 70(address=5)
  traverse();
}

void erase_test(){
  printf("****** erase_test *****\n");
  erase(1); // 30 40 20 70
  traverse();
  erase(2); // 40 20 70
  traverse();
  erase(4); // 40 70
  traverse();
  erase(5); // 40
  traverse();
}

int main(void) {
	for(int i = 0; i < MAX; i++)
	{
		prev[i] = -1;
		next[i] = -1;
	}
  insert_test();
  erase_test();
}
