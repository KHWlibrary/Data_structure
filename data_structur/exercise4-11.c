//���Ŀ� �ִ� ��ȣ�� ��ȣ�� ����ϴ� ���α׷��� �ۼ��϶�.
//���� ��ȣ�� ���� �� ���� Ȱȣ ��ȣ�� �ϳ��� �����Ѵ�.
//������ ��ȣ�� ������ ��Ī�Ǵ� ���� ��ȣ ��ȣ�� ����Ѵ�

#include <stdio.h>      // ǥ�� ����� �Լ� ����� ���� ��� ���� (ex: printf, fgets ��)
#include <stdlib.h>     // �Ϲ����� ��ƿ��Ƽ �Լ��� ��� ���� ��� (ex: exit �Լ� ��)

//===== ���� �ڵ��� ���� =====
// ������ �����͸� ���߿� ���� ���� ���� ������ LIFO(Last In First Out) �����Դϴ�.
// ��ȣ�� ¦�� ���߰ų�, ��ø�� �����ϴ� �� �����մϴ�.

#define MAX_STACK_SIZE 100         // ������ �ִ� �뷮�� 100���� ����
typedef char element;              // ���ÿ� ����� �ڷ����� char(����)�� ����

// ���� ����ü ����
typedef struct {
    element data[MAX_STACK_SIZE]; // ���� �����͸� ������ �迭
    int top;                      // ������ ���� ����� �ε����� ����
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
    s->top = -1;  // ������ ��� ������ ��Ÿ���� ���� top�� -1�� ����
}

// ������ ������� Ȯ���ϴ� �Լ�
int is_empty(StackType* s)
{
    return (s->top == -1); // top�� -1�̸� ������ ��� �ִ� ����
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1)); // top�� �迭�� ������ �ε����� ��ȭ ����
}

// ���ÿ� ���� �߰��ϴ� �Լ� (push)
void push(StackType* s, element item)
{
    if (is_full(s)) { // ������ ���� á���� Ȯ��
        fprintf(stderr, "���� ��ȭ ����\n"); // ���� �޽��� ���
        return; // ���� �ߴ�
    }
    else
        s->data[++(s->top)] = item; // top�� ������Ų ��, �ش� ��ġ�� item ����
}

// ���ÿ��� ���� �����ϰ� ��ȯ�ϴ� �Լ� (pop)
element pop(StackType* s)
{
    if (is_empty(s)) { // ������ ��� �ִ��� Ȯ��
        fprintf(stderr, "���� ���� ����\n"); // ���� �޽��� ���
        exit(1); // ���α׷� ������ ����
    }
    else
        return s->data[(s->top)--]; // top ��ġ�� ���� ��ȯ�ϰ� top�� ���ҽ�Ŵ
}

// ������ �ֻ�� ���� ��ȯ�ϵ� �������� �ʴ� �Լ� (peek)
element peek(StackType* s)
{
    if (is_empty(s)) { // ������ ��� �ִ��� Ȯ��
        fprintf(stderr, "���ð��鿡��\n"); // ���� �޽��� ���
        exit(1); // ���α׷� ������ ����
    }
    else
        return s->data[s->top]; // top ��ġ�� ���� ��ȯ�� (���� X)
}
//===== ���� �ڵ��� �� =====


// �Էµ� ��ȣ ���ڿ��� �м��ϰ� ���ڷ� ��ø ������ ǥ���ϴ� �Լ�
void process_parentheses(char* expr) {
    StackType stack;         // ��ȣ ó���� ���� ���� ����
    init_stack(&stack);      // ���� �ʱ�ȭ (top = -1)
    int current_value = 0;   // ��ø ������ ǥ���� ����, ���� �ٱ��� 1���� ����

    // ���ڿ��� �� ���ھ� Ž��
    for (int i = 0; expr[i] != '\0'; i++) {
        // ���� ��ȣ '('�� ������ ��
        if (expr[i] == '(') {
            // ���� ���� ���¸� ���ÿ� ���� (���߿� �ݴ� ��ȣ���� ����)
            push(&stack, current_value);
            current_value += 1; // ��ȣ�� �ϳ� �� ��������Ƿ� ���� ����
            printf("%d", current_value); // ������ ���� ���
        }
        // �ݴ� ��ȣ ')'�� ������ ��
        else if (expr[i] == ')') {
            // ������ ��� ���� ������
            if (!is_empty(&stack)) {
                // ���ÿ��� ���� ���ڸ� ���� ���� ���ڷ� ����
                current_value = pop(&stack);
                printf("%d", current_value); // ���� ���� ���
            }
            // ������ ��� ������ ��ȣ ������ �߸��� ���̹Ƿ�
            else {
                printf(" "); // ���� ���
                return; // �Լ� ����
            }
        }
    }
}

// ���� �Լ�
int main()
{
    char expr[MAX_STACK_SIZE];  // ��ȣ ���ڿ��� ������ �迭 ����

    printf("��ȣ�� �Է½ÿ�: "); // ����ڿ��� �Է� �ȳ� ���
    fgets(expr, MAX_STACK_SIZE, stdin); // ����ڷκ��� ��ȣ ���ڿ� �Է� ����

    process_parentheses(expr); // ��ȣ �м� �Լ� ȣ��

    return 0; // ���α׷� ����
}
 