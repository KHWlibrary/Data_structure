#include<stdio.h>
#include<stdlib.h>

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

//�켱���� ť�� ������ �̿��� ����
//�ִ� ���� �̿��� �� ���� �Լ�
void heap_sort(element a[], int n)
{
	int i;  // �ݺ����� ���� ����
	HeapType* h;  // �� �ڷᱸ���� ����Ű�� ������ ����

	h = create();  // ���� �������� �����Ͽ� ������ h�� ����

	init(h);  // ���� �ʱ�ȭ�Ͽ� heap_size�� 0���� ����

	// �־��� �迭�� ��� ��Ҹ� ���� ���� (�ִ� �� ����)
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);  // ��Ҹ� �ִ� ���� ����
	}

	// ������ ���� ū ��Ҹ� ������ �迭�� �ڿ������� ���� (���� ����)
	for (i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(h);  // ���� ��Ʈ ���(�ִ�)�� ���� �迭�� ����
	}

	free(h);  // �������� ������ �� �޸𸮸� ����
}

#define SIZE 8  // ������ �迭�� ũ�⸦ 8�� ����

// main �Լ�: ���α׷��� ������
int main(void)
{
	// ������ ��ҵ��� ����ü �迭�� �ʱ�ȭ
	element list[SIZE] = { {23}, {12}, {35}, {65}, {32}, {43}, {32}, {76} };

	heap_sort(list, SIZE);  // �� ���� �Լ� ȣ��

	// ���ĵ� ����� ���
	for (int i = 0; i < SIZE; i++) {
		printf(" %d ", list[i].key);  // �� ����� key ���� ���
	}

	printf("\n");  // ��� �� �� �ٲ�
	return 0;  // ���α׷� ����
}
