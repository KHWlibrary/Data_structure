#include<stdio.h>
#include<stdlib.h>

typedef int element; // element��� �̸����� int �ڷ����� ���� (�ڵ��� ������ ���)
typedef struct DoubleListNode	// ���� ���� ����Ʈ ����ü ����
{
	element data;				// �����͸� ������ ���
	struct DoubleListNode* left_link;  // ���� ��带 ����ų ������
	struct DoubleListNode* right_link; // ������ ��带 ����ų ������
}DoubleListNode;

// ���� ���� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void init(DoubleListNode* pointhead)
{
	pointhead->left_link = pointhead;  // ��� ����� ���� ��ũ�� �ڱ� �ڽ��� ����Ŵ (�� ����Ʈ ����)
	pointhead->right_link = pointhead; // ��� ����� ������ ��ũ�� �ڱ� �ڽ��� ����Ŵ (�� ����Ʈ ����)
}

// ���� ���� ����Ʈ�� ��� ����� �����͸� ����ϴ� �Լ�
void print_DoubleList(DoubleListNode* pointhead)
{
	DoubleListNode* p; // ���� ��带 ����ų ������
	// ��� ����� ������ ������ �����Ͽ� ��� ��忡 ������ ������ ��ȸ
	for (p = pointhead->right_link; p != pointhead; p = p->right_link)
	{
		printf("<-| |%d| |->", p->data); // �� ����� �����͸� Ư�� �������� ���
	}
	printf("\n"); // �� �� ��� �� ����
}

// �־��� ��� before�� �����ʿ� ���ο� ������(data)�� ���� ��带 �����ϴ� �Լ�
void insert_DoubleNode(DoubleListNode* before, element data)
{
	DoubleListNode* newnode = (DoubleListNode*)malloc(sizeof(DoubleListNode)); // ���ο� ��带 ���� ���� �޸� �Ҵ�
	newnode->data = data; // ���ο� ��忡 ������ ����
	newnode->left_link = before; // ���ο� ����� ���� ��ũ�� before ��带 ����Ŵ
	newnode->right_link = before->right_link; // ���ο� ����� ������ ��ũ�� before ����� ���� ������ ��带 ����Ŵ
	before->right_link->left_link = newnode; // before ����� ���� ������ ����� ���� ��ũ�� ���ο� ���� ����
	before->right_link = newnode; // before ����� ������ ��ũ�� ���ο� ���� �����Ͽ� ���ο� ��带 ����
}

// �־��� ��� removed�� ���� ���� ����Ʈ���� �����ϴ� �Լ�
void delete_DoubleNode(DoubleListNode* head, DoubleListNode* removed)
{
	if (removed == head) return; // ������ ��尡 ��� ����� �ƹ��͵� ���� �ʰ� �Լ� ����
	removed->left_link->right_link = removed->right_link; // ������ ����� ���� ����� ������ ��ũ�� ������ ����� ������ ���� ����
	removed->right_link->left_link = removed->left_link; // ������ ����� ������ ����� ���� ��ũ�� ������ ����� ���� ���� ����
	free(removed); // ������ ����� ���� �޸� ����
}

// ���� ���� ����Ʈ�� �׽�Ʈ�ϴ� ���� �Լ�
int main(void)
{
	DoubleListNode* head = (DoubleListNode*)malloc(sizeof(DoubleListNode)); // ��� ��带 ���� ���� �޸� �Ҵ�
	init(head); // ��� ��带 �̿��Ͽ� ���� ���� ����Ʈ �ʱ�ȭ
	printf("�߰� �ܰ�\n");
	for (int i = 0; i < 5; i++) {
		// ��� ����� �����ʿ� ���ο� ��带 ���� (��������� ����Ʈ�� �տ� �߰��Ǵ� ����)
		insert_DoubleNode(head, i);
		print_DoubleList(head); // ���� �� ���� ����Ʈ ���� ���
	}
	printf("\n���� �ܰ�\n");
	for (int i = 0; i < 5; i++) {
		print_DoubleList(head); // ���� �� ���� ����Ʈ ���� ���
		delete_DoubleNode(head, head->right_link); // ��� ����� ������ ��带 ���� (��������� ����Ʈ�� �տ������� ����)
	}
	free(head); // ���α׷� ���� �� ��� ����� ���� �޸� ����
	return 0; // ���α׷� ���� ����
}