#include <stdio.h>  // printf 함수에 쓰임
#include <stdlib.h> // malloc, free, exit 함수에 쓰임

typedef int element;    // element를 int형으로 사용할 수 있게함

// 연결 리스트 노드 정의
typedef struct ListNode {
    element data;   // 노드에 data값 저장
    struct ListNode* link;  // 다음 노드를 가리키는 포인터
} ListNode; // 구조체 이름

// 리스트를 출력하는 함수
void print_list(ListNode* head) {
    if (head == NULL) return;   // head에 비어있으면 아무것도 출력하지 않고 종료

    ListNode* p = head; // 현재 노드를 가리키는 포인터, head에서부터 시작한다
    // do while을 사용해 모든 노드를 하나씩 출력하고 다음 노드로 넘어가면서
    // 계속 출력하다가 head로 돌아오면 do while 출력문을 빠져나간다.
    do {
        printf("%d -> ", p->data);  // 현재 데이터 출력
        p = p->link;                // 다음 노드로 이동
    } while (p != head);    // 다시 head로 돌아올때 까지 반복
    printf("(head)\n");     // 순환 끝 표시
}

// 맨 앞에 삽입하는 함수 (수정됨)
ListNode* insert_ListNode(ListNode* head, element data) {
    ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
    if (newnode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    newnode->data = data;

    if (head == NULL) { // 리스트가 비어있을 때
        newnode->link = newnode; // 자기 자신을 가리킴
        head = newnode;
    }
    else { // 리스트에 노드가 있을 때
        ListNode* tail = head;
        // 마지막 노드(tail) 찾기: tail->link가 현재 head를 가리키는 노드
        while (tail->link != head) {
            tail = tail->link;
        }
        newnode->link = head;   // 새 노드가 기존 head를 가리킴
        tail->link = newnode; // 마지막 노드가 새 노드를 가리킴
        head = newnode;       // head를 새 노드로 갱신
    }
    return head; // 변경된 head 반환
}


// 리스트에서 데이터를 가진 노드를 찾는 함수
ListNode* search_ListNode(ListNode* head, element data) {
    if (head == NULL) return NULL;  // head값이 NULL이면 NULL반환

    ListNode* p = head;     // head에서부터 찾기 시작
    // 찾는 data값을 입력한 data 값이 같으면 그 노드를 반환한다.
    // 찾지 모든 노드를 확인했는데 찾지 못 하면 NULL로 반환한다.
    do {
        if (p->data == data)
            return p;  // 찾은 경우 해당 노드 반환
        p = p->link;    // 다음 노드로 이동
    } while (p != head); // 다시 head로 돌아올 때까지 반복

    return NULL;  // 못 찾은 경우 NULL반환
}

// 원형 연결 리스트의 모든 노드를 해제하는 함수
void free_list(ListNode* head) {
    if (head == NULL) return;  // 리스트가 비어 있으면 바로 종료

    ListNode* p = head->link;  // 두 번째 노드부터 시작
    ListNode* start_node = head; // 루프 종료 조건을 위해 시작 노드 저장

    // head가 아닌 다른 노드들을 먼저 해제
    while (p != start_node) {
        ListNode* temp = p; // 현재 노드를 임시 저장
        p = p->link;      // 다음 노드로 이동
        // printf("Freeing node with data: %d\n", temp->data); // 디버깅용 출력 (필요시 주석 해제)
        free(temp);       // 임시 저장된 노드 메모리 해제
    }

    // 마지막으로 head 노드 해제
    // printf("Freeing head node with data: %d\n", start_node->data); // 디버깅용 출력 (필요시 주석 해제)
    free(start_node);
}


// 메인 함수
int main(void) {
    ListNode* head = NULL;      // head 포인터 NULL로 초기화

    // 노드 삽입 (맨 앞에 삽입) 및 각 단계 출력
    printf("Insert 1: ");
    head = insert_ListNode(head, 1);        // 1삽입
    print_list(head);                       // 출력: 1 -> (head)

    printf("Insert 2: ");
    head = insert_ListNode(head, 2);        // 2삽입
    print_list(head);                       // 출력: 2 -> 1 -> (head)

    printf("Insert 3: ");
    head = insert_ListNode(head, 3);        // 3삽입
    print_list(head);                       // 출력: 3 -> 2 -> 1 -> (head)

    printf("Insert 4: ");
    head = insert_ListNode(head, 4);        // 4삽입
    print_list(head);                       // 출력: 4 -> 3 -> 2 -> 1 -> (head)

    printf("Insert 5: ");
    head = insert_ListNode(head, 5);        // 5삽입
    print_list(head);                       // 출력: 5 -> 4 -> 3 -> 2 -> 1 -> (head)

    // 최종 리스트 출력
    printf("\n최종 원형 연결 리스트 출력:\n");
    print_list(head);                       // 출력: 5 -> 4 -> 3 -> 2 -> 1 -> (head)

    // search 테스트 (찾는 값을 5로 변경)
    element key = 5; // 찾는 값: 5
    printf("\nSearching for node %d...\n", key);
    ListNode* found = search_ListNode(head, key);
    if (found != NULL) {
        printf("노드 %d를 찾았습니다.\n", key);   // 찾으면 출력 (줄바꿈 추가)
    }
    else {
        printf("노드 %d는 리스트에 없습니다.\n", key); // 못 찾으면 출력
    }

    printf("\nFreeing list memory...\n");
    free_list(head); // 모든 메모리 해제
    head = NULL; // 해제 후 head를 NULL로 설정하는 것이 안전합니다.
    printf("List freed.\n");

    return 0;   // 프로그램 종료
} 