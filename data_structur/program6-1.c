#define MAX_LIST_SIZE 100   // ����Ʈ�� �ִ� ũ�� ���� (100���� ��ұ��� ���� ����)

#include<stdio.h>           // ǥ�� ����� �Լ� ����
#include<stdlib.h>          // ǥ�� ���̺귯�� �Լ� ���� (exit �� ���)

// element�� int�� �����Ͽ� �ڵ� ������ ���
typedef int element;

// �迭 ��� ����Ʈ ����ü ����
typedef struct {
	element array[MAX_LIST_SIZE];  // �����͸� ������ �迭
	int size;                      // ���� ����� �������� ����
} ArrayListType;

// ���� �޽��� ��� �� ���α׷� �����ϴ� �Լ�
void error(char* message) {
	fprintf(stderr, "%s\n", message);  // ���� �޽����� ǥ�� ������ ���
	exit(1);                           // ���α׷� ������ ����
}

// ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void init(ArrayListType* L) {
	L->size = 0;  // ����Ʈ ũ�⸦ 0���� ����
}

// ����Ʈ�� ���� á���� Ȯ�� (���� á���� 1, �ƴϸ� 0 ��ȯ)
int is_full(ArrayListType* L) {
	return L->size == MAX_LIST_SIZE;
}

// ����Ʈ���� Ư�� ��ġ�� ���� ��ȯ�ϴ� �Լ�
element get_entry(ArrayListType* L, int pos) {
	if (pos < 0 || pos >= L->size)     // ��ȿ���� ���� ��ġ�� ���
		error("��ġ ����");             // ���� �޽��� ���
	return L->array[pos];              // �ش� ��ġ�� �� ��ȯ
}

// ����Ʈ�� ��� ��Ҹ� ����ϴ� �Լ�
void print_list(ArrayListType* L) {
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);  // �� ��Ҹ� "����->" �������� ���
	printf("\n");
}

// ����Ʈ�� �� �������� �׸��� �߰��ϴ� �Լ�
void insert_last(ArrayListType* L, element item) {
	if (L->size >= MAX_LIST_SIZE) {       // ����Ʈ�� ���� á�ٸ�
		error("����Ʈ �����÷ο�");         // ���� ó��
	}
	L->array[L->size++] = item;           // ������ ��ġ�� �� ���� �� size ����
}

// ����Ʈ�� Ư�� ��ġ�� �׸��� �����ϴ� �Լ�
void insert(ArrayListType* L, int pos, element item) {
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {  // ��ȿ�� ��ġ���� Ȯ��
		for (int i = (L->size - 1); i >= pos; i--)        // �ڿ������� �� ĭ�� �̵�
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;     // ������ ��ġ�� �� �׸� ����
		L->size++;                // ũ�� ����
	}
}

// ����Ʈ�� Ư�� ��ġ�� �׸��� �����ϴ� �Լ�
element delete(ArrayListType* L, int pos) {
	element item;

	if (pos < 0 || pos >= L->size)    // ��ȿ���� ���� ��ġ�� ���
		error("��ġ����");             // ���� ó��

	item = L->array[pos];             // ������ �׸� ����
	for (int i = pos; i < (L->size - 1); i++)  // �� �׸���� �� ĭ�� ������ �̵�
		L->array[i] = L->array[i + 1];
	L->size--;                        // ũ�� ����
	return item;                      // ������ �׸� ��ȯ
}

// ���� �Լ�: ����Ʈ ��� ����
int main(void) {
	ArrayListType list;              // ����Ʈ ���� ����

	init(&list);                     // ����Ʈ �ʱ�ȭ

	insert(&list, 0, 10); print_list(&list);  // 0�� ��ġ�� 10 ���� �� [10]
	insert(&list, 0, 20); print_list(&list);  // 0�� ��ġ�� 20 ���� �� [20, 10]
	insert(&list, 0, 30); print_list(&list);  // 0�� ��ġ�� 30 ���� �� [30, 20, 10]
	insert(&list, 0, 40); print_list(&list);  // 0�� ��ġ�� 40 ���� �� [40, 30, 20, 10]

	insert_last(&list, 50); print_list(&list);  // ����Ʈ �� ���� 50 �߰� �� [40, 30, 20, 10, 50]

	return 0;  // ���α׷� ����
}
