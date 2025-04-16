#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct ListNode		//��� Ÿ��
{
	element data;			
	struct ListNode* link;	//��� ���� �Ű�ü
}ListNode;

//����Ʈ �׸� ���
void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) return;	//head���� ������ �׳� ����
	p = head->link;				//
	do {						//
		printf("%d->", p->data);//while�� �ϱ����� �ϴ� ���� 1ȸ ���
		p = p->link;			//
	} while (p != head);		//
	printf("%d", p->data);		//������ ��� ���
}

//�� �տ� ����
ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode *)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		// ����Ʈ�� ����ִ� ���: �� ��带 �ڱ� �ڽ����� �����ϰ� head�� ����
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)�� ��尡 ���� ù ��° ��带 ����Ű���� ���� 
		head->link = node;			// (2)������ ��尡 ���ο� ��带 ����Ű���� ����
	}
	return head;	//����� ��� ������ ��ȯ
}

//�� �� ����
ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));		//node ���ο� ���
	node->data = data;
	if (head == NULL) {
		// ����Ʈ�� ����ִ� ���: �� ��带 �ڱ� �ڽ����� �����ϰ� head�� ����
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link; //(1) �� ��尡 ù ��° ��带 ����Ű���� ����
		head->link = node;		//(2)���� ������ ��尡 ���ο� ��带 ����Ŵ
		head = node;			//(3)head�� ������ ����
	}
	return head;	//���浵�� ��� ������ ��ȯ
}
//���� ���� ����Ʈ �׽�Ʈ ���α׷�

int main(void)
{
	ListNode* head = NULL;

	//list 10->20->30->40
	head = insert_first(head, 20);
	head = insert_last(head, 30);
	head = insert_last(head, 40);
	head = insert_first(head, 10);

	print_list(head);
	return 0;
}