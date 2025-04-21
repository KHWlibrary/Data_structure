// 배열에 들어있는 정수의 수열을 거꾸로 출력하는 프로그램. 스택을 사용함
#define _CRT_SECURE_NO_WARNINGS    // Visual Studio에서 scanf 보안 경고 제거를 위한 매크로

#include <stdio.h>      // 표준 입출력 함수 사용
#include <stdlib.h>     // exit 함수 사용

//===== 스택 코드의 시작 =====
#define MAX_STACK_SIZE 7           // 스택에 저장할 수 있는 최대 요소 개수 (0~6까지 총 7개, 실제론 6자리 정수까지)

// element라는 별칭을 int로 정의 (스택에 저장할 데이터 타입)
typedef int element;

// 스택 자료형 정의
typedef struct {
    element data[MAX_STACK_SIZE]; // 데이터를 저장할 배열
    int top;                      // 스택의 top 인덱스를 가리키는 변수
} StackType;

// 스택 초기화 함수 - top을 -1로 초기화하여 공백 상태로 설정
void init_stack(StackType* s)
{
    s->top = -1;
}

// 스택이 비어있는지 확인하는 함수
int is_empty(StackType* s)
{
    return (s->top == -1);    // top이 -1이면 공백 상태
}

// 스택이 가득 찼는지 확인하는 함수
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));   // top이 마지막 인덱스에 도달했는지 확인
}

// 스택에 요소를 삽입하는 함수
void push(StackType* s, element item)
{
    if (is_full(s)) {    // 스택이 가득 찬 경우 에러 출력
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else
        s->data[++(s->top)] = item;    // top을 하나 증가시키고 해당 위치에 값 저장
}

// 스택에서 요소를 제거하고 반환하는 함수
element pop(StackType* s)
{
    if (is_empty(s)) {    // 스택이 비어 있는 경우 에러 출력 후 종료
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];   // top 위치의 값을 반환하고 top을 감소
}

// 스택의 top 요소를 제거하지 않고 확인하는 함수
element peek(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->data[s->top];   // top 위치의 값을 그대로 반환
}
//===== 스택 코드의 끝 =====

// 메인 함수 시작
int main(void)
{
    StackType s;             // 스택 변수 선언
    init_stack(&s);          // 스택 초기화

    int num;                 // 사용자로부터 입력 받을 정수

    // 안내 메시지 출력
    printf("정수 배열의 크기: %d\n", MAX_STACK_SIZE - 1);    // 최대 6자리까지 입력 가능
    printf("정수를 입력하시오: ");
    scanf("%d", &num);       // 사용자 입력 받기

    // 입력 값이 0이면
