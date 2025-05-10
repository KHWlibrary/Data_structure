#define _CRT_NO_SECURE_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char list[30];	//글자 수 29자리까지
	int priority;	//우선순위
}element;

typedef struct {
	element heap[50];//힙 크기 
	int heap_size;
}Heap;

//힙 생성 함수
Heap* create()
{
	return (Heap*)malloc(sizeof(Heap));
}

//힙 초기화 함수
void init(Heap* h)
{
	h->heap_size = 0;
}

//힙 삽입함수
void insert_heap(Heap* h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.priority < h->heap[i / 2].priority)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_heap(Heap* h)
{
	int parent, child;
	element item, temp;	//int와 element차이는?
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		//
		if ((child <= h->heap_size) && (h->heap[child].priority > h->heap[child + 1].priority))
			child++;
		if (temp.priority <= h->heap[child].priority) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void help()
{
	printf("삽입(i), 삭제(d), 종료(q): ");
}

int main(void)
{
	Heap* heap;
	heap = create();
	init(heap);	//초기화
	element e;

	char command = {};
	while (command != 'q') {
		help();
		command = getchar();
		getchar();
		switch (command)
		{
		case 'i':
			printf("해야할 일: ");
			gets_s(e.list);
			printf("우선순위: ");
			scanf("%d", &e.priority);
			insert_heap(heap, e);
			break;
		case 'd':
			e = delete_heap(heap);
			printf("제일 우선순위가 높은 일은 %s", e.list);
			break;
		}
	}
	return 0;
}