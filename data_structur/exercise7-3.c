#include <stdio.h>  //printf�Լ��� ����
#include <stdlib.h> //malloc, free, exit�Լ��� ����

typedef int element;    //element�� int������ ����� �� �ְ���

// ���� ����Ʈ ��� ����
typedef struct ListNode {
    element data;   //��忡 data�� ����
    struct ListNode* link;  //���� ��带 ����Ű�� ������
} ListNode; //����ü �̸�

// ����Ʈ�� ����ϴ� �Լ�
void print_list(ListNode* head) {
    if (head == NULL) return;   //head�� ��������� �ƹ��͵� ������� �ʰ� ����

    ListNode* p = head; //���� ��带 ����Ű�� ������ ,head�������� �����Ѵ�
    do {
        printf("%d -> ", p->data);  //���� ������ ���
        p = p->link;                //���� ���� �̵�
    } while (p != head);    //�ٽ� head�� ���ƿö� ���� �ݺ�, ���� ����Ʈ���� �� �� �ִ�.
    printf("(head)\n");     // ��ȯ �� ǥ��
}

// �� �տ� �����ϴ� �Լ�
ListNode* insert_ListNode(ListNode* head, element data) {   
    ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));  // �� ��� ���� �޸� �Ҵ�
    if (newnode == NULL) {     //�޸� �Ҵ� ���н�  ���� �޽��� ���
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1);        //����
    }
    newnode->data = data;  //�� ��忡 �����Ͱ� ����

    if (head == NULL) {
        // ù ����� ��� �ڱ� �ڽ��� ����Ŵ
        newnode->link = newnode;  //�ڱ� �ڽ��� ����Ű�� ��������Ʈ
        head = newnode;        //head�� �� ��带 ����Ű����
    }
    else {
        // �� ��带 head ������ ����
        newnode->link = head->link;    //�� ��尡 ���� ù ��° ��带 ����Ŵ
        head->link = newnode;          //���� ������ ��尡 �� ��带 ����Ŵ
    }
    return head;  // ����� head ��ȯ
}

// ����Ʈ���� �����͸� ���� ��带 ã�� �Լ�
ListNode* search_ListNode(ListNode* head, element data) {
    if (head == NULL) return NULL;  //head���� NULL�̸� NULL��ȯ

    ListNode* p = head;     //head�������� ã�� ����
    do {
        if (p->data == data)
            return p;  // ã�� ��� �ش� ��� ��ȯ
        p = p->link;    //���� ���� �̵�
    } while (p != head);

    return NULL;  // �� ã�� ��� NULL��ȯ
}

// ���� ���� ����Ʈ�� ��� ��带 �����ϴ� �Լ�
void free_list(ListNode* head) {
    if (head == NULL) return;  // ����Ʈ�� ��� ������ �ٷ� ����

    ListNode* p = head->link;  // �� ��° ������ ���� 
    ListNode* temp;

    while (p != head) {
        temp = p;          // ���� ��带 �ӽ÷� ����
        p = p->link;       // ���� ���� �̵�
        free(temp);        // ���� ��� �޸� ����
    }

    free(head);  // ���������� head ��� ����
}

// ���� �Լ�
int main(void) {
    ListNode* head = NULL;      //head ������ NULL�� �ʱ�ȭ

    // ��� ���� (�� �տ� ����)
    head = insert_ListNode(head, 1);        //1����
    head = insert_ListNode(head, 2);        //2����
    head = insert_ListNode(head, 3);        //3����
    head = insert_ListNode(head, 4);        //4����
    head = insert_ListNode(head, 5);        //5����

    // ����Ʈ ���
    printf("���� ���� ����Ʈ ���:\n");
    print_list(head);  

    // search �׽�Ʈ
    element key = 3; //ã�� ��: 3
    ListNode* found = search_ListNode(head, key);
    if (found != NULL) {
        printf("��� %d�� ã�ҽ��ϴ�:", key);   //ã���� ���
    }
    else {
        printf("��� %d�� ����Ʈ�� �����ϴ�.\n", key); //�� ã���� ���
    }
    free_list(head); //��� �޸� ����
    return 0;   //���α׷� ����
}
