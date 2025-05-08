#include<stdio.h>      // ǥ�� ����� �Լ� ����� ���� ���
#include<stdlib.h>     // malloc, free ���� ���� �޸� �Լ� ����� ���� ���

#define MAX_ELEMENT 200   // ������ ������ �� �ִ� �ִ� ��� �� ����

// ���� ������ ��� ����ü ����
typedef struct {
	int key;   // �켱����(Ű ��)
} element;

// ���� ����ü ����
typedef struct {
	element heap[MAX_ELEMENT];  // ��ҵ��� ������ �迭
	int heap_size;              // ���� ������ ����� ����� ����
} HeapType;

// ������ �����ϴ� �Լ� (���� �޸� �Ҵ�)
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));  // HeapType ũ�⸸ŭ �޸� �Ҵ� �� ������ ��ȯ
}

// ������ �ʱ�ȭ�ϴ� �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;   // ���� ũ�⸦ 0���� �ʱ�ȭ
}

// �ִ� ������ ��Ҹ� �����ϴ� �Լ�
void insert_max_heap(HeapType* h, element item)
{
	int i = ++(h->heap_size);  // ���� ũ�⸦ 1 ������Ű��, �� �ε����� i�� ����

	// ������ ��ġ�� ã�� ���� Ʈ���� ���� �ö󰡸� �θ� ���� ��
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];  // �θ� ��带 �ڽ� ��ġ�� ��������
		i /= 2;                       // i�� �θ� �ε����� �̵�
	}
	h->heap[i] = item;  // ������ ��ġ�� ������ item�� ����
}

// �ִ� �������� ��Ʈ ��Ҹ� �����ϴ� �Լ�
element delete_max_heap(HeapType* h) {
	int parent = 1;               // �θ� ��� �ε��� ���� ��ġ
	int child = 2;                // �ڽ� ��� �ε��� ���� ��ġ
	element item = h->heap[1];    // ��Ʈ ��带 item�� ���� (������ ���)
	element temp = h->heap[h->heap_size--];  // ������ ��带 temp�� ���� �� ���� ũ�� ����

	// ���� �Ӽ��� �����ϱ� ���� �Ʒ��� �������� ���ġ
	while (child <= h->heap_size) {
		// ���� �ڽİ� ������ �ڽ� �� �� ū ���� ���� �ڽ� ��带 ����
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
			child++;  // ������ �ڽ��� �� ũ�� ������ �ڽ� ����
		}
		// temp�� �ڽĺ��� ũ�ų� ������ �ڸ��� ã�� �� �� ���� ����
		if (temp.key >= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];  // �� ū �ڽ� ��带 �θ� ��ġ�� ����ø�
		parent = child;                    // �� �ܰ� �Ʒ��� �̵�
		child *= 2;                        // �ڽ� ��� �ε����� �ٽ� ����
	}
	h->heap[parent] = temp;  // ������ ��ġ�� temp �����Ͽ� ���� �Ӽ� ����
	return item;             // ������ ��Ʈ ��� ��ȯ
}

// ���α׷� ���� ������
int main(void)
{
	// ������ ��� 3�� ����
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element e4, e5, e6;   // ���� �� ��ȯ�� ��� �����
	HeapType* heap;       // ���� ����ü ������ ����

	heap = create();	  // ���� ���� ����
	init(heap);			  // ���� �ʱ�ȭ

	// ��� ���� (�ִ� ���� ����)
	insert_max_heap(heap, e1);  // 10 ����
	insert_max_heap(heap, e2);  // 5 ����
	insert_max_heap(heap, e3);  // 30 ����

	// ��� ���� (�ִ� ������ ���ʷ� ����)
	e4 = delete_max_heap(heap);    // ���� ū ��(30) ����
	printf("< %d >", e4.key);      // ���: < 30 >
	e5 = delete_max_heap(heap);    // ���� ū ��(10) ����
	printf("< %d >", e5.key);      // ���: < 10 >
	e6 = delete_max_heap(heap);    // ���� ��(5) ����
	printf("< %d >\n", e6.key);    // ���: < 5 >

	free(heap);  // ���� �޸� ����
	return 0;    // ���α׷� ����
}
