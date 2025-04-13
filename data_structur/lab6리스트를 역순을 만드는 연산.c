#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct ListNode
{
	element data;
	struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}
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
//����Ʈ �������� �����
ListNode* reverse(ListNode* head)
{
	//��ȸ �����ͷ� p, q, r�� ���
	ListNode* p, * q, * r;

	p = head;		//p�� �������� ���� ����Ʈ
	q = NULL;		//q�� ������ ���� ���
	while (p != NULL) {
		r = q;	//r�� ������ �� ����Ʈ.
				//r�� q,q�� p�� ���ʷ� ���󰣴�.
		q = p;
		p = p->link;
		q->link = r;	//q�� ��ũ ������ �ٲ۴�
	}
	return q;
}

//�׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head1 = NULL;
	ListNode* head2 = NULL;

	head1 = insert_first(head1, 10);
	head1 = insert_first(head1, 20);
	head1 = insert_first(head1, 30);
	print_list(head1);

	head2 = reverse(head1);
	print_list(head2);
	return 0;
}