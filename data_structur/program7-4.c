#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element[100];		//�ִ�99�ڸ� ������ �� �ִ�.
typedef struct ListNode			//��� ����ü ����
{
	element data;		//�������
	struct Listnode* link;	// ������带 ����ų ������
}Listnode;

//ù ��° ���� �Լ�
ListNode* insert_first(ListNode* head, element data) //head�� ù ��° ��带 ����Ű�� ������,data�� ���ο� ��忡 �߰��� ��
{
	ListNode* node = (Listnode*)malloc(sizeof(ListNode));	//node�� ���� �޸� �Ҵ�
	//head�� ���������
	if (head == NULL)
	{
		head = node;	//head�� ��� �ְ�
		node->link = head;	//link�� head�ּ� �ֱ�
	}
	else//head ������� ������ 
	{
		node->link = head->link;//head �ּҸ� ���ο� node�� �ֱ�
		head->link = node;		//
	}
}