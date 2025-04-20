// 표준 입출력 및 동적 메모리 할당을 위한 헤더 파일 포함
#include<stdio.h>  // printf, scanf 등의 입출력 함수 사용
#include<stdlib.h> // malloc, free 등의 동적 메모리 관리 함수 사용

// 정수형 데이터를 저장하는 노드 정의
typedef int element; // 리스트 노드의 데이터 타입을 정수형으로 지정

// 연결 리스트의 노드 구조체 정의
typedef struct ListNode {
    element data;            // 노드가 저장하는 데이터
    struct ListNode* link;   // 다음 노드를 가리키는 포인터
} ListNode;

// 리스트의 모든 항목을 출력하는 함수
void print_list(ListNode* head) {
    ListNode* p; // 순회할 노드 포인터 선언

    if (head == NULL) return; // 리스트가 비어있다면 출력하지 않고 종료

    p = head->link; // 첫 번째 노드의 포인터를 가져옴
    do {
        printf("%d->", p->data); // 현재 노드의 데이터를 출력
        p = p->link; // 다음 노드로 이동
    } while (p != head); // 마지막 노드까지 순회

    printf("%d", p->data); // 마지막 노드의 데이터 출력
}

// 리스트의 맨 앞에 새 노드를 삽입하는 함수
ListNode* insert_first(ListNode* head, element data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode)); // 새로운 노드를 동적 할당
    node->data = data; // 새 노드에 데이터 저장

    if (head == NULL) { // 리스트가 비어있다면
        head = node; // head를 새 노드로 설정
        node->link = head; // 새 노드가 자기 자신을 가리키게 설정
    }
    else {
        node->link = head->link; // 새 노드가 기존 첫 번째 노드를 가리키도록 설정
        head->link = node; // 기존 마지막 노드가 새 노드를 가리키도록 설정
    }

    return head; // 변경된 head 반환
}

// 리스트의 맨 뒤에 새 노드를 삽입하는 함수
ListNode* insert_last(ListNode* head, element data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode)); // 새로운 노드를 동적 할당
    node->data = data; // 새 노드에 데이터 저장

    if (head == NULL) { // 리스트가 비어있다면
        head = node; // head를 새 노드로 설정
        node->link = head; // 새 노드가 자기 자신을 가리키게 설정
    }
    else {
        node->link = head->link; // 새 노드가 기존 첫 번째 노드를 가리키도록 설정
        head->link = node; // 기존 마지막 노드가 새 노드를 가리키도록 설정
        head = node; // head를 새 노드로 변경
    }

    return head; // 변경된 head 반환
}

// 원형 연결 리스트를 테스트하는 프로그램의 메인 함수
int main(void) {
    ListNode* head = NULL; // 리스트의 초기 상태를 NULL로 설정

    // 리스트에 요소를 추가: 10->20->30->40 순서대로 삽입
    head = insert_first(head, 20); // 20을 리스트의 첫 번째로 삽입
    head = insert_last(head, 30); // 30을 리스트의 마지막에 삽입
    head = insert_last(head, 40); // 40을 리스트의 마지막에 삽입
    head = insert_first(head, 10); // 10을 리스트의 첫 번째로 삽입

    print_list(head); // 리스트의 모든 요소를 출력

    return 0; // 프로그램 정상 종료
}