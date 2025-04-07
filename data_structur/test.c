#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h>

#pragma warning (disable : 4996)

typedef struct queue
{
	int* arr;	//���� �޸��� �ּҸ� �����ϴ� ������
	int front;	//������ġ(�迭�� ÷��)
	int rear;	//������ġ(�迭�� ÷��)
	int count;	//����� ������ ����
	int capacity;// �迭�� �ִ� �뷮
}queue;

void queueInit(queue* pQue, int size);
void enqueue(queue* pQue, int data);
int dequeue(queue* pQue);
void print(const queue* pQue);
void queueClear(queue* pQue);
int main()
{
	int choice, data;

	queue que;	//����ü ����

	queueInit(&que, 5);

	while (1)
	{
		system("cls");
		printf("\n\n\t\t***Circular Queue(����ť)***\n\n");
		printf("1.enqueue(����)   2.dequeue(����)   3.print    4.clear   0.terminae\n");
		printf("choice : ");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			printf("\n\nInteger Input : ");
			scanf("%d", &data);
			while (getchar() != '\n');
			enqueue(&que, data);
			break;
		case 2:
			data = dequeue(&que);		//���� ��, ������ ���� ����

			if (data == -999999999)
				print("\n\n\t\t queue underflow\n");
			else
				printf("\n\n\t\t%d dequeue\n", data);
			break;
		case 3:
			print(&que);
			break;
		case 4:
			queueClear(&que);
			break;
		case 0:
			free(que.arr);
			exit(0);
		}
		printf("\n\n\t\t");
		system("pause");
	}
	return 0;
}

void queueInit(queue* pQue, int size)
{
	pQue->arr = (int*)malloc(sizeof(int) * size);
	pQue->front = 0;
	pQue->rear = 0;
	pQue->count = 0;
	pQue->capacity = size;
}

void enqueue(queue* pQue, int data)
{
	if (pQue->count == pQue->capacity)		//������� �� �� ����
	{
		printf("\n\n\t\tqueue overflow\n");
		return 0;
	}
	pQue->arr[pQue->rear] = data;;		//������ ����
	pQue->rear++;		//���� ��ġ ����
	pQue->count++;		//���� ���� ����
	if (pQue->rear == pQue->capacity)	//������ ��� �ε���
		pQue->rear = 0;
}

int dequeue(queue* pQue)
{
	int delvalue;
	if (pQue->count == 0) //underflow
	{
		return -999999999;
	}
	delvalue = pQue->arr[pQue->front]; //������ ��
	pQue->front++;	//���� ��ġ ����
	pQue->count--;	//���� ���� ����

	if (pQue->front == pQue->capacity)
		pQue->front = 0;
	return delvalue;	//������ ��
}

void print(const queue* pQue)
{
	int i;

	printf("\n\nQueue display(FIFO) : ");
	if (pQue->count == 0) {
		printf("\n\n\t\tť�� ��� �ִ� ���� �Դϴ�.\n");
		return;
	}

	for (i = pQue->front; i < pQue->front + pQue->count; i++)
	{
		printf("%d", pQue->arr[i % pQue->capacity]);
	}
	puts("");
}

void queueClear(queue* pQue)
{
	pQue->count = 0;
	pQue->front = 0;
	pQue->rear = 0;
}
