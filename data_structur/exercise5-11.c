#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX 100

//ť�� ���� ����ü
typedef struct {
	char items[MAX];
	int front;
	int rear;
}Queue;

//ť �ʱ�ȭ
void initQueue(Queue* q) {
	q->front = 0;
	q->rear = -1;
}

//ť�� ����ִ��� Ȯ��
int is_empty(Queue* q) {
	return q->rear < q->front;
}
//ť�� ����
void enqueue(Queue* q, char ch) {
	if (q->rear < MAX - 1) {
		q->items[++(q->rear)] = ch;
	}
}
//ť���� ����
char dequeue(Queue* q) {
	if (!is_empty(q)) {
		return q->items[(q->front)++];
	}
	return '\0';		// ť�� ��� ������ �߸��� ���� ��ȯ
}

//ȸ�� �Ǻ� �Լ�
int is_palindrome(const char* str) {
	Queue q;
	initQueue(&q);

	//���ڿ��� ť�� �ֱ�(��ҹ��� ���� ����, ���� ����)
	for (int i = 0; str[i] != '\0'; i++) {
		if (isalnum(str[i])) {		//isalnum ���ĺ� �Ǵ� �����̸� 0�� �ƴ� ���� ��ȯ�Ѵ�
			enqueue(&q, tolower(str[i]));	//�ҹ��ڷ� ����
		}
	}
	//ť�� �հ� �ڸ� ���Ͽ� ȸ�� �Ǻ�
	for (int i = 0; i < (q.rear - q.front + 1) / 2; i++) {
		if (dequeue(&q) != dequeue(&q)) {		//queue�հ� ���� ���ڸ� ���� ������ ���Ѵ�
			return 0;	//ȸ���� �ƴϸ� 0 ��ȯ
		}
	}
	return 1;	//ȸ���̸� 1 ��ȯ
}

int main() {
	char str[MAX];
	printf("���ڿ��� �Է��ϼ���: ");
	fgets(str, sizeof(str), stdin);		//stdin ǥ���Է�
	str[strcspn(str, "\n")] = '\0'; //���๮�� ����

	if (is_palindrome(str)) {
		printf("ȸ���Դϴ�.\n");
	}
	else {
		printf("ȸ���� �ƴմϴ�.\n");
	}
	return 0;
}