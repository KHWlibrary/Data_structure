//LPT ���α׷�
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

//���� ���� �Լ�
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

//���� �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}

//������ �����ϴ� �Լ�
void insert_min_heap(HeapType* h, element item)
{
	int i = ++(h->heap_size);
}