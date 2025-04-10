#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char name[100];		//���ڿ� ���� ����
}element;

typedef struct ListNode {		//��� Ÿ��
	element data;
	struct ListNode* link;
}ListNode;

//���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//�� �տ� �߰�
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));		//ListNode���� �Ҵ�
	p->data = value;	//�� ����
	p->link = head;		//��� ������ �� ����
	head = p;			//��� ������ ����
	return head;
}

//����Ʈ 
void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%s->", p->data.name);			//"%s"�� ���ڿ� ���
	printf("NULL \n");
}

//�׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head = NULL;
	element data;

	strcpy(data.name, "APPLE");			//strcpy ���ڿ� ������� �ϳ��ϳ� ������
	head = insert_first(head, data);
	print_list(head);
	strcpy(data.name, "BANANA");
	head = insert_first(head, data);
	print_list(head)	;
	strcpy(data.name, "ORANGE");
	head = insert_first(head, data);
	print_list(head);
}