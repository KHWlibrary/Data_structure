#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

// ���� ����ü ����
typedef struct {
    char data[MAX_SIZE];  // ���� ����
    int count[MAX_SIZE];  // ������ ������ �����ϴ� �迭
    int top;              // ������ ����� ��Ÿ���� ����
} Stack;

// ���� �ʱ�ȭ �Լ�
void initStack(Stack* stack) {
    stack->top = -1;  // ������ ������� �� top�� -1
}

// ���ÿ� ��Ҹ� �߰��ϴ� �Լ�
void push(Stack* stack, char c, int cnt) {
    if (stack->top < MAX_SIZE - 1) {
        stack->top++;
        stack->data[stack->top] = c;
        stack->count[stack->top] = cnt;
    }
}

// ���ÿ��� ��Ҹ� �����ϴ� �Լ�
void pop(Stack* stack) {
    if (stack->top >= 0) {
        stack->top--;
    }
}

// ������ top ��Ҹ� ��ȯ�ϴ� �Լ�
char peekChar(Stack* stack) {
    return stack->data[stack->top];
}

// ������ top�� �ִ� ������ ��ȯ�ϴ� �Լ�
int peekCount(Stack* stack) {
    return stack->count[stack->top];
}

// ���ڿ� ���� �Լ�
void compressString(const char* input) {
    Stack stack;
    initStack(&stack);

    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        if (stack.top == -1 || peekChar(&stack) != input[i]) {
            push(&stack, input[i], 1);  // ���ο� ���ڸ� ���ÿ� ����
        }
        else {
            stack.count[stack.top]++;  // ���ӵ� ������ ���� ����
        }
    }

    // ����� ���ڿ� ���
    for (int i = 0; i <= stack.top; i++) {
        printf("%d%c", stack.count[i], stack.data[i]);
    }
    printf("\n");
}

int main() {
    char input[MAX_SIZE];

    // ����ڷκ��� ���ڿ� �Է� �ޱ�
    printf("���ڿ��� �Է��ϼ���: ");
    scanf("%s", input);

    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = tolower(input[i]);  // �빮�ڸ� �ҹ��ڷ� ��ȯ
    }

    // ����� ���ڿ� ���
    printf("����� ���ڿ�: ");
    compressString(input);

    return 0;
}
