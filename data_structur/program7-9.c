#include<stdio.h>
#include<stdlib.h>

// ������ ���� ����
typedef int element; // ���ÿ� ����� ����� ������ Ÿ���� int�� ����
typedef struct StackNode {
    element data; // ��忡 ����� ������
    struct StackNode* link; // ���� ��带 ����Ű�� ������
} StackNode;

typedef struct {
    StackNode* top; // ������ �ֻ�� ��带 ����Ű�� ������
} LinkedStacktype;

// ���� �ʱ�ȭ �Լ�
void init(LinkedStacktype* s) {
    s->top = NULL; // ������ top�� NULL�� �����Ͽ� ���� �������� �ʱ�ȭ
}

// ���� ���¸� Ȯ���ϴ� �Լ�
int is_empty(LinkedStacktype* s) {
    return (s->top == NULL); // top�� NULL�̸� ������ ��������� �ǹ�
}

// ��ȭ ���¸� Ȯ���ϴ� �Լ� (���� ����Ʈ������ �׻� 0 ��ȯ)
int is_full(LinkedStacktype* s) {
    return 0; // ���� ����Ʈ ��� ������ �޸𸮰� ����ϴ� �� ��ȭ ���°� ����
}

// ���ÿ� ��Ҹ� �����ϴ� �Լ�
void push(LinkedStacktype* s, element item) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode)); // �� ��� ���� �Ҵ�
    temp->data = item; // �� ��忡 ������ ����
    temp->link = s->top; // �� ��尡 ���� top ��带 ����Ű���� ����
    s->top = temp; // top�� �� ���� ����
}

// ���� ������ ����ϴ� �Լ�
void print_stack(LinkedStacktype* s) {
    for (StackNode* p = s->top; p != NULL; p = p->link) // top���� ������ ��ũ�� ���󰡸� ������ ���
        printf("%d->", p->data);
    printf("NULL\n"); // ������ �� ǥ��
}

// ���ÿ��� ��Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
element pop(LinkedStacktype* s) {
    if (is_empty(s)) { // ������ ����ִ��� Ȯ��
        fprintf(stderr, "������ �������\n"); // ���� �޽��� ���
        exit(1); // ���α׷� ����
    }
    else {
        StackNode* temp = s->top; // ������ ��带 ����Ŵ
        int data = temp->data; // ������ ����� �����͸� ����
        s->top = s->top->link; // top�� ���� ���� ����
        free(temp); // ������ ��� �޸� ����
        return data; // ���ŵ� ������ ��ȯ
    }
}

// ������ �ֻ�� ��Ҹ� ��ȯ�ϴ� �Լ�
element peak(LinkedStacktype* s) {
    if (is_empty(s)) { // ������ ����ִ��� Ȯ��
        fprintf(stderr, "������ �������\n"); // ���� �޽��� ���
        exit(1); // ���α׷� ����
    }
    else {
        return s->top->data; // �ֻ�� ��� ��ȯ
    }
}

// ���� �Լ�
int main(void) {
    LinkedStacktype s; // ���� ����Ʈ ��� ���� ����
    init(&s); // ���� �ʱ�ȭ
    push(&s, 1); print_stack(&s); // ���ÿ� 1 ���� �� ���
    push(&s, 2); print_stack(&s); // ���ÿ� 2 ���� �� ���
    push(&s, 3); print_stack(&s); // ���ÿ� 3 ���� �� ���
    pop(&s); print_stack(&s); // ���ÿ��� ��� ���� �� ���
    pop(&s); print_stack(&s); // ���ÿ��� ��� ���� �� ���
    pop(&s); print_stack(&s); // ���ÿ��� ��� ���� �� ���
    return 0; // ���α׷� ����
}