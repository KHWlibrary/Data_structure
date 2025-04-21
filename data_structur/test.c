#include <stdio.h>
#include <stdlib.h>

typedef int element;

// 연결 리스트 노드 정의
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// 리스트를 출력하는 함수
void print_list(ListNode* head) {
    if (head == NULL) return;

    ListNode* p = head;
    do {
        printf("%d -> ", p->data);
        p = p->link;
    } while (p != head);
    printf("(head)\n");
}

// 맨 앞에 삽입하는 함수
ListNode* insert_ListNode(ListNode* head, element data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));  // 새 노드 동적 할당
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    node->data = data;

    if (head == NULL) {
        // 첫 노드인 경우 자기 자신을 가리킴
        node->link = node;
        head = node;
    }
    else {
        // 새 노드를 head 다음에 삽입
        node->link = head->link;
        head->link = node;
    }
    return head;  // 변경된 head 반환
}

// 리스트에서 데이터를 가진 노드를 찾는 함수
ListNode* search_ListNode(ListNode* head, element data) {
    if (head == NULL) return NULL;

    ListNode* p = head;
    do {
        if (p->data == data)
            return p;  // 찾은 경우 해당 노드 반환
        p = p->link;
    } while (p != head);

    return NULL;  // 못 찾은 경우
}

// 메인 함수
int main(void) {
    ListNode* head = NULL;

    // 노드 삽입 (맨 앞에 삽입)
    head = insert_ListNode(head, 1);
    head = insert_ListNode(head, 2);
    head = insert_ListNode(head, 3);
    head = insert_ListNode(head, 4);
    head = insert_ListNode(head, 5);

    // 리스트 출력
    printf("원형 연결 리스트 출력:\n");
    print_list(head);

    // search 테스트
    element key = 3;
    ListNode* found = search_ListNode(head, key);
    if (found != NULL) {
        printf("노드 %d를 찾았습니다:", key);
    }
    else {
        printf("노드 %d는 리스트에 없습니다.\n", key);
    }

    return 0;
}
