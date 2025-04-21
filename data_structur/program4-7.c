#include<stdio.h>      // ǥ�� ����� �Լ� ���
#include<stdlib.h>     // ���� �޸� �Ҵ�, exit �Լ� ���
#define MAX_STACK_SIZE 100  // ���� �ִ� ũ�� ����

// ===== ���� ���� �ڵ� ���� =====

// ���ÿ� ������ ����� �ڷ����� char�� ���� (���ڳ� ������ ���� ����)
typedef char element;

// ���� ����ü ���� (�迭 ��� ����)
typedef struct {
    element data[MAX_STACK_SIZE];  // ��ҵ��� ������ �迭
    int top;                       // ������ ���� ��(top) ����� �ε���
} StackType;

// ���� �ʱ�ȭ �Լ� - ������ ��� �ִ� ���·� ����
void init_stack(StackType* s)
{
    s->top = -1;  // top�� -1�� �����Ͽ� ������ ��� ������ ǥ��
}

// ������ ��� �ִ��� Ȯ���ϴ� �Լ�
int is_empty(StackType* s)
{
    return(s->top == -1);  // top�� -1�̸� ���� ������
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));  // top�� �迭 ���̸� ��ȭ ����
}

// ���ÿ� ��Ҹ� �߰��ϴ� �Լ� (push ����)
void push(StackType* s, element item)
{
    if (is_full(s)) {  // ������ ���� á�� ���
        fprintf(stderr, "���� ��ȭ ����\n");  // ���� �޽��� ���
        return;  // �� �̻� ������ �� �����Ƿ� ����
    }
    else {
        s->data[++(s->top)] = item;  // top�� ������Ű�� �ش� ��ġ�� item ����
    }
}

// ���ÿ��� ��Ҹ� ������ �Լ� (pop ����)
element pop(StackType* s)
{
    if (is_empty(s)) {  // ������ ��� ������
        fprintf(stderr, "���� ���� ����\n");  // ���� �޽��� ���
        exit(1);  // ���α׷� ���� ����
    }
    else {
        return s->data[(s->top)--];  // top ��ġ�� ���� ��ȯ�ϰ� top ����
    }
}

// ������ top ��Ҹ� �������� �ʰ� ��ȯ�ϴ� �Լ� (peek ����)
element peek(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���ð��鿡��\n");  // ������ ��� ���� ���
        exit(1);
    }
    else {
        return s->data[s->top];  // ���� top ��ġ�� ��� ��ȯ
    }
}

// ===== ���� �ڵ� �� =====

// ===== ���� ǥ�� ���� ��� �Լ� =====
// ���� ǥ���(postfix expression)�� ������ �޾� ��� ����� ��ȯ
int eval(char exp[])
{
    int op1, op2;    // �ǿ����� 1, 2
    int value;       // ���� �� ������ ��ȯ�� �ǿ����� ����
    int i = 0;       // �ݺ��� �ε���
    int len = strlen(exp);  // �Էµ� ���� ���ڿ��� ����
    char ch;         // ���� �а� �ִ� ����
    StackType s;     // ��꿡 ����� ���� ����

    init_stack(&s);  // ���� �ʱ�ȭ

    // ������ ��� ���ڵ��� �� ���ھ� �˻�
    for (i = 0; i < len; i++) {
        ch = exp[i];  // ���� ���ڸ� ch�� ����

        // �ǿ������� ��� (������ ���) �� ���ÿ� push
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            value = ch - '0';  // ���� '0'~'9' �� ���� 0~9�� ��ȯ
            push(&s, value);   // ���ÿ� ���� ����
        }
        else {
            // �������� ���: �ǿ����� 2���� ���ÿ��� ����
            op2 = pop(&s);  // �� ��° �ǿ�����
            op1 = pop(&s);  // ù ��° �ǿ�����

            // �����ڿ� ���� ��� �����ϰ� ����� ���ÿ� ����
            switch (ch) {
            case '+':
                push(&s, op1 + op2);
                break;
            case '-':
                push(&s, op1 - op2);
                break;
            case '*':
                push(&s, op1 * op2);
                break;
            case '/':
                push(&s, op1 / op2);
                break;
            }
        }
    }

    // ����� ���� �� ���ÿ� ���� ���� ����� ��ȯ
    return pop(&s);
}

// ===== ���� �Լ� =====
int main(void)
{
    int result;  // ��� ��� ���� ����

    // �׽�Ʈ�� ���� ǥ�� ���� ���
    printf("����ǥ����� 82/3-32*+\n");

    // ���� ǥ�� ������ ����ϰ� ��� ����
    result = eval("82/3-32*+");  // ���� ����: (8 / 2) - 3 + (3 * 2)

    // ��� ���
    printf("������� %d\n", result);  // ����� 7

    return 0;
}
