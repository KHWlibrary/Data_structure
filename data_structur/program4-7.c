#include<stdio.h>      // 표준 입출력 함수 사용
#include<stdlib.h>     // 동적 메모리 할당, exit 함수 사용
#define MAX_STACK_SIZE 100  // 스택 최대 크기 정의

// ===== 스택 관련 코드 시작 =====

// 스택에 저장할 요소의 자료형을 char로 정의 (숫자나 연산자 저장 가능)
typedef char element;

// 스택 구조체 정의 (배열 기반 스택)
typedef struct {
    element data[MAX_STACK_SIZE];  // 요소들을 저장할 배열
    int top;                       // 스택의 가장 위(top) 요소의 인덱스
} StackType;

// 스택 초기화 함수 - 스택을 비어 있는 상태로 설정
void init_stack(StackType* s)
{
    s->top = -1;  // top을 -1로 설정하여 스택이 비어 있음을 표시
}

// 스택이 비어 있는지 확인하는 함수
int is_empty(StackType* s)
{
    return(s->top == -1);  // top이 -1이면 공백 상태임
}

// 스택이 가득 찼는지 확인하는 함수
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));  // top이 배열 끝이면 포화 상태
}

// 스택에 요소를 추가하는 함수 (push 연산)
void push(StackType* s, element item)
{
    if (is_full(s)) {  // 스택이 가득 찼을 경우
        fprintf(stderr, "스택 포화 에러\n");  // 에러 메시지 출력
        return;  // 더 이상 삽입할 수 없으므로 종료
    }
    else {
        s->data[++(s->top)] = item;  // top을 증가시키고 해당 위치에 item 저장
    }
}

// 스택에서 요소를 꺼내는 함수 (pop 연산)
element pop(StackType* s)
{
    if (is_empty(s)) {  // 스택이 비어 있으면
        fprintf(stderr, "스택 공백 에러\n");  // 에러 메시지 출력
        exit(1);  // 프로그램 강제 종료
    }
    else {
        return s->data[(s->top)--];  // top 위치의 값을 반환하고 top 감소
    }
}

// 스택의 top 요소를 삭제하지 않고 반환하는 함수 (peek 연산)
element peek(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택공백에러\n");  // 스택이 비어 있을 경우
        exit(1);
    }
    else {
        return s->data[s->top];  // 현재 top 위치의 요소 반환
    }
}

// ===== 스택 코드 끝 =====

// ===== 후위 표기 수식 계산 함수 =====
// 후위 표기법(postfix expression)의 수식을 받아 계산 결과를 반환
int eval(char exp[])
{
    int op1, op2;    // 피연산자 1, 2
    int value;       // 문자 → 정수로 변환한 피연산자 저장
    int i = 0;       // 반복문 인덱스
    int len = strlen(exp);  // 입력된 수식 문자열의 길이
    char ch;         // 현재 읽고 있는 문자
    StackType s;     // 계산에 사용할 스택 선언

    init_stack(&s);  // 스택 초기화

    // 수식의 모든 문자들을 한 글자씩 검사
    for (i = 0; i < len; i++) {
        ch = exp[i];  // 현재 문자를 ch에 저장

        // 피연산자인 경우 (숫자일 경우) → 스택에 push
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            value = ch - '0';  // 문자 '0'~'9' → 정수 0~9로 변환
            push(&s, value);   // 스택에 숫자 저장
        }
        else {
            // 연산자인 경우: 피연산자 2개를 스택에서 꺼냄
            op2 = pop(&s);  // 두 번째 피연산자
            op1 = pop(&s);  // 첫 번째 피연산자

            // 연산자에 따라 계산 수행하고 결과를 스택에 저장
            switch (ch) {
            case '+':
                push(&s, op1 + op2);
                break;
            case '-':
                push(&s, op1 - op2);
                break;
            case '*':
                push(&s, op1 * op2);
                break;
            case '/':
                push(&s, op1 / op2);
                break;
            }
        }
    }

    // 계산이 끝난 후 스택에 남은 최종 결과를 반환
    return pop(&s);
}

// ===== 메인 함수 =====
int main(void)
{
    int result;  // 계산 결과 저장 변수

    // 테스트할 후위 표기 수식 출력
    printf("후위표기식은 82/3-32*+\n");

    // 후위 표기 수식을 계산하고 결과 저장
    result = eval("82/3-32*+");  // 실제 수식: (8 / 2) - 3 + (3 * 2)

    // 결과 출력
    printf("결과값은 %d\n", result);  // 결과는 7

    return 0;
}
