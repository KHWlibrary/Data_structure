#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct ListNode
{
	element data;
	struct ListNode* link;
}ListNode;

//���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);	//���� �޽��� ���
	exit(1);		//������ �Լ� -> ���α׷� ����
}

//�� �տ� �߰�
ListNode* insert_first(ListNode* head, element value)		//(������, ��)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));		//�����޸𸮿� ListNode �Ҵ�
	p->data = value;		//data�� value�� �ֱ�
	p->link = head;			//�ּҰ� head����
	head = p;
	return head;
}

//����Ʈ ���
void print_list(ListNode* head)
{
	ListNode* p = head;  // ����Ʈ�� ù ��° ��带 ����Ű�� ������
	while (p != NULL)  // ����Ʈ�� ���� ������ �ݺ�
	{
		printf("%d->", p->data);  // ���� ����� �����͸� ���
		p = p->link;  // ���� ��带 ����Ŵ
	}
	printf("NULL\n");  // ����Ʈ�� ���� ��Ÿ���� NULL ���
}

//����Ʈ ����
ListNode* concat_list(ListNode* head1, ListNode* head2)
{
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		ListNode* p;
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;
		return head1;
	}
}
//�׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head1 = NULL;
	ListNode* head2 = NULL;

	head1 = insert_first(head1, 10);
	head1 = insert_first(head1, 15);
	head1 = insert_first(head1, 20);

	print_list(head1);

	head2 = insert_first(head2, 300);
	head2 = insert_first(head2, 140);

	print_list(head2);

	ListNode* total = concat_list(head1, head2);
	print_list(total);
	return 0;
}