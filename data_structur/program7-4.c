#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element[100];		//�ִ�99�ڸ� ������ �� �ִ�.
typedef struct ListNode			//��� ����ü ����
{
	element data;		//�������
	struct ListNode* link;	// ������带 ����ų ������
}ListNode;

//ù ��° ���� �Լ�
ListNode* insert_first(ListNode* head, element data) //head�� ù ��° ��带 ����Ű�� ������,data�� ���ο� ��忡 �߰��� ��
{
	ListNode* node = (ListNode*) malloc(sizeof(ListNode));	//node�� ���� �޸� �Ҵ�
	//head�� ���������
	if (node == NULL)
	{
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	strcpy_s(node->data, sizeof(node->data), data);  // data ���� ��忡 ����
	if (head == NULL)
	{  
		node->link = node;      // �ڱ� �ڽ��� ����Ű���� ���� (��ȯ ���� ����Ʈ)
		head = node;            // head�� �� ��带 ����
	}
	else//head ������� ������ 
	{
		ListNode* temp = head;
		while (temp->link != head) {
			temp = temp->link;
		}
		node->link = head;      // �� ����� link�� ���� head�� ����Ŵ
		head = node;            // head�� �� ���� ������Ʈ
	}
	return head;	//�����head�� ��ȯ
}

int main(void)
{
	ListNode* head = NULL;		//����Ʈ ù ��° ����ų ������, ó������ head�� ����Ŵ

	head = insert_first(head, "KIM");//KIM������ head�� �� ��带 ����Ŵ
	head = insert_first(head, "PARK");//PARK������ head�� �� ��带 ����Ŵ
	head = insert_first(head, "LEE");//LEE������ head�� �� ��带 ����Ŵ

	ListNode* p = head;	//p�� ���� ��带 ����ų ������, ó������ head�� ����Ŵ 
	int count = 0;		//��µ� ��� ���ڸ� ��

	//��ȯ ���Ḯ��Ʈ�� ���������� ���
	do {
		printf("���� ���� = %s\n", p->data);	//���� ����� ������ ���
		p = p->link;
		count++;
	} while (p != head && count < 3);//p�� head�� ���ƿö� ���� �׸���3���� ��带 ����Ҷ�����
	// ���� �Ҵ�� �޸� ���� (�ʼ�)
	if (head != NULL) {
		ListNode* current = head->link;
		ListNode* temp = NULL;
		while (current != head) {
			temp = current;
			current = current->link;
			free(temp);
		}
		free(head);
		head = NULL;
	}

	return 0;
}

