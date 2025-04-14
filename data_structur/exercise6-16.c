//�ܼ� ���� ����Ʈ�� ��� �����Ͱ� �־��� ���� �� ù ��° ��忡������ �ϳ��� �ǳʼ� �ִ�
//��带 ���� �����ϴ� �Լ��� �ۼ��϶�. �� Ȧ����° �ִ� ������ ���� �����ȴ�.
#include<stdio.h>
#include<stdlib.h>

typedef struct LinkNode
{
	int data;
	struct LinkNode* link;
}LinkNode;

//����߰�

LinkNode *insert_node(LinkNode* head, int value)
{
	LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
	p->data = value;
	p->link = head;
	head = p;

	return head;
}
//Ȧ����° ��� ����
LinkNode* delete_odd(LinkNode* head)
{
	if (head == NULL || head->link == NULL) {
		return head;	//ù ��° ��峪 �� ��° ��尡 ������ ������ ��尡 ����
	}
	LinkNode* temp = head;
	LinkNode* prev = NULL;

	//ù ��° ��� �ǳ� �ٰ� �� ��° ������
	temp = temp->link;
	head = temp;	//�� ��° ��带 head�� ����

	//Ȧ����° ��� ����
	while (temp != NULL && temp->link != NULL)
	{
		prev = temp;
		temp = temp->link->link;	//��ĭ �ǳ� �ٱ�
		prev->link = temp;			//������尡 ���� ��带 ����Ű����	
	}
	return head;
}
//���
void print_list(LinkNode* head) {
	LinkNode* temp = head;
	while (temp != NULL) {
		printf("%d -> ", temp->data);
		temp = temp->link;
	}
	printf("NULL\n");
}

// �޸� free �Լ�
void free_list(LinkNode* head) {
	LinkNode* temp;
	while (head != NULL) {
		temp = head;
		head = head->link;
		free(temp);
	}
}

int main(void)
{
	LinkNode* head = NULL;
	head = insert_node(head, 1);
	head = insert_node(head, 2);
	head = insert_node(head, 3);
	head = insert_node(head, 4);
	head = insert_node(head, 5);
	head = insert_node(head, 6);
	head = insert_node(head, 7);
	head = insert_node(head, 8);

	printf("������ ����Ʈ : \n");
	print_list(head);

	head = delete_odd(head);

	printf("������ ����Ʈ : \n");
	print_list(head);

	//�޸� ����
	free_list(head);

	return 0;
}