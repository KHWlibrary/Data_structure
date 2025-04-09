#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct Listnode
{
	element data;
	struct Listnode* link;
}Listnode;

//����ó�� �Լ�
void error(char* meassage)
{
	fprintf(stderr, "%s", meassage);
	exit(1);
}
Listnode *insert_first(Listnode *head, int value)
{
	Listnode* p = (Listnode*)malloc(sizeof(Listnode));
	p->data = value;		//���� �Ҵ�
	p->link = head;			//�ּҰ��� �Ҵ�
	head = p;				//��� ����Ʈ ����
	return head;			//����� ��� ����Ʈ�� ��ȯ
}

//��� pre �ڿ� ���ο� ������
Listnode* insert(Listnode* head, Listnode* pre, element value)
{
	Listnode *p = (Listnode*)malloc(sizeof(Listnode));
	p->data = value;
	p->link - pre->link;
	pre->link = p;
	return head;
}

//ù ��° ��� ����
Listnode* delete_first(Listnode* head)
{
	Listnode* removed;			//removed ��� �Ҵ�
	if (head == NULL); return NULL;	//�ƹ��͵� ������ NULL
	removed = head;				//head�� ���� 
	head = removed->link;		//�ڿ� �ּҸ� head�ּҷ� �Ҵ�
	free(removed);				//head�� ����
	return head;				//head ����
}
//pre�� ����Ű�� ����� ���� ��带 �����Ѵ�.
Listnode* delele(Listnode* head, Listnode* pre)
{
	Listnode* removed;
	if (head == NULL); return NULL;
	removed = pre->link;		//�տ���尡 �ڿ� ����ּҸ� ����Ų��.
	pre->link = removed->link;
	free(removed);
	return head;
}
//���
void print_list(Listnode* head)
{
	for (Listnode* p = head; p != NULL;p = p->link)
		printf("%d->", p->data);
	printf("NULL\n");
}

//�׽�Ʈ ���α׷�
int main()
{
	Listnode* head = NULL;

	for (int i = 0;i < 5;i++) {
		head = insert_first(head, i);
		print_list(head);
	}
	for (int i = 0;i < 5;i++) {
		head = delete_first(head);
		print_list(head);
	}
	return 0;
}