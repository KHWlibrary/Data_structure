//수식에 있는 괄호의 번호를 출력하는 프로그램을 작성하라.
//왼쪽 괄호가 나올 때 마다 활호 번호는 하나씩 증가한다.
//오른쪽 갈호가 나오면 매칭되는 왼쪽 갈호 번호를 출력한다

#include <stdio.h>      // 표준 입출력 함수 사용을 위한 헤더 파일 (ex: printf, fgets 등)
#include <stdlib.h>     // 일반적인 유틸리티 함수들 사용 위한 헤더 (ex: exit 함수 등)

//===== 스택 코드의 시작 =====
// 스택은 데이터를 나중에 넣은 것이 먼저 나오는 LIFO(Last In First Out) 구조입니다.
// 괄호의 짝을 맞추거나, 중첩을 추적하는 데 유용합니다.

#define MAX_STACK_SIZE 100         // 스택의 최대 용량을 100으로 설정
typedef char element;              // 스택에 저장될 자료형을 char(문자)로 설정

// 스택 구조체 정의
typedef struct {
    element data[MAX_STACK_SIZE]; // 실제 데이터를 저장할 배열
    int top;                      // 스택의 현재 꼭대기 인덱스를 저장
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
    s->top = -1;  // 스택이 비어 있음을 나타내기 위해 top을 -1로 설정
}

// 스택이 비었는지 확인하는 함수
int is_empty(StackType* s)
{
    return (s->top == -1); // top이 -1이면 스택이 비어 있는 상태
}

// 스택이 가득 찼는지 확인하는 함수
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1)); // top이 배열의 마지막 인덱스면 포화 상태
}

// 스택에 값을 추가하는 함수 (push)
void push(StackType* s, element item)
{
    if (is_full(s)) { // 스택이 가득 찼는지 확인
        fprintf(stderr, "스택 포화 에러\n"); // 에러 메시지 출력
        return; // 삽입 중단
    }
    else
        s->data[++(s->top)] = item; // top을 증가시킨 후, 해당 위치에 item 삽입
}

// 스택에서 값을 제거하고 반환하는 함수 (pop)
element pop(StackType* s)
{
    if (is_empty(s)) { // 스택이 비어 있는지 확인
        fprintf(stderr, "스택 공백 에러\n"); // 에러 메시지 출력
        exit(1); // 프로그램 비정상 종료
    }
    else
        return s->data[(s->top)--]; // top 위치의 값을 반환하고 top을 감소시킴
}

// 스택의 최상단 값을 반환하되 제거하지 않는 함수 (peek)
element peek(StackType* s)
{
    if (is_empty(s)) { // 스택이 비어 있는지 확인
        fprintf(stderr, "스택공백에러\n"); // 에러 메시지 출력
        exit(1); // 프로그램 비정상 종료
    }
    else
        return s->data[s->top]; // top 위치의 값을 반환만 (삭제 X)
}
//===== 스택 코드의 끝 =====


// 입력된 괄호 문자열을 분석하고 숫자로 중첩 구조를 표현하는 함수
void process_parentheses(char* expr) {
    StackType stack;         // 괄호 처리를 위한 스택 선언
    init_stack(&stack);      // 스택 초기화 (top = -1)
    int current_value = 0;   // 중첩 정도를 표현할 숫자, 가장 바깥은 1부터 시작

    // 문자열을 한 글자씩 탐색
    for (int i = 0; expr[i] != '\0'; i++) {
        // 여는 괄호 '('를 만났을 때
        if (expr[i] == '(') {
            // 현재 숫자 상태를 스택에 저장 (나중에 닫는 괄호에서 복원)
            push(&stack, current_value);
            current_value += 1; // 괄호가 하나 더 깊어졌으므로 숫자 증가
            printf("%d", current_value); // 증가된 숫자 출력
        }
        // 닫는 괄호 ')'를 만났을 때
        else if (expr[i] == ')') {
            // 스택이 비어 있지 않으면
            if (!is_empty(&stack)) {
                // 스택에서 이전 숫자를 꺼내 현재 숫자로 설정
                current_value = pop(&stack);
                printf("%d", current_value); // 이전 숫자 출력
            }
            // 스택이 비어 있으면 괄호 구조가 잘못된 것이므로
            else {
                printf(" "); // 공백 출력
                return; // 함수 종료
            }
        }
    }
}

// 메인 함수
int main()
{
    char expr[MAX_STACK_SIZE];  // 괄호 문자열을 저장할 배열 선언

    printf("괄호를 입력시오: "); // 사용자에게 입력 안내 출력
    fgets(expr, MAX_STACK_SIZE, stdin); // 사용자로부터 괄호 문자열 입력 받음

    process_parentheses(expr); // 괄호 분석 함수 호출

    return 0; // 프로그램 종료
}
 