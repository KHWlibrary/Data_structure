#include<stdio.h>              // ǥ�� ����� �Լ� ���
#include<stdlib.h>             // malloc, free �� ���� �޸� ���� �Լ� ���

// ���� ����Ʈ ��� ����ü ����
typedef struct LinkNode
{
	int data;                 // ��忡 ����� ������
	struct LinkNode* link;   // ���� ��带 ����Ű�� ������
} LinkNode;

// ���� ����Ʈ�� ��带 �տ������� �߰��ϴ� �Լ�
LinkNode* insert_node(LinkNode* head, int value)
{
	LinkNode* newnode = (LinkNode*)malloc(sizeof(LinkNode));  // �� ��� ���� �Ҵ�
	newnode->data = value;                                    // ������ �� ����
	newnode->link = head;                                     // �� ��尡 ���� head�� ����Ű���� ����
	head = p;                                           // �� ��带 head�� ����
	return head;                                        // ����� head ��ȯ
}

// Ȧ�� ��° ��带 �����ϴ� �Լ�
LinkNode* delete_odd(LinkNode* head)
{
	// ��尡 ���ų� �ϳ��� ���� ��� ������ ��� ����
	if (head == NULL || head->link == NULL) {
		return head;
	}

	LinkNode* temp = head;       // ��ȸ ������ �ʱ�ȭ
	LinkNode* prev = NULL;       // ���� ��带 ������ ������

	temp = temp->link;           // �� ��° ������ ���� (ù ��° ���� �ǳʶ�)
	head = temp;                 // �� ��° ��带 ���ο� head�� ����

	// ���� ¦�� ��ġ ��常 �����ϸ鼭 Ȧ�� ��ġ ���� �ǳʶ�
	while (temp != NULL && temp->link != NULL)
	{
		prev = temp;             // ���� ��带 prev�� ����
		temp = temp->link->link; // �� ĭ�� �ǳʶ� (Ȧ�� ��� ��ŵ)
		prev->link = temp;       // prev ����� link�� temp�� �����Ͽ� �߰� ��� ���� ȿ��
	}
	return head;                 // ����� head ��ȯ
}

// ���� ����Ʈ�� ����ϴ� �Լ�
void print_list(LinkNode* head) {
	LinkNode* temp = head;       // ��ȸ ������
	while (temp != NULL) {
		printf("%d -> ", temp->data); // ������ ���
		temp = temp->link;            // ���� ���� �̵�
	}
	printf("NULL\n");                // �� ǥ��
}

// ���� ����Ʈ�� ��� ��带 �������� �����ϴ� �Լ�
void free_list(LinkNode* head) {
	LinkNode* temp;
	while (head != NULL) {
		temp = head;             // ���� ��带 temp�� ����
		head = head->link;       // ���� ���� �̵�
		free(temp);              // ���� ��� �޸� ����
	}
}

// main �Լ�: ���α׷��� ������
int main(void)
{
	LinkNode* head = NULL;      // �� ����Ʈ ����

	// ������ ���ʿ� �����Ͽ� ����Ʈ ���� (�������� ���Ե�)
	head = insert_node(head, 1);  // head: 1
	head = insert_node(head, 2);  // head: 2 -> 1
	head = insert_node(head, 3);  // head: 3 -> 2 -> 1
	head = insert_node(head, 4);  // ...
	head = insert_node(head, 5);
	head = insert_node(head, 6);
	head = insert_node(head, 7);
	head = insert_node(head, 8);  // ���� ����Ʈ: 8 -> 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1

	printf("������ ����Ʈ : \n");
	print_list(head);           // ���� �� ����Ʈ ���

	head = delete_odd(head);    // Ȧ�� ��° ��� ����

	printf("������ ����Ʈ : \n");
	print_list(head);           // ���� �� ����Ʈ ���

	free_list(head);            // �޸� ����

	return 0;                   // ���α׷� ����
}
