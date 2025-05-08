#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct {
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT]; // heap �迭 ����
	int heap_size;             // ���� ���� ����� ��� ��
} HeapType;

// �� ���� �Լ�
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// �� �ʱ�ȭ �Լ�
void init(HeapType* h) {
	h->heap_size = 0;
}

// �ִ� ���� ��� ����
void insert_max_heap(HeapType* h, element item) {
	int i = ++(h->heap_size);  // �� ũ�� ���� �� �ش� ��ġ���� ����

	// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ��
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];  // �θ� �ڽ����� ����
		i /= 2;
	}
	h->heap[i] = item;  // �˸��� ��ġ�� item ����
}

// �ִ� ������ ��� ����
element delete_max_heap(HeapType* h) {
	int parent = 1, child = 2; 
	element item = h->heap[1];           // ��Ʈ ��� ����
	element temp = h->heap[h->heap_size--]; // ������ ��带 �ӽ� �����ϰ� �� ũ�� ����

	// �ڽ� ���� ���ϸ鼭 ���ġ
	while (child <= h->heap_size) {
		// �� �ڽ� �� �� ū �ڽ� ����
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
			child++;
		}
		// ���ڸ��� ���� �ݺ� ����
		if (temp.key >= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];  // �ڽ��� �θ�� ����ø�
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;  // ���� ��ġ�� temp ����
	return item;
}

int main(void) {
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }; // ��� 3�� ����
	element e4, e5, e6;
	HeapType* heap;

	heap = create();	// �� ����
	init(heap);			// �� �ʱ�ȭ

	// ��� ����
	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);

	// ��� ���� �� ���
	e4 = delete_max_heap(heap);
	printf("< %d >", e4.key);
	e5 = delete_max_heap(heap);
	printf("< %d >", e5.key);
	e6 = delete_max_heap(heap);
	printf("< %d >\n", e6.key);

	free(heap); // ���� �޸� ����
	return 0;
}
