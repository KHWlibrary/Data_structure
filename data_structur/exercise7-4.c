#include<stdio.h>
#include<stdlib.h>

typedef int element;	//element�� int������ ����� �� �ְ���
typedef struct ListNode	//���Ḯ��Ʈ ��� ����ü ����
{
	element data;	//��忡 data�� ����
	struct ListNode* link;	//���� ��带 ����Ű�� ������
}ListNode;	//����ü �̸�

//����Ʈ�� ��� �׸��� ����ϴ� �׸�
void print_list(ListNode* head)
{
	if (head == NULL) return;	//����Ʈ�� ����ִٸ� ������� �ʰ� ����
	ListNode* p = head;		//���� ��带 ����Ű�� ������, head���� ����
	do {
		printf("%d->", p->data);	//���� ��� ������ ���
		p = p->link;	//���� ���� �̵�
	} while (p != head);	//�� ���� �������� �ݺ�
	printf("(head)\n");	//��ȯ �� ǥ��
}
//����Ʈ �� �տ� �� ��带 �����ϴ� �Լ�
ListNode* insert_first(ListNode* head, element data)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	if (newnode == NULL)
	{
		fprintf(stderr,"�޸� �Ҵ� ����\n");
		exit(1);
	}
	newnode->data = data;  //�� ��忡 �����Ͱ� ����

	if (head == NULL)
	{	//ù ����� ��� �ڱ� �ڽ��� ����Ŵ
		newnode->link = newnode;	//�ڱ� �ڽ��� ����Ű�� ��������Ʈ
		head = node;	//head�� �� ��带 ����Ű����
	}
	else
	{
		newnode->link = head->link;		//�� ��尡 ���� ù ��° ��带 ����Ŵ
		head->link = newnode;		//���� ��尡 �� ��带 ����Ŵ
	}
	return head;
}

//get_size�� �̿��� ������ ������ ��ȯ�ϴ� �Լ��� ������
int get_size(ListNode* head) {
	if (head == NULL) return 0;	//����Ʈ�� ����ִٸ� 0��ȯ
	int count = 0;
	ListNode* p = head;
	do {
		count++;		//1�� ��ȸ �Ҷ����� count 1�� ���� 
		p = p->link;	//�������� �̵�
	} while (p != head);	//�� ���� �������� �ݺ�
	return count;
}

// ���� ���� ����Ʈ�� ��� ��带 �����ϴ� �Լ�
void free_list(ListNode* head) {
	if (head == NULL) return;  // ����Ʈ�� ��� ������ �ٷ� ����

	ListNode* p = head->link;  // �� ��° ������ ����
	ListNode* temp;

	while (p != head) {
		temp = p;          // ���� ��带 �ӽ÷� ����
		p = p->link;       // ���� ���� �̵�
		free(temp);        // ���� ��� �޸� ����
	}

	free(head);  // ���������� head ��� ����
}

//���α׷� �����ϴ� ���� �Լ�
int main(void)
{
	ListNode* head = NULL;	//head������ NULL�� �ʱ�ȭ
	int count = 0;//count �� �ʱ�ȭ

	//��� �� �տ� ����
	head = insert_first(head, 20);	//20����
	head = insert_first(head, 10);	//10����
	head = insert_first(head, 230);	//230����
	head = insert_first(head, 5);	//5����
	head = insert_first(head, 123);	//123����

	//����Ʈ ���
	printf("���� ���� ����Ʈ ���:\n");
	print_list(head);

	//������ ���� Ȯ��
	int size = get_size(head);
	printf("������ ���� : %d\n", size);

	free_list(head);	//��� �޸� ����
	return 0;	//���α׷� ����
}