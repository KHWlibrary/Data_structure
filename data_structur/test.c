#include<stdio.h>
#include<stdlib.h>

typedef struct LinkNode
{
    int data;
    struct LinkNode* link;
} LinkNode;

// ��� �߰� �Լ�
LinkNode* insert_node(LinkNode* head, int value)
{
    LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
    p->data = value;
    p->link = head;
    head = p;

    return head;
}

// Ȧ����° ��� ���� �Լ�
LinkNode* delete_odd(LinkNode* head)
{
    // ù ��° ��尡 ���ų� �� ��° ��尡 ���ٸ� ������ ��尡 ����
    if (head == NULL || head->link == NULL) {
        return head;
    }

    LinkNode* temp = head;
    LinkNode* prev = NULL;

    // ù ��° ��带 �ǳʶٰ� �� ��° ������ ����
    temp = temp->link;
    head = temp;  // �� ��° ��带 head�� ����

    // Ȧ����° ��带 ���� (�� ĭ�� �ǳʶ�)
    while (temp != NULL && temp->link != NULL)
    {
        prev = temp;
        temp = temp->link->link;  // �� ĭ �ǳ� �ٱ�
        prev->link = temp;  // ���� ��尡 ���� ��带 ����Ű�� ��
    }

    return head;
}

// ����Ʈ ��� �Լ�
void print_list(LinkNode* head) {
    LinkNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}

// �޸� ���� �Լ�
void free_list(LinkNode* head) {
    LinkNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->link;
        free(temp);
    }
}

int main(void)
{
    LinkNode* head = NULL;

    // ��� �߰�
    head = insert_node(head, 1);
    head = insert_node(head, 2);
    head = insert_node(head, 3);
    head = insert_node(head, 4);
    head = insert_node(head, 5);
    head = insert_node(head, 6);
    head = insert_node(head, 7);
    head = insert_node(head, 8);

    // ���� �� ����Ʈ ���
    printf("���� �� ����Ʈ : \n");
    print_list(head);

    // Ȧ����° ��� ����
    head = delete_odd(head);

    // ���� �� ����Ʈ ���
    printf("���� �� ����Ʈ : \n");
    print_list(head);

    // �޸� ����
    free_list(head);

    return 0;
}
