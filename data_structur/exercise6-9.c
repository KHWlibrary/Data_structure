//�ܼ� ���Ḯ��Ʈ
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LIST_SIZE 100    // ����Ʈ�� �ִ� ũ�� ����
#include <stdio.h>
#include <stdlib.h>

typedef int element;         // ����Ʈ�� ����� �׸� Ÿ�� ����

// �迭 ����Ʈ ����ü ����
typedef struct
{
	element array[MAX_LIST_SIZE];  // �����͸� ������ �迭
	int size;                      // ���� ����Ʈ�� ����� �׸� ��
} ArrayListType;

// ���� �߻� �� �޽����� ����ϰ� ���α׷� ����
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ����Ʈ �ʱ�ȭ �Լ�
void init(ArrayListType* L)
{
	L->size = 0;  // �׸� ������ 0���� ����
}

// ����Ʈ�� ���� á���� Ȯ��
// ���� �� ������ 1, �ƴϸ� 0 ��ȯ
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}

// ����Ʈ���� �־��� ��ġ(pos)�� �׸��� ��ȯ
element get_entry(ArrayListType* L, element pos)
{
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	return L->array[pos];
}

// ����Ʈ�� ��� �׸��� ���
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("NULL\n");  // ����Ʈ �� ǥ��
}

// ����Ʈ�� �������� �׸��� �߰�
void insert_last(ArrayListType* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) {
		error("����Ʈ �����÷ο�");  // �ִ� ũ�⸦ �ʰ��� ��� ����
	}
	L->array[L->size++] = item;  // �������� �׸� �߰� �� size ����
}

// ������ ��ġ(pos)�� �׸�(item)�� ����
// ���� ��ġ ������ �׸���� �� ĭ�� �ڷ� �̵�
void insert(ArrayListType* L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)  // �ڿ������� �� ĭ�� �б�
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;  // ������ ��ġ�� �� �׸� ����
		L->size++;             // �׸� ���� ����
	}
}

// ������ ��ġ(pos)�� �׸��� �����ϰ� �� ���� ��ȯ
element delete(ArrayListType* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
		error("��ġ ����");  // �߸��� ��ġ�� �����ϸ� ���� ó��

	item = L->array[pos];  // ������ �׸� ����
	for (int i = pos; i < (L->size - 1); i++)  // �� �׸���� ������ �̵�
		L->array[i] = L->array[i + 1];

	L->size--;  // �׸� ���� ����
	return item;  // ������ �׸� ��ȯ
}

// ���� �Լ� - ����Ʈ ���� �� ����� �Է� �׽�Ʈ
int main(void)
{
	ArrayListType list;  // ����Ʈ ���� ����
	init(&list);         // ����Ʈ �ʱ�ȭ

	int count, data;
	int i;

	printf("����� ����: ");
	scanf("%d", &count);  // �߰��� ��� �� �Է�

	// ����ڰ� �Է��� ��ŭ �����͸� ����Ʈ�� �߰�
	for (i = 0; i < count; i++)
	{
		printf("��� #%d ������ : ", i + 1);
		scanf("%d", &data);
		insert_last(&list, data);  // ����Ʈ ���� ������ �߰�
	}

	// ���� ����Ʈ ���
	printf("������ �迭����Ʈ: ");
	print_list(&list);

	return 0;
}
