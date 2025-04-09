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
void error(char* message)
{
	fprintf(stderr, "%s\n", massage);
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
