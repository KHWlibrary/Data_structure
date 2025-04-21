#include<stdio.h>     // ǥ�� ����� �Լ� ����� ���� ��� ����
#include<stdlib.h>    // �Ϲ����� ��ƿ��Ƽ �Լ���(��: exit �Լ� ��)�� ���� ��� ����

#define MAX_STACK_SIZE 100   // ������ �ִ� ũ�⸦ 100���� ����
typedef int element;         // element�� int������ �����Ͽ� �ڵ� ������ ���
element stack[MAX_STACK_SIZE];  // ���� �迭�� ������ ����
int top = -1;                // ������ top�� -1�� �ʱ�ȭ�Ͽ� �� ���� ���·� ����

// ���� ���¸� �˻��ϴ� �Լ�
int is_empty()
{
	return(top == -1);       // top�� -1�̸� ������ ����ִ� ����
}

// ��ȭ ���¸� �˻��ϴ� �Լ�
int is_full()
{
	return(top == (MAX_STACK_SIZE - 1)); // top�� �ִ� �ε����� �����ߴ��� Ȯ��
}

// ���ÿ� �����͸� �����ϴ� �Լ� (push)
void push(element item)
{
	if (is_full()) {         // ������ ���� á���� Ȯ��
		fprintf(stderr, "���� ��ȭ ����\n"); // ���� �޽��� ���
		return;               // �Լ� ����
	}
	else stack[++top] = item;  // top�� ������Ű�� �ش� ��ġ�� item ����
}

// ���ÿ��� �����͸� �����ϰ� ��ȯ�ϴ� �Լ� (pop)
element pop()
{
	if (is_empty()) {        // ������ ����ִ��� Ȯ��
		fprintf(stderr, "���� ���� ����"); // ���� �޽��� ���
		exit(1);             // ���α׷� ������ ����
	}
	else return stack[top--]; // top ��ġ�� �����͸� ��ȯ�ϰ� top ����
}

// ������ top ��Ҹ� ��ȯ�ϵ� �������� �ʴ� �Լ� (peek)
element peek()
{
	if (is_empty()) {        // ������ ����ִ��� Ȯ��
		fprintf(stderr, "���� ���� ����"); // ���� �޽��� ���
		exit(1);             // ���α׷� ������ ����
	}
	else return stack[top];  // top ��ġ�� �����͸� �״�� ��ȯ
}

// ���� �Լ�: ���� ��� ����
int main(void)
{
	push(1);                 // ���ÿ� 1 �߰�
	push(2);                 // ���ÿ� 2 �߰�
	push(3);                 // ���ÿ� 3 �߰�

	printf("%d\n", pop());   // ���ÿ��� ���� ���� ���(3)�� �����ϰ� ���
	printf("%d\n", pop());   // ���� ���(2)�� �����ϰ� ���
	printf("%d\n", pop());   // ������ ���(1)�� �����ϰ� ���

	return 0;                // ���α׷� ����
}
