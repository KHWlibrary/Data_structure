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
	pre->link = pr
}