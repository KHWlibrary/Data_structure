#include<stdio.h>
#include<stdlib.h>

// ������ ��Ҹ� �����ϴ� Ÿ�� ����
typedef int element;

// ���� ����Ʈ�� ��� ����
typedef struct Listnode
{
	element data;             // ������ �ʵ�
	struct Listnode* link;   // ���� ��带 ����Ű�� ������
} Listnode;

// ���� �߻� �� �޽��� ��� �� ���α׷� ����
void error(char* message)
{
	fprintf(stderr, "%s", message);
	exit(1);
}

// ����Ʈ�� �� �տ� ��带 �����ϴ� �Լ�
Listnode* insert_first(Listnode* head, element data)
{
	Listnode* newnode = (Listnode*)malloc(sizeof(Listnode)); // �� ��� ����
	newnode->data = data;    // �� �Ҵ�
	newnode->link = head;     // �� ��尡 ���� head�� ����Ű�� ��
	head = newnode;           // head�� �� ���� ������Ʈ
	return head;        // ���ο� head ��ȯ
}

// ������ ���(pre) �ڿ� �� ��带 �����ϴ� �Լ�
Listnode* insert(Listnode* head, Listnode* pre, element data)
{
	Listnode* newnode = (Listnode*)malloc(sizeof(Listnode)); // �� ��� ����
	newnode->data = data;        // �� �Ҵ�
	newnode->link = pre->link;    // pre�� ����Ű�� ���� ��带 �� ��尡 ����Ŵ
	pre->link = newnode;          // pre�� �� ��带 ����Ű�� ��
	return head;            // head�� �״�� ��ȯ
}

// ����Ʈ�� ù ��° ��带 �����ϴ� �Լ�
Listnode* delete_first(Listnode* head)
{
	Listnode* removed;
	if (head == NULL) return NULL; // ����Ʈ�� ��������� NULL ��ȯ
	removed = head;          // ������ ��带 ����
	head = removed->link;    // head�� ���� ���� �̵�
	free(removed);           // ���� head �޸� ����
	return head;             // ���ο� head ��ȯ
}

// pre�� ����Ű�� ����� ���� ��带 �����ϴ� �Լ�
Listnode* delete_node(Listnode* head, Listnode* pre)
{
	Listnode* removed;
	if (head == NULL) return NULL; // ����Ʈ�� ��������� NULL ��ȯ
	removed = pre->link;           // ������ ���� pre�� ���� ���
	pre->link = removed->link;     // pre�� ������ ����� ���� ��带 ����Ŵ
	free(removed);                 // ������ ��� �޸� ����
	return head;                   // head �״�� ��ȯ
}

// ����Ʈ�� ��� ��带 ����ϴ� �Լ�
void print_list(Listnode* head)
{
	for (Listnode* p = head; p != NULL; p = p->link)  // ��(NULL)���� ��ȸ
		printf("%d->", p->data);  // ��� ������ ���
	printf("NULL\n");            // ����Ʈ �� ǥ��
}

// ���� �Լ�: ����Ʈ ����/���� �׽�Ʈ
int main()
{
	Listnode* head = NULL; // �ʱ� ����Ʈ�� ��� ����

	// �� 0���� 4���� ����Ʈ �տ� ����
	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i); // �տ� ����
		print_list(head);             // ����Ʈ ���� ���
	}

	// ����Ʈ�� ��� ��带 �տ������� ����
	for (int i = 0; i < 5; i++) {
		head = delete_first(head); // �� ��� ����
		print_list(head);          // ����Ʈ ���� ���
	}
	return 0;
}
