//문자열을 압축하는 프로그램을 작성하라.

#define _CRT_SECURE_NO_WARNINGS    // scanf, strcpy 등의 함수에서 보안 경고를 피하기 위한 매크로
#include <stdio.h>                 // 표준 입출력 함수들 사용 (ex. printf, scanf)
#include <stdlib.h>                // 일반 함수들 사용 (ex. exit, malloc)
#include <string.h>                // 문자열 처리 함수 사용 (ex. strlen, strcmp)
#include <ctype.h>                 // 문자 처리 함수 사용 (ex. tolower)

//===== 스택 코드의 시작 =====
#define MAX_STACK_SIZE 100         // 스택에 저장할 수 있는 최대 크기 정의
typedef char element;              // 스택의 자료형을 char로 설정 (문자 저장)

typedef struct {
    element data[MAX_STACK_SIZE]; // 문자들을 저장할 배열
    int top;                      // 스택의 top을 가리키는 인덱스
} StackType;

// 스택을 초기화하는 함수
void init_stack(StackType* s) {
    s->top = -1;                  // top을 -1로 설정하여 공백 상태로 초기화
}

// 스택이 비었는지 확인하는 함수
int is_empty(StackType* s) {
    return (s->top == -1);        // top이 -1이면 공백 상태
}

// 스택이 가득 찼는지 확인하는 함수
int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));  // top이 최대 인덱스에 도달하면 포화 상태
}

// 스택에 문자를 추가하는 함수
void push(StackType* s, element item) {
    if (is_full(s)) {                             // 스택이 가득 찼는지 확인
        fprintf(stderr, "스택 포화 에러\n");       // 오류 메시지 출력
        return;                                   // 함수 종료
    }
    else s->data[++(s->top)] = item;              // top을 증가시키고 데이터 저장
}

// 스택에서 문자를 꺼내 반환하는 함수
element pop(StackType* s) {
    if (is_empty(s)) {                            // 스택이 비어있는지 확인
        fprintf(stderr, "스택 공백 에러\n");       // 오류 메시지 출력
        exit(1);                                  // 프로그램 종료
    }
    else return s->data[(s->top)--];              // top 위치의 데이터 반환하고 top 감소
}

// 스택의 가장 위 요소를 제거하지 않고 반환하는 함수
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택공백에러\n");
        exit(1);
    }
    else return s->data[s->top];
}
//===== 스택 코드의 끝 =====


// 숫자를 문자로 바꾼 후 하나씩 스택에 push하는 함수
void push_count(StackType* s, int count) {
    char buffer[10];                         // 숫자를 문자열로 저장할 임시 배열
    sprintf(buffer, "%d", count);            // 정수를 문자열로 변환하여 buffer에 저장

    // 변환된 문자열을 한 글자씩 스택에 넣기
    push(s, buffer[0]);                      // 첫 글자 push
    for (int i = 1; buffer[i] != '\0'; i++) {
        push(s, buffer[i]);                  // 두 번째 글자부터 끝까지 push
    }
}


// 런-길이 인코딩 함수: 반복되는 문자를 압축하는 알고리즘
void run_length_encoding(const char* str) {
    StackType stack;              // 스택 선언
    init_stack(&stack);           // 스택 초기화

    int len = strlen(str);        // 입력 문자열의 길이 계산
    int i = 0;                    // 반복문에서 사용할 인덱스

    // 문자열 끝까지 반복
    while (i < len) {
        char current = str[i];    // 현재 문자 저장
        int count = 1;            // 현재 문자의 반복 횟수 초기화

        // 다음 문자가 현재 문자와 같으면 count 증가
        while (i + 1 < len && str[i + 1] == current) {
            count++;              // 반복된 횟수 증가
            i++;                  // 인덱스 이동
        }

        // 반복 횟수와 문자를 스택에 넣기 (횟수를 먼저 push)
        push_count(&stack, count);   // 예: 3 → '3'
        push(&stack, current);       // 예: 'a'

        i++;                      // 다음 문자로 이동
    }

    // 결과 출력: 스택에서 pop 하면서 거꾸로 출력됨
    printf("Run-Length encoding 결과: ");
    while (!is_empty(&stack)) {
        printf("%c", pop(&stack));  // pop 하면서 출력 (역순)
    }
    printf("\n");
}


// 메인 함수: 프로그램의 시작점
int main() {
    char input[100];                        // 사용자 입력을 저장할 배열

    printf("문자열을 입력하세요: ");        // 입력 요청 출력
    scanf("%s", input);                     // 문자열 입력 받기

    // 입력 받은 문자열을 모두 소문자로 변환
    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = tolower(input[i]);       // 대문자 → 소문자로 변환
    }

    run_length_encoding(input);             // 런-길이 인코딩 수행
    return 0;                               // 프로그램 정상 종료
}
