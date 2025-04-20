#include<stdio.h>
#include<stdlib.h>

// 데이터 유형 정의
typedef int element; // 스택에 저장될 요소의 데이터 타입을 int로 정의
typedef struct StackNode {
    element data; // 노드에 저장된 데이터
    struct StackNode* link; // 다음 노드를 가리키는 포인터
} StackNode;

typedef struct {
    StackNode* top; // 스택의 최상단 노드를 가리키는 포인터
} LinkedStacktype;

// 스택 초기화 함수
void init(LinkedStacktype* s) {
    s->top = NULL; // 스택의 top을 NULL로 설정하여 공백 스택으로 초기화
}

// 공백 상태를 확인하는 함수
int is_empty(LinkedStacktype* s) {
    return (s->top == NULL); // top이 NULL이면 스택이 비어있음을 의미
}

// 포화 상태를 확인하는 함수 (연결 리스트에서는 항상 0 반환)
int is_full(LinkedStacktype* s) {
    return 0; // 연결 리스트 기반 스택은 메모리가 허용하는 한 포화 상태가 없음
}

// 스택에 요소를 삽입하는 함수
void push(LinkedStacktype* s, element item) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode)); // 새 노드 동적 할당
    temp->data = item; // 새 노드에 데이터 저장
    temp->link = s->top; // 새 노드가 기존 top 노드를 가리키도록 설정
    s->top = temp; // top을 새 노드로 갱신
}

// 스택 내용을 출력하는 함수
void print_stack(LinkedStacktype* s) {
    for (StackNode* p = s->top; p != NULL; p = p->link) // top부터 시작해 링크를 따라가며 데이터 출력
        printf("%d->", p->data);
    printf("NULL\n"); // 스택의 끝 표시
}

// 스택에서 요소를 제거하고 반환하는 함수
element pop(LinkedStacktype* s) {
    if (is_empty(s)) { // 스택이 비어있는지 확인
        fprintf(stderr, "스택이 비어있음\n"); // 에러 메시지 출력
        exit(1); // 프로그램 종료
    }
    else {
        StackNode* temp = s->top; // 제거할 노드를 가리킴
        int data = temp->data; // 제거할 노드의 데이터를 저장
        s->top = s->top->link; // top을 다음 노드로 갱신
        free(temp); // 제거한 노드 메모리 해제
        return data; // 제거된 데이터 반환
    }
}

// 스택의 최상단 요소를 반환하는 함수
element peak(LinkedStacktype* s) {
    if (is_empty(s)) { // 스택이 비어있는지 확인
        fprintf(stderr, "스택이 비어있음\n"); // 에러 메시지 출력
        exit(1); // 프로그램 종료
    }
    else {
        return s->top->data; // 최상단 요소 반환
    }
}

// 메인 함수
int main(void) {
    LinkedStacktype s; // 연결 리스트 기반 스택 선언
    init(&s); // 스택 초기화
    push(&s, 1); print_stack(&s); // 스택에 1 삽입 후 출력
    push(&s, 2); print_stack(&s); // 스택에 2 삽입 후 출력
    push(&s, 3); print_stack(&s); // 스택에 3 삽입 후 출력
    pop(&s); print_stack(&s); // 스택에서 요소 제거 후 출력
    pop(&s); print_stack(&s); // 스택에서 요소 제거 후 출력
    pop(&s); print_stack(&s); // 스택에서 요소 제거 후 출력
    return 0; // 프로그램 종료
}