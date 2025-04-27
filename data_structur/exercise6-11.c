#define _CRT_SECURE_NO_WARNINGS    // scanf ��� �� ���� ��� ����
#define MAX_LIST_SIZE 100          // ����Ʈ �ִ� ũ�� ����
#include <stdio.h>
#include <stdlib.h>

// ���(element) �ڷ��� ���� (���⼭�� int)
typedef int element;

// �迭 ����Ʈ Ÿ�� ����
typedef struct
{
	element array[MAX_LIST_SIZE]; // �����͸� ������ �迭
	int size;                     // ���� ����Ʈ�� ����� ��� ��
} ArrayListType;

// ���� �߻� �� �޽����� ����ϰ� ���α׷� ����
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ����Ʈ �ʱ�ȭ: ��� ���� 0���� ����
void init(ArrayListType* L)
{
	L->size = 0;
}

// ����Ʈ�� ���� á���� Ȯ�� (1: ������, 0: ��������)
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}

// Ư�� ��ġ(pos)�� ��Ҹ� ��ȯ
element get_entry(ArrayListType* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");  // ������ ��� ��� ���� ó��
	return L->array[pos];
}

// ����Ʈ�� ��� ��Ҹ� ���
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n"); // �� ǥ��
}

// ����Ʈ�� �������� �� ��� �߰�
void insert_last(ArrayListType* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) {
		error("����Ʈ �����÷ο�");  // �ִ� ũ�� �ʰ� �� ����
	}
	L->array[L->size++] = item;  // ��� ���� �� ũ�� ����
}

// ������ ��ġ(pos)�� ��� ���� (�� ��ҵ� �� ĭ�� �ڷ� �̵�)
void insert(ArrayListType* L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		// �ڿ������� �� ĭ�� �̵�
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;  // ������ ��ġ�� �� �� ����
		L->size++;             // ũ�� ����
	}
}

// ������ ��ġ(pos)�� ��� ���� �� �� ���� ��ȯ
element delete(ArrayListType* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
		error("��ġ����");  // �߸��� ��ġ ���� �� ����
	item = L->array[pos];    // ������ �� ����
	// ���� ��ҵ��� �� ĭ�� ������ �̵�
	for (int i = pos; i < (L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;               // ũ�� ����
	return item;             // ������ �� ��ȯ
}

// ���� �Լ�
int main(void)
{
	ArrayListType list;      // �迭 ����Ʈ ���� ����
	init(&list);             // ����Ʈ �ʱ�ȭ

	int count, data;
	int i;
	int sum = 0;             // �������� �� ����� ����

	printf("����� ����: ");
	scanf("%d", &count);     // �Է��� ������ ���� �Է�

	// ����ڰ� �Է��� ������ŭ �����͸� �Է¹ް� ����Ʈ�� �߰�
	for (i = 0; i < count; i++)
	{
		printf("��� #%d ������ : ", i + 1);
		scanf("%d", &data);
		insert_last(&list, data);  // ����Ʈ�� ������ �߰�
	}

	// ����Ʈ�� ����� ��� �������� �� ���
	for (i = 0; i < list.size; i++) {
		sum += list.array[i];
	}

	// �հ� ���
	printf("���� ����Ʈ�� ������ �� = %d\n", sum);

	return 0;
}
