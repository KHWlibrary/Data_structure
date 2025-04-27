#define _CRT_SECURE_NO_WARNING     // strcpy_s �� ���� �Լ� ��� �� ��� ����
#include<stdio.h>                  // ǥ�� ����� �Լ� ���
#include<stdlib.h>                 // ���� �޸� �Ҵ��� ���� malloc, free
#include<string.h>                 // ���ڿ� �Լ� ����� ���� ���

// ��� ������ ������ ��� ����ü ����
typedef struct ListNode {
	char name[20];                // �̸� (���ڿ� �ִ� 19�� + �� ����)
	int age;                      // ����
	float height;                 // Ű
	struct ListNode* link;       // ���� ��带 ����Ű�� ������
} ListNode;

// ���� ����Ʈ�� ���ο� ��� �߰� �Լ�
ListNode* insert(ListNode* head, char* name, int age, double height)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));  // �� ��� ���� �޸� �Ҵ�
	strcpy_s(p->name, sizeof(p->name), name);            // �̸� ���� (���� �Լ� ���)
	p->age = age;                                        // ���� ����
	p->height = height;                                  // Ű ����
	p->link = NULL;                                      // ��ũ �ʱ�ȭ

	// ���� ����Ʈ�� ��� �ִ� ���, �� ��带 head�� ����
	if (head == NULL) {
		head = p;
	}
	// ����Ʈ�� ��� ���� ���� ���, ������ ��带 ã�� �� ��带 ����
	else {
		ListNode* temp = head;                           // ��ȸ�� ������
		while (temp->link != NULL) {                     // ������ ������ �̵�
			temp = temp->link;
		}
		temp->link = p;                                  // ������ ����� link�� �� ��� ����
	}
	return head;                                         // ����� head ��ȯ
}

// ���� ����Ʈ�� ��� �����͸� ����ϴ� �Լ�
void print_list(ListNode* head) {
	ListNode* temp = head;                              // ��ȸ�� ������
	while (temp != NULL) {                              // ����Ʈ ������ ��ȸ
		printf("�̸�:%s, ����:%d, Ű:%.2f\n", temp->name, temp->age, temp->height);
		temp = temp->link;                              // ���� ���� �̵�
	}
}

// ���� ����Ʈ�� ��� ��带 ���� �޸� �����ϴ� �Լ�
void free_list(ListNode* head)
{
	ListNode* temp;                                     // �ӽ� ������
	while (head != NULL) {                              // ��尡 ���� ���� ������ �ݺ�
		temp = head;                                    // ���� ��� �ӽ� ����
		head = head->link;                              // ���� ���� �̵�
		free(temp);                                     // ���� ��� �޸� ����
	}
}

// ���α׷� ���� ����
int main(void)
{
	ListNode* head = NULL;                              // ���� ����Ʈ�� ���� ������ (��� ����)

	// ���� ���� ����
	head = insert(head, "�赵��", 23, 183.0f);
	head = insert(head, "�輱��", 37, 165.0f);
	head = insert(head, "����ȣ", 31, 178.0f);

	// ����Ʈ ���
	printf("���� ��������:\n");
	print_list(head);

	// �޸� ����
	free_list(head);

	return 0;                                            // ���α׷� ���� ����
}
