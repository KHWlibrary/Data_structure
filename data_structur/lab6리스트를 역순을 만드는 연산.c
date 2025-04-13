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