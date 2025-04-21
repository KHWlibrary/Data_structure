#include <stdio.h>
#include <stdlib.h>

typedef int element;

// ���� ����Ʈ ��� ����
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// ����Ʈ�� ����ϴ� �Լ�
void print_list(ListNode* head) {
    if (head == NULL) return;

    ListNode* p = head;
    do {
        printf("%d -> ", p->data);
        p = p->link;
    } while (p != head);
    printf("(head)\n");
}

// �� �տ� �����ϴ� �Լ�
ListNode* insert_ListNode(ListNode* head, element data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));  // �� ��� ���� �Ҵ�
    if (node == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1);
    }
    node->data = data;

    if (head == NULL) {
        // ù ����� ��� �ڱ� �ڽ��� ����Ŵ
        node->link = node;
        head = node;
    }
    else {
        // �� ��带 head ������ ����
        node->link = head->link;
        head->link = node;
    }
    return head;  // ����� head ��ȯ
}

// ����Ʈ���� �����͸� ���� ��带 ã�� �Լ�
ListNode* search_ListNode(ListNode* head, element data) {
    if (head == NULL) return NULL;

    ListNode* p = head;
    do {
        if (p->data == data)
            return p;  // ã�� ��� �ش� ��� ��ȯ
        p = p->link;
    } while (p != head);

    return NULL;  // �� ã�� ���
}

// ���� �Լ�
int main(void) {
    ListNode* head = NULL;

    // ��� ���� (�� �տ� ����)
    head = insert_ListNode(head, 1);
    head = insert_ListNode(head, 2);
    head = insert_ListNode(head, 3);
    head = insert_ListNode(head, 4);
    head = insert_ListNode(head, 5);

    // ����Ʈ ���
    printf("���� ���� ����Ʈ ���:\n");
    print_list(head);

    // search �׽�Ʈ
    element key = 3;
    ListNode* found = search_ListNode(head, key);
    if (found != NULL) {
        printf("��� %d�� ã�ҽ��ϴ�:", key);
    }
    else {
        printf("��� %d�� ����Ʈ�� �����ϴ�.\n", key);
    }

    return 0;
}
