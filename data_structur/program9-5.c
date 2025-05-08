//LPT 프로그램
#include<stdio.h>
#define MAX_ELEMENT 200

typedef struct {
	int id;
	int avail;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

//히프 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

//히프 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}

//히프를 삽입하는 함수
void insert_min_heap(HeapType* h, element item)
{
	int i = ++(h->heap_size);
}