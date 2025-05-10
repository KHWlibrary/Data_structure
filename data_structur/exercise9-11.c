#define _CRT_NO_SECURE_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char list[30];	//���� �� 29�ڸ�����
	int priority;	//�켱����
}element;

typedef struct {
	element heap[50];//�� ũ�� 
	int heap_size;
}Heap;

//�� ���� �Լ�
Heap* create()
{
	return (Heap*)malloc(sizeof(Heap));
}

//�� �ʱ�ȭ �Լ�
void init(Heap* h)
{
	h->heap_size = 0;
}

//�� �����Լ�
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
	element item, temp;	//int�� element���̴�?
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
	printf("����(i), ����(d), ����(q): ");
}

int main(void)
{
	Heap* heap;
	heap = create();
	init(heap);	//�ʱ�ȭ
	element e;

	char command = {};
	while (command != 'q') {
		help();
		command = getchar();
		getchar();
		switch (command)
		{
		case 'i':
			printf("�ؾ��� ��: ");
			gets_s(e.list);
			printf("�켱����: ");
			scanf("%d", &e.priority);
			insert_heap(heap, e);
			break;
		case 'd':
			e = delete_heap(heap);
			printf("���� �켱������ ���� ���� %s", e.list);
			break;
		}
	}
	return 0;
}