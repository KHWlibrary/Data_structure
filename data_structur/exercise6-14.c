#define _CRT_SECURE_NO_WARNING
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ListNode
{
	char name[20];
	int age;
	float height;
	struct ListNode* link;
}ListNode;

//����Ʈ ���ο� ��� �߰�
ListNode* insert(ListNode* head, char* name, int age, double height)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	strcpy_s(p->name, sizeof(p->name), name);
	p->age = age;
	p->height = height;
	p->link = NULL;

	//����Ʈ�� ��������� ���ο� ����� ù ��°�� ����
	if (head == NULL) {
		head = p;
	}
	//�׷��� ������ �������� �߰�
	else
	{
		ListNode* temp = head;
		while (temp->link != NULL)
		{
			temp = temp->link;
		}
		temp->link = p;
	}
	return head;
}
// ���� ����Լ�
void print_list(ListNode* head) {
	ListNode* temp = head;
	while (temp != NULL) {
		printf("�̸�:%s, ����:%d, Ű:%.2f\n", temp->name, temp->age, temp->height);
		temp = temp->link;
	}
}
//�޸� �����Լ�
void free_list(ListNode* head)
{
	ListNode* temp;
	while (head != NULL) {
		temp = head;
		head = head->link;
		free(temp);
	}
}
//�׽�Ʈ
int main(void)
{
	ListNode* head = NULL;

	//������ ����
	head = insert(head, "�赵��", 23, 183.0f);
	head = insert(head, "�輱��", 37, 165.0f);
	head = insert(head, "����ȣ", 31, 178.0f);

	//���Ḯ��Ʈ ���
	printf("���� ��������:\n");
	print_list(head);

	//���Ḯ��Ʈ �޸�����
	free_list(head);

	return 0;
}