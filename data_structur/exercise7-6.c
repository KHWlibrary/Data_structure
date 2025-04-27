//���� ���� ����Ʈ�� �������� ��ȸ�ϸ鼭 ����� ������ ���� ����ϴ� ���α׷�
#include <stdio.h>  //printf�Լ��� ����
#include <stdlib.h> //malloc, free, exit�Լ��� ����

typedef int element;	//element�� int������ ����� �� �ְ���
typedef struct ListNode	//���Ḯ��Ʈ ��� ����ü ����
{
	element data;	//��忡 ������ data �� 
	struct ListNode* link;	//���� ��带 ����Ű�� ������
}ListNode;	//����ü �̸�

//����Ʈ�� ����Լ��� ����ϴ� �Լ�
void print_list(ListNode* head)
{
	if (head == NULL) return;	//����Ʈ�� ����ִٸ� ������� �ʰ� ����
	ListNode* p = head;		//���� ��带 ����Ű�� ������, head���� ����
	//������ ���,������� �̵��� ������ 1���� �����
	//�������� p�� head�ƴϸ� ���� head�̸� �ݺ����� ��������
	do {
		printf(" %d ", p->data);	//���� ��� ������ ���
		p = p->link;	//���� ���� �̵�
	} while (p != head);	//�� ���� �������� �ݺ�
}

//�� �տ� �����ϴ� �� ��带 �����ϴ� �Լ�
ListNode* insert_first(ListNode* head, element data)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	if (newnode == NULL) {     //�޸� �Ҵ� ���н�  ���� �޽��� ���
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);        //����
	}
	newnode->data = data;	//�� ��忡 ������ ����
	
	if (head == NULL) {	//����Ʈ�� ���������
		head = newnode;	//head�� �� ���� ����
		newnode->link = head; //�� ��尡 �ڱ� �ڽ��� ����Ű�� ����
	}
	else
	{
		ListNode* tail = head;	//tail ��� �Ҵ�
		while (tail->link != head) {  // ������ ��� ã��
			tail = tail->link;	//���� ��带 ����Ű�� ������
		}
		tail->link = newnode;	//������ ��尡 �� ��带 ����Ű�� ����
		newnode->link = head;	 //�� ��尡 head�� ����Ŵ
		head = newnode; // �� ��带 head�� ����
	}
	return head; //����� head�� ��ȯ
}

//���� ���Ḯ��Ʈ�� ��� ��带 �����ϴ� �Լ�
void free_list(ListNode* head) {
	if (head == NULL) return;	//����Ʈ�� ��������� �ٷ� ����

	ListNode* p = head->link;	//�� ��° ������ ����
	ListNode* temp;

	while (p != head) {
		temp = p;	//�����带 �ӽ÷� ����
		p = p->link;	//���� ���� �̵�
		free(temp);	//���� ��� �޸� ����
	}
	free(head);	//���������� head��� ����
}

//�����Լ�
int main(void)
{
	ListNode* head = NULL;		//head����Ʈ �ʱ�ȭ

	int count, data;	//count, data ���������� ǥ��
	int i;	//for���� ���� ����
	
	printf("������ ������ �Է��ϼ���: ");
	scanf_s("%d", &count);		//������ ���� �Է�

	for (i = 1; i < count+1; i++) {
		printf("���#%d�� �����͸� �Է��ϼ���: ", i);
		scanf_s("%d", &data);	//������ �Է�
		head = insert_first(head, data);
	}
	printf("������ �������� ���: ");
	print_list(head);	//������ �������� ���
	
	free_list(head);	//��� �޸� ����
	
	return 0;//���α׷� ����
}