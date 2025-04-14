#include<stdio.h>
#include<stdlib.h>

typedef struct LinkNode
{
    int data;
    struct LinkNode* link;
} LinkNode;

// 노드 추가 함수
LinkNode* insert_node(LinkNode* head, int value)
{
    LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
    p->data = value;
    p->link = head;
    head = p;

    return head;
}

// 홀수번째 노드 삭제 함수
LinkNode* delete_odd(LinkNode* head)
{
    // 첫 번째 노드가 없거나 두 번째 노드가 없다면 삭제할 노드가 없음
    if (head == NULL || head->link == NULL) {
        return head;
    }

    LinkNode* temp = head;
    LinkNode* prev = NULL;

    // 첫 번째 노드를 건너뛰고 두 번째 노드부터 시작
    temp = temp->link;
    head = temp;  // 두 번째 노드를 head로 설정

    // 홀수번째 노드를 삭제 (두 칸씩 건너뜀)
    while (temp != NULL && temp->link != NULL)
    {
        prev = temp;
        temp = temp->link->link;  // 두 칸 건너 뛰기
        prev->link = temp;  // 이전 노드가 현재 노드를 가리키게 함
    }

    return head;
}

// 리스트 출력 함수
void print_list(LinkNode* head) {
    LinkNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}

// 메모리 해제 함수
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

    // 노드 추가
    head = insert_node(head, 1);
    head = insert_node(head, 2);
    head = insert_node(head, 3);
    head = insert_node(head, 4);
    head = insert_node(head, 5);
    head = insert_node(head, 6);
    head = insert_node(head, 7);
    head = insert_node(head, 8);

    // 변경 전 리스트 출력
    printf("변경 전 리스트 : \n");
    print_list(head);

    // 홀수번째 노드 삭제
    head = delete_odd(head);

    // 변경 후 리스트 출력
    printf("변경 후 리스트 : \n");
    print_list(head);

    // 메모리 해제
    free_list(head);

    return 0;
}
