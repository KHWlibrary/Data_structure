#define _CRT_SECURE_NO_WARNINGS
#define MAX_LIST_SIZE 100	//����Ʈ�� �ִ�ũ��
#include<stdio.h>
#include<stdlib.h>

typedef int element;		//�׸��� ����
typedef struct 
{
	element array[MAX_LIST_SIZE];	//�迭 ����
	int size;
}ArrayListType;

//���� ó�� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//����Ʈ �ʱ�ȭ �Լ�
void init(ArrayListType* L)
{
	L->size = 0;
}
//����Ʈ�� ���� �� ������ 1�� ��ȯ
//�׷��� ������ 0�� ��ȯ
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	return L->array[pos];
}

//����Ʈ ���
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0;i < L->size;i++)
		printf("%d->", L->array[i]);
	printf("\n");
}
//�׸� �߰� ����
void insert_last(ArrayListType* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) {
		error("����Ʈ �����÷ο�");
	}
	L->array[L->size++] = item;
}
//�׸� �߰��Ǿ� ������ �ִ� �׸�� �ϳ��� �̵�
void insert(ArrayListType* L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size++;
	}
}
//�׸� ���� ����
element delete(ArrayListType* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
		error("��ġ����");
	item = L->array[pos];
	for (int i = pos; i < (L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;
	return item;
}

int main(void)
{
	ArrayListType list;
	init(&list);
	
	int count, data;
	int i;

	printf("����� ����: ");
	scanf("%d", &count);
	for (i = 0; i < count; i++)
	{
		printf("��� #%d ������ : ", i+1);
		scanf("%d", &data);
		insert_last(&list, data);
	}
	printf("������ ���Ḯ��Ʈ");
	print_list(&list);

	return 0;
}