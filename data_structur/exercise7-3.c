//Ư������ ã�� �Լ�search()�� �ۼ��ϰ� �׽�Ʈ�ϴ� ���α׷�
#include <stdio.h>  //printf�Լ��� ����
#include <stdlib.h> //malloc, free, exit�Լ��� ����

typedef int element;    //element�� int������ ����� �� �ְ���

// ���� ����Ʈ ��� ����
typedef struct ListNode {
    element data;   //��忡 ������ data�� 
    struct ListNode* link;  //���� ��带 ����Ű�� ������
} ListNode; //����ü �̸�

// ����Ʈ�� ����ϴ� �Լ�
void print_list(ListNode* head) {
    if (head == NULL) return;   //head�� ��������� �ƹ��͵� ������� �ʰ� ����

    ListNode* p = head; //���� ��带 ����Ű�� ������ ,head�������� �����Ѵ�
    //do while�� ����� ��� ��带 �ϳ��� ����ϰ� ���� ���� �Ѿ�鼭
    //��� ����ϴٰ� head�� ���ƿ��� do while ��¹��� ����������. 
    do {
        printf("%d -> ", p->data);  //���� ������ ���
        p = p->link;                //���� ���� �̵�
    } while (p != head);    //�ٽ� head�� ���ƿö� ���� �ݺ�, 
    printf("(head)\n");     // ��ȯ �� ǥ��
}

// �� �տ� �����ϴ� �Լ�
ListNode* insert_ListNode(ListNode* head, element data) {   
    ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));  // �� ��忡 ���� �޸� �Ҵ�
    if (newnode == NULL) {     //�޸� �Ҵ����� �� �� ���  ���� �޽��� ���
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1);        //����
    }
    newnode->data = data;  //�� ��忡 �����Ͱ� ����

    //head�� �ƹ��͵� ���� �� ù ����̱⶧�� ���ο� ��带 ������ְ�
    //�ڱ� �ڽ��� ����Ű�� �Ͽ� ��������Ʈ�� �����.
    if (head == NULL) {
        newnode->link = newnode;  //�ڱ� �ڽ��� ����Ű�� ��������Ʈ
        head = newnode;        //head�� �� ��带 ����Ű����
    }
    //
    else { // ����Ʈ�� ��尡 ���� ��
        ListNode* tail = head;
        //������ ���(tail) ã��         
        //tail->link�� head�� �ƴϸ� ��� �ݺ�����
        //tail->link�� head�̸� �ݺ��� ��������
        while (tail->link != head) {
            tail = tail->link;
        }
        newnode->link = head;   // �� ��尡 ���� head�� ����Ŵ
        tail->link = newnode; // ������ ��尡 �� ��带 ����Ŵ
        head = newnode;       // head�� �� ���� ����
    }
    return head;  // ����� head ��ȯ
}

// ����Ʈ���� �����͸� ���� ��带 ã�� �Լ�
ListNode* search_ListNode(ListNode* head, element data) {
    if (head == NULL) return NULL;  //head���� NULL�̸� NULL��ȯ

    ListNode* p = head;     //head�������� ã�� ����
    //ã�� data���� �Է��� data ���� ������ �� ��带 ��ȯ�Ѵ�.
    //ã�� ��� ��带 Ȯ���ߴµ� ã�� �� �ϸ� NULL�� ��ȯ�Ѵ�.
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
    ListNode* start_node = head; // ���� ���� ������ ���� ���� ��� ����

    // head�� �ƴ� �ٸ� ������ ���� ����
    while (p != start_node) {
        ListNode* temp = p; // ���� ��带 �ӽ� ����
        p = p->link;      // ���� ���� �̵�
        free(temp);       // �ӽ� ����� ��� �޸� ����
    }

    // ���������� head ��� ����
    free(start_node);
}

// ���� �Լ�
int main(void) {
    ListNode* head = NULL;      //head ������ NULL�� �ʱ�ȭ

    // ��� ���� (�� �տ� ����)
    printf("insert 1:");
    head = insert_ListNode(head, 1);        //1����   
    print_list(head);                       //��� �� 1->head
    printf("insert 2:");
    head = insert_ListNode(head, 2);        //2����
    print_list(head);                       //��� �� 2->1->head
    printf("insert 3:");
    head = insert_ListNode(head, 3);        //3����
    print_list(head);                       //��� �� 3->2->1->head
    printf("insert 4:");
    head = insert_ListNode(head, 4);        //4����
    print_list(head);                       //��� �� 4->3->2->1->head
    printf("insert 5:");
    head = insert_ListNode(head, 5);        //5����
    print_list(head);                       //��� �� 5->4->3->2->1->head
    // ����Ʈ ���
    printf("���� ���� ����Ʈ ���:\n");
    print_list(head);  

    // search �׽�Ʈ
    element key = 5; //ã�� ��: 3
    ListNode* found = search_ListNode(head, key);
    if (found != NULL) {
        printf("��� %d�� ã�ҽ��ϴ�:", key);   //ã���� ���
    }
    else {
        printf("��� %d�� ����Ʈ�� �����ϴ�.\n", key); //�� ã���� ���
    }
    free_list(head); //��� �޸� ����
    head = NULL;
    return 0;   //���α׷� ����
}
