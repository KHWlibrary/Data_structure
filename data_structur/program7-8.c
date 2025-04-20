#include<stdio.h>   // ǥ�� ����� �Լ� ����� ���� ��� ����
#include<stdlib.h>  // ���� �޸� �Ҵ��� ���� ��� ����
#include<string.h>  // ���ڿ� ó�� �Լ� ����� ���� ��� ����

// element�� char �迭(���ڿ�)�� ����, ���̴� 100
typedef char element[100];

// ���� ���� ����Ʈ�� ��� ����ü ����
typedef struct DoubleListNode
{
	element data;                     // ��忡 ����� ������(���ڿ�)
	struct DoubleListNode* left_link;   // ����(����) ��带 ����Ű�� ������
	struct DoubleListNode* right_link;  // ������(����) ��带 ����Ű�� ������
} DoubleListNode;

// ���� ���õ� ��带 ����Ű�� ���� ������
DoubleListNode* current;

// ����Ʈ ��� ��� �ʱ�ȭ �Լ�
void init(DoubleListNode* pointhead)
{
	pointhead->left_link = pointhead;  // ���� �����Ͱ� �ڱ� �ڽ��� ����Ŵ (���� ����)
	pointhead->right_link = pointhead; // ������ �����͵� �ڱ� �ڽ��� ����Ŵ (���� ����)
}

// ����Ʈ�� ��� ��带 ����ϴ� �Լ�
void print_DoubleListNode(DoubleListNode* pointhead)
{
	DoubleListNode* p;
	// ��� ����� �����ʺ��� �����Ͽ� �ٽ� ����� ���ƿ� ������ �ݺ�
	for (p = pointhead->right_link; p != pointhead; p = p->right_link) {
		if (p == current)  // ���� ����� ��� ǥ��
			printf("<-| #%s# |->", p->data);
		else               // �׷��� ������ �Ϲ� ���
			printf("<-| %s |->", p->data);
	}
	printf("\n");  // �ٹٲ�
}

// �� ��带 Ư�� ����� �����ʿ� �����ϴ� �Լ�
void insert_DoubleListNode(DoubleListNode* before, element data)	//before ���� ��� ǥ��
{
	// �� ��带 ���� �޸� �Ҵ�
	DoubleListNode* newnode = (DoubleListNode*)malloc(sizeof(DoubleListNode));
	// ���ڿ� ���� (�����ϰ� ũ�� ���)
	strcpy_s(newnode->data, sizeof(newnode->data), data);
	// �� ����� ���� �����ʹ� ���� ��ġ ���� ��带 ����Ŵ
	newnode->left_link = before;
	// �� ����� ������ �����ʹ� ���� ��ġ ���� ����� ���� ��带 ����Ŵ
	newnode->right_link = before->right_link;
	// ���� ��ġ ���� ����� ���� ��尡 �� ��带 ����Ű�� ��
	before->right_link->left_link = newnode;
	// ���� ��ġ ���� ����� �������� �� ��带 ����Ű�� ��
	before->right_link = newnode;
}

// Ư�� ��带 ����Ʈ���� �����ϴ� �Լ�
void delete(DoubleListNode* head, DoubleListNode* removed)
{
	if (removed == head) return; // ��� ���� �������� ����
	// ������ ����� ���� ��尡 ������ ����� ������ ��带 ����Ű�� ��
	removed->left_link->right_link = removed->right_link;
	// ������ ����� ������ ��尡 ������ ����� ���� ��带 ����Ű�� ��
	removed->right_link->left_link = removed->left_link;
	// ������ ����� �޸� ����
	free(removed);
}

// ���� �Լ� - ���� ���� ����Ʈ �׽�Ʈ
int main(void)
{
	char ch;  // ����� �Է��� ������ ���� ����
	// ��� ��带 ���� �޸� ���� �Ҵ�
	DoubleListNode* head = (DoubleListNode*)malloc(sizeof(DoubleListNode));
	// ��� ��� �ʱ�ȭ
	init(head);

	// ������ ���� (����Ʈ�� �� ������ ���ԵǹǷ� �������� ���� �� ����)
	insert_DoubleListNode(head, "�ƴϱ�");
	insert_DoubleListNode(head, "sheesh");
	insert_DoubleListNode(head, "forever");
	insert_DoubleListNode(head, "drip");

	// current �����͸� ù ��° ���� ���� ����
	current = head->right_link;
	// ����Ʈ ���
	print_DoubleListNode(head);

	// ����� �Է��� �޾� �ݺ� ó��
	do {
		printf("\n��ɾ �Է��Ͻÿ�(<,>,q): ");  // ��ɾ� �ȳ�
		ch = getchar();  // ����� �Է� �ޱ�

		if (ch == '<') {  // �������� �̵�
			current = current->left_link;
			if (current == head)  // ����� ������ ���, �ٽ� ����(������ ���)�� �̵�
				current = current->right_link;
		}
		else if (ch == '>') {  // ���������� �̵�
			current = current->right_link;
			if (current == head)  // ����� ������ ���, �ٽ� ������(ù ���)�� �̵�
				current = current->right_link;
		}
		// ����Ʈ ��� (���� ��ġ ����)
		print_DoubleListNode(head);
		getchar();  // �Է� ���� ������ (Enter ó��)
	} while (ch != 'q');  // 'q' �Է� �� ����

	// ��� ��� �޸� ����
	free(head);
	return 0;  // ���α׷� ����
}
