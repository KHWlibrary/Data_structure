#include <stdio.h>  // printf �Լ��� ����
#include <stdlib.h> // malloc, free, exit �Լ��� ����

typedef int element;    // element�� int������ ����� �� �ְ���

// ���� ����Ʈ ��� ����
typedef struct ListNode {
    element data;   // ��忡 data�� ����
    struct ListNode* link;  // ���� ��带 ����Ű�� ������
} ListNode; // ����ü �̸�

// ����Ʈ�� ����ϴ� �Լ�
void print_list(ListNode* head) {
    if (head == NULL) return;   // head�� ��������� �ƹ��͵� ������� �ʰ� ����

    ListNode* p = head; // ���� ��带 ����Ű�� ������, head�������� �����Ѵ�
    // do while�� ����� ��� ��带 �ϳ��� ����ϰ� ���� ���� �Ѿ�鼭
    // ��� ����ϴٰ� head�� ���ƿ��� do while ��¹��� ����������.
    do {
        printf("%d -> ", p->data);  // ���� ������ ���
        p = p->link;                // ���� ���� �̵�
    } while (p != head);    // �ٽ� head�� ���ƿö� ���� �ݺ�
    printf("(head)\n");     // ��ȯ �� ǥ��
}

// �� �տ� �����ϴ� �Լ� (������)
ListNode* insert_ListNode(ListNode* head, element data) {
    ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
    if (newnode == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1);
    }
    newnode->data = data;

    if (head == NULL) { // ����Ʈ�� ������� ��
        newnode->link = newnode; // �ڱ� �ڽ��� ����Ŵ
        head = newnode;
    }
    else { // ����Ʈ�� ��尡 ���� ��
        ListNode* tail = head;
        // ������ ���(tail) ã��: tail->link�� ���� head�� ����Ű�� ���
        while (tail->link != head) {
            tail = tail->link;
        }
        newnode->link = head;   // �� ��尡 ���� head�� ����Ŵ
        tail->link = newnode; // ������ ��尡 �� ��带 ����Ŵ
        head = newnode;       // head�� �� ���� ����
    }
    return head; // ����� head ��ȯ
}


// ����Ʈ���� �����͸� ���� ��带 ã�� �Լ�
ListNode* search_ListNode(ListNode* head, element data) {
    if (head == NULL) return NULL;  // head���� NULL�̸� NULL��ȯ

    ListNode* p = head;     // head�������� ã�� ����
    // ã�� data���� �Է��� data ���� ������ �� ��带 ��ȯ�Ѵ�.
    // ã�� ��� ��带 Ȯ���ߴµ� ã�� �� �ϸ� NULL�� ��ȯ�Ѵ�.
    do {
        if (p->data == data)
            return p;  // ã�� ��� �ش� ��� ��ȯ
        p = p->link;    // ���� ���� �̵�
    } while (p != head); // �ٽ� head�� ���ƿ� ������ �ݺ�

    return NULL;  // �� ã�� ��� NULL��ȯ
}

// ���� ���� ����Ʈ�� ��� ��带 �����ϴ� �Լ�
void free_list(ListNode* head) {
    if (head == NULL) return;  // ����Ʈ�� ��� ������ �ٷ� ����

    ListNode* p = head->link;  // �� ��° ������ ����
    ListNode* start_node = head; // ���� ���� ������ ���� ���� ��� ����

    // head�� �ƴ� �ٸ� ������ ���� ����
    while (p != start_node) {
        ListNode* temp = p; // ���� ��带 �ӽ� ����
        p = p->link;      // ���� ���� �̵�
        // printf("Freeing node with data: %d\n", temp->data); // ������ ��� (�ʿ�� �ּ� ����)
        free(temp);       // �ӽ� ����� ��� �޸� ����
    }

    // ���������� head ��� ����
    // printf("Freeing head node with data: %d\n", start_node->data); // ������ ��� (�ʿ�� �ּ� ����)
    free(start_node);
}


// ���� �Լ�
int main(void) {
    ListNode* head = NULL;      // head ������ NULL�� �ʱ�ȭ

    // ��� ���� (�� �տ� ����) �� �� �ܰ� ���
    printf("Insert 1: ");
    head = insert_ListNode(head, 1);        // 1����
    print_list(head);                       // ���: 1 -> (head)

    printf("Insert 2: ");
    head = insert_ListNode(head, 2);        // 2����
    print_list(head);                       // ���: 2 -> 1 -> (head)

    printf("Insert 3: ");
    head = insert_ListNode(head, 3);        // 3����
    print_list(head);                       // ���: 3 -> 2 -> 1 -> (head)

    printf("Insert 4: ");
    head = insert_ListNode(head, 4);        // 4����
    print_list(head);                       // ���: 4 -> 3 -> 2 -> 1 -> (head)

    printf("Insert 5: ");
    head = insert_ListNode(head, 5);        // 5����
    print_list(head);                       // ���: 5 -> 4 -> 3 -> 2 -> 1 -> (head)

    // ���� ����Ʈ ���
    printf("\n���� ���� ���� ����Ʈ ���:\n");
    print_list(head);                       // ���: 5 -> 4 -> 3 -> 2 -> 1 -> (head)

    // search �׽�Ʈ (ã�� ���� 5�� ����)
    element key = 5; // ã�� ��: 5
    printf("\nSearching for node %d...\n", key);
    ListNode* found = search_ListNode(head, key);
    if (found != NULL) {
        printf("��� %d�� ã�ҽ��ϴ�.\n", key);   // ã���� ��� (�ٹٲ� �߰�)
    }
    else {
        printf("��� %d�� ����Ʈ�� �����ϴ�.\n", key); // �� ã���� ���
    }

    printf("\nFreeing list memory...\n");
    free_list(head); // ��� �޸� ����
    head = NULL; // ���� �� head�� NULL�� �����ϴ� ���� �����մϴ�.
    printf("List freed.\n");

    return 0;   // ���α׷� ����
} 