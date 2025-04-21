// �迭�� ����ִ� ������ ������ �Ųٷ� ����ϴ� ���α׷�. ������ �����
#define _CRT_SECURE_NO_WARNINGS    // Visual Studio���� scanf ���� ��� ���Ÿ� ���� ��ũ��

#include <stdio.h>      // ǥ�� ����� �Լ� ���
#include <stdlib.h>     // exit �Լ� ���

//===== ���� �ڵ��� ���� =====
#define MAX_STACK_SIZE 7           // ���ÿ� ������ �� �ִ� �ִ� ��� ���� (0~6���� �� 7��, ������ 6�ڸ� ��������)

// element��� ��Ī�� int�� ���� (���ÿ� ������ ������ Ÿ��)
typedef int element;

// ���� �ڷ��� ����
typedef struct {
    element data[MAX_STACK_SIZE]; // �����͸� ������ �迭
    int top;                      // ������ top �ε����� ����Ű�� ����
} StackType;

// ���� �ʱ�ȭ �Լ� - top�� -1�� �ʱ�ȭ�Ͽ� ���� ���·� ����
void init_stack(StackType* s)
{
    s->top = -1;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int is_empty(StackType* s)
{
    return (s->top == -1);    // top�� -1�̸� ���� ����
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));   // top�� ������ �ε����� �����ߴ��� Ȯ��
}

// ���ÿ� ��Ҹ� �����ϴ� �Լ�
void push(StackType* s, element item)
{
    if (is_full(s)) {    // ������ ���� �� ��� ���� ���
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else
        s->data[++(s->top)] = item;    // top�� �ϳ� ������Ű�� �ش� ��ġ�� �� ����
}

// ���ÿ��� ��Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
element pop(StackType* s)
{
    if (is_empty(s)) {    // ������ ��� �ִ� ��� ���� ��� �� ����
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];   // top ��ġ�� ���� ��ȯ�ϰ� top�� ����
}

// ������ top ��Ҹ� �������� �ʰ� Ȯ���ϴ� �Լ�
element peek(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else
        return s->data[s->top];   // top ��ġ�� ���� �״�� ��ȯ
}
//===== ���� �ڵ��� �� =====

// ���� �Լ� ����
int main(void)
{
    StackType s;             // ���� ���� ����
    init_stack(&s);          // ���� �ʱ�ȭ

    int num;                 // ����ڷκ��� �Է� ���� ����

    // �ȳ� �޽��� ���
    printf("���� �迭�� ũ��: %d\n", MAX_STACK_SIZE - 1);    // �ִ� 6�ڸ����� �Է� ����
    printf("������ �Է��Ͻÿ�: ");
    scanf("%d", &num);       // ����� �Է� �ޱ�

    // �Է� ���� 0�̸�
