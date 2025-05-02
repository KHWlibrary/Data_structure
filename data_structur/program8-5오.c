//���� ��ȸ ���α׷�
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//==========����ť �ڵ� ����================
// ť�� �ִ� ũ�� ���� (�迭 ũ��)
#define MAX_QUEUE_SIZE 100

typedef TreeNode* element;

// ť ����ü ����
typedef struct {
	int front;                      // front: �����͸� ���� ��ġ
	int rear;                       // rear: �����͸� ���� ��ġ
	element data[MAX_QUEUE_SIZE];   // ť �����͸� ������ �迭
} QueueType;

// ���� ó�� �Լ�: �޽��� ��� �� ���α׷� ����
void error(char* message)
{
	fprintf(stderr, "%s\n", message);  // ���� �޽����� stderr�� ���
	exit(1);                           // ������ ����
}

// ť �ʱ�ȭ �Լ�: front�� rear�� -1�� ������ �� ���·� �ʱ�ȭ
void init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}

// ť�� ���� á���� Ȯ���ϴ� �Լ�
int is_full(QueueType* q)
{
	if (q->rear == MAX_QUEUE_SIZE - 1)  // rear�� �迭�� ������ �ε����� �����ϸ� ��ȭ
		return 1;
	else
		return 0;
}

// ť�� ������� Ȯ���ϴ� �Լ�
int is_empty(QueueType* q)
{
	if (q->front == q->rear)  // front�� rear�� ������ ť�� ��� ����
		return 1;
	else
		return 0;
}

// ť�� �����͸� �߰��ϴ� �Լ�
void enqueue(QueueType* q, int item)
{
	if (is_full(q)) {                   // ť�� ���� ���� ���� �߻�
		error("ť�� ��ȭ�����Դϴ�.");
		return;
	}
	q->data[++(q->rear)] = item;       // rear�� ������Ű�� �ش� ��ġ�� ������ ����
}

// ť���� �����͸� ������ �Լ�
TreeNode* dequeue(QueueType* q)
{
	if (is_empty(q)) {                 // ť�� ������� ���� �߻�
		error("ť�� �����Դϴ�");
		return NULL;
	}
	return q->data[++(q->front)];  // front�� ������Ű�� �ش� ��ġ�� ������ ��ȯ
}

//���� ��ȸ �Լ�
void level_order(TreeNode* ptr)
{
	QueueType q;
	init_queue(&q);	//ť �ʱ�ȭ
	if (ptr == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf(" [%d] ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}
//			15
//		4		20
//	  1		  16   25
TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,&n1,NULL };
TreeNode n3 = { 16,NULL,NULL };
TreeNode n4 = { 25,NULL,NULL };
TreeNode n5 = { 20,&n3,&n4 };
TreeNode n6 = { 15,&n2,&n5 };
TreeNode* root = &n6;

int main(void)
{
	printf("���� ��ȸ=");
	level_order(root);
	printf("\n");
	return 0;
}