//��尪 Ž�� �˰���

#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

//���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//�� �տ� �߰�
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));		//ListNode���� �Ҵ�
	p->data = value;	//�� ����
	p->link = head;		//��� ������ �� ����
	head = p;			//��� ������ ����
	return head;
}

//����Ʈ 
void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);			//"%d"�� ������ ���
	printf("NULL \n");
}

//Ž��
ListNode* search_list(ListNode* head, element x)
{
	ListNode* p = head;

	while (p != NULL) {
		if (p->data == x) return p;		//���� p�� ��ġ�ϴ� ���̸� p->data ������ ����
		p = p->link;						//�ƴϸ� �������� �Ѿ��
	}
	return NULL; // Ž�� ����
}


//���� �Լ�
int main(void)
{
	ListNode* head = NULL;

	head = insert_first(head, 30);
	print_list(head);
	head = insert_first(head, 20);
	print_list(head);
	head = insert_first(head, 10);
	print_list(head);

	if (search_list(head, 20) != NULL)
		printf("����Ʈ���� 20�� ã�ҽ��ϴ�.\n");
	else
		printf("����Ʈ���� 20�� ã�� �� �߽��ϴ�. \n");
	return 0;
}