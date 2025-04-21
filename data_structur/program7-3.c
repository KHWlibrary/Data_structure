// ǥ�� ����� �� ���� �޸� �Ҵ��� ���� ��� ���� ����
#include<stdio.h>  // printf, scanf ���� ����� �Լ� ���
#include<stdlib.h> // malloc, free ���� ���� �޸� ���� �Լ� ���

// ������ �����͸� �����ϴ� ��� ����
typedef int element; // ����Ʈ ����� ������ Ÿ���� ���������� ����

// ���� ����Ʈ�� ��� ����ü ����
typedef struct ListNode {
    element data;            // ��尡 �����ϴ� ������
    struct ListNode* link;   // ���� ��带 ����Ű�� ������
} ListNode;

// ����Ʈ�� ��� �׸��� ����ϴ� �Լ�
void print_list(ListNode* head) {
    ListNode* p; // ��ȸ�� ��� ������ ����

    if (head == NULL) return; // ����Ʈ�� ����ִٸ� ������� �ʰ� ����

    p = head->link; // ù ��° ����� �����͸� ������
    do {
        printf("%d->", p->data); // ���� ����� �����͸� ���
        p = p->link; // ���� ���� �̵�
    } while (p != head); // ������ ������ ��ȸ

    printf("%d", p->data); // ������ ����� ������ ���
}

// ����Ʈ�� �� �տ� �� ��带 �����ϴ� �Լ�
ListNode* insert_first(ListNode* head, element data) {
    ListNode* newnode = (ListNode*)malloc(sizeof(ListNode)); // ���ο� ��带 ���� �Ҵ�
    newnode->data = data; // �� ��忡 ������ ����

    if (head == NULL) { // ����Ʈ�� ����ִٸ�
        head = newnode; // head�� �� ���� ����
        newnode->link = head; // �� ��尡 �ڱ� �ڽ��� ����Ű�� ����
    }
    else {
        newnode->link = head->link; // �� ��尡 ���� ù ��° ��带 ����Ű���� ����
        head->link = newnode; // ���� ������ ��尡 �� ��带 ����Ű���� ����
    }
    return head; // ����� head ��ȯ
}

// ����Ʈ�� �� �ڿ� �� ��带 �����ϴ� �Լ�
ListNode* insert_last(ListNode* head, element data) {
    ListNode* newnode = (ListNode*)malloc(sizeof(ListNode)); // ���ο� ��带 ���� �Ҵ�
    newnode->data = data; // �� ��忡 ������ ����

    if (head == NULL) { // ����Ʈ�� ����ִٸ�
        head = newnode; // head�� �� ���� ����
        newnode->link = head; // �� ��尡 �ڱ� �ڽ��� ����Ű�� ����
    }
    else {
        newnode->link = head->link; // �� ��尡 ���� ù ��° ��带 ����Ű���� ����
        head->link = newnode; // ���� ������ ��尡 �� ��带 ����Ű���� ����
        head = newnode; // head�� �� ���� ����
    }
    return head; // ����� head ��ȯ
}

// ���� ���� ����Ʈ�� �׽�Ʈ�ϴ� ���α׷��� ���� �Լ�
int main(void) {
    ListNode* head = NULL; // ����Ʈ�� �ʱ� ���¸� NULL�� ����

    // ����Ʈ�� ��Ҹ� �߰�: 10->20->30->40 ������� ����
    head = insert_first(head, 20); // 20�� ����Ʈ�� ù ��°�� ����
    head = insert_last(head, 30); // 30�� ����Ʈ�� �������� ����
    head = insert_last(head, 40); // 40�� ����Ʈ�� �������� ����
    head = insert_first(head, 10); // 10�� ����Ʈ�� ù ��°�� ����

    print_list(head); // ����Ʈ�� ��� ��Ҹ� ���

    return 0; // ���α׷� ���� ����
}