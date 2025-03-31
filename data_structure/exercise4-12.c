#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//=====스택 코드의 시작=====
#define MAX_STACK_SIZE 100
typedef char element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

//스택 초기화 함수
void init_stack(StackType* s) {
    s->top = -1;
}

//공백 상태 검출 함수
int is_empty(StackType* s) {
    return (s->top == -1);
}
//포화 상태 검출 함수
int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}
//삽입함수
void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}
//삭제함수
element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}
//피크함수
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택공백에러\n");
        exit(1);
    }
    else return s->data[s->top];
}
//===== 스택 코드의 끝 =====

// 숫자를 문자로 변환해서 push
void push_count(StackType* s, int count) {
    char buffer[10];
    sprintf(buffer, "%d", count);  // 숫자를 문자열로 변환

    // 문자 먼저 push
    push(s, buffer[0]);

    // 숫자(자릿수) 뒤에 push
    for (int i = 1; buffer[i] != '\0'; i++) {
        push(s, buffer[i]);
    }
}

void run_length_encoding(const char* str) {
    StackType stack;
    init_stack(&stack);

    int len = strlen(str);
    int i = 0;
    while (i < len) {
        char current = str[i];
        int count = 1;

        while (i + 1 < len && str[i + 1] == current) {
            count++;
            i++;
        }

        // 먼저 count를 push하고, 그 다음 문자를 push
        push_count(&stack, count);
        push(&stack, current);

        i++;  //다음 문자 넘어가기 위한 i++
    }

    // 출력: 스택에서 역순으로 pop
    printf("Run-Length encoding 결과: ");
    while (!is_empty(&stack)) {
        printf("%c", pop(&stack));
    }
    printf("\n");
}


// 메인 함수
int main() {
    char input[100];
    printf("문자열을 입력하세요: ");
    scanf("%s", input);

    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = tolower(input[i]);  // 대문자를 소문자로 변환
    }

    run_length_encoding(input);
    return 0;
}
