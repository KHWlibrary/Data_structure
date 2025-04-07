#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h>

#pragma warning (disable : 4996)

typedef struct queue
{
	int* arr;	//동적 메모리의 주소를 저장하는 포인터
	int front;	//삭제위치(배열의 첨자)
	int rear;	//삽입위치(배열의 첨자)
	int count;	//저장된 원소의 개수
	int capacity;// 배열의 최대 용량
}queue;

void queueInit(queue* pQue, int size);
void enqueue(queue* pQue, int data);
int dequeue(queue* pQue);
void print(const queue* pQue);
void queueClear(queue* pQue);
int main()
{
	int choice, data;

	queue que;	//구조체 변수

	queueInit(&que, 5);

	while (1)
	{
		system("cls");
		printf("\n\n\t\t***Circular Queue(원형큐)***\n\n");
		printf("1.enqueue(삽입)   2.dequeue(삭제)   3.print    4.clear   0.terminae\n");
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
			data = dequeue(&que);		//삭제 후, 삭제된 값을 리턴

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
	if (pQue->count == pQue->capacity)		//저장공간 꽉 찬 상태
	{
		printf("\n\n\t\tqueue overflow\n");
		return 0;
	}
	pQue->arr[pQue->rear] = data;;		//데이터 저장
	pQue->rear++;		//저장 위치 변경
	pQue->count++;		//저장 개수 증가
	if (pQue->rear == pQue->capacity)	//범위를 벗어난 인덱스
		pQue->rear = 0;
}

int dequeue(queue* pQue)
{
	int delvalue;
	if (pQue->count == 0) //underflow
	{
		return -999999999;
	}
	delvalue = pQue->arr[pQue->front]; //삭제된 값
	pQue->front++;	//삭제 위치 증가
	pQue->count--;	//저장 개수 감소

	if (pQue->front == pQue->capacity)
		pQue->front = 0;
	return delvalue;	//삭제된 값
}

void print(const queue* pQue)
{
	int i;

	printf("\n\nQueue display(FIFO) : ");
	if (pQue->count == 0) {
		printf("\n\n\t\t큐가 비어 있는 상태 입니다.\n");
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
