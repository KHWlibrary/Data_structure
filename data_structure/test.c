#define _CRT_SECURE_NO_WARNINGS // Visual Studio 환경에서 보안 관련 경고를 비활성화합니다.

#include<stdio.h>  // 표준 입출력 함수(printf, scanf 등)를 사용하기 위해 포함합니다.
#include<stdlib.h> // 표준 라이브러리 함수(exit 등)를 사용하기 위해 포함합니다.

// 차후에 스택이 필요하면 여기만 복사하여 붙인다.
//=====스택 코드의 시작=====
#define MAX_STACK_SIZE 7 // 스택의 최대 크기를 7로 정의합니다.
typedef int element;      // 스택에 저장될 요소의 타입을 int로 정의합니다. (element라는 별칭 사용)

// 스택 구조체 정의
typedef struct {
    element data[MAX_STACK_SIZE]; // 데이터를 저장할 배열 (크기는 MAX_STACK_SIZE)
    int top;                     // 스택의 가장 위 요소를 가리키는 인덱스
} StackType;

// 스택 초기화 함수: 스택의 top을 -1로 설정하여 비어있는 상태로 만듭니다.
void init_stack(StackType* s)
{
    s->top = -1;
}

// 공백 상태 검출 함수: 스택이 비어있는지 확인합니다. (top이 -1이면 true)
int is_empty(StackType* s)
{
    return(s->top == -1); // top이 -1이면 1(true)을 반환, 아니면 0(false)을 반환
}

// 포화 상태 검출 함수: 스택이 가득 찼는지 확인합니다. (top이 마지막 인덱스이면 true)
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1)); // top이 MAX_STACK_SIZE-1이면 1(true) 반환, 아니면 0(false) 반환
}

// 삽입 함수 (push): 스택의 맨 위에 요소를 추가합니다.
void push(StackType* s, element item)
{
    if (is_full(s)) { // 스택이 가득 찼는지 확인
        fprintf(stderr, "스택 포화 에러\n"); // 가득 찼으면 에러 메시지 출력
        return; // 함수 종료 (더 이상 삽입 불가)
    }
    else {
        s->top = s->top + 1;        // top을 1 증가시키고
        s->data[s->top] = item;    // 새로운 top 위치에 item을 저장
        // 위 두 줄은 s->data[++(s->top)] = item; 와 동일합니다. (전위 증가 연산자 사용)
    }
}

// 삭제 함수 (pop): 스택의 맨 위 요소를 제거하고 반환합니다.
element pop(StackType* s)
{
    if (is_empty(s)) { // 스택이 비어있는지 확인
        fprintf(stderr, "스택 공백 에러\n"); // 비어있으면 에러 메시지 출력
        exit(1);                       // 프로그램 강제 종료
    }
    else {
        element temp = s->data[s->top]; // 현재 top의 데이터를 임시 변수에 저장
        s->top = s->top - 1;           // top을 1 감소시켜 요소를 제거한 효과
        return temp;                    // 임시 변수에 저장했던 데이터 반환
        // 위 세 줄은 return s->data[(s->top)--]; 와 동일합니다. (후위 감소 연산자 사용)
    }
}

// 피크 함수 (peek): 스택의 맨 위 요소를 제거하지 않고 확인만 합니다.
element peek(StackType* s)
{
    if (is_empty(s)) { // 스택이 비어있는지 확인
        fprintf(stderr, "스택 공백 에러\n"); // 비어있으면 에러 메시지 출력
        exit(1);                       // 프로그램 강제 종료
    }
    else {
        return s->data[s->top]; // 현재 top 위치의 데이터를 반환 (top은 변경되지 않음)
    }
}
//===== 스택 코드의 끝 =====

int main(void)
{
    StackType s; // StackType 구조체 변수 s 선언 (스택 생성)

    init_stack(&s); // 생성된 스택 s를 초기화

    int num; // 사용자로부터 입력받을 정수를 저장할 변수

    // 스택의 실제 용량(MAX_STACK_SIZE)을 기반으로 최대 입력 가능한 자릿수를 안내하는 것이 더 좋습니다.
    // printf("정수 배열의 크기: %d\n", MAX_STACK_SIZE -1  ); // 최대 6자리 입력 가능하다고 안내 (실제로는 7자리)
    printf("최대 입력 가능한 정수 자릿수: %d\n", MAX_STACK_SIZE); // 스택 크기만큼 입력 가능함을 안내 (7자리)
    printf("정수를 입력하시오: ");
    scanf("%d", &num); // 사용자로부터 정수를 입력받아 num 변수에 저장

    // 입력값 검증
    if (num == 0) { // 입력값이 0이면
        printf("반전된 정수 배열: 0\n"); // 그냥 0을 출력 (특별히 처리)
        return 0; // 프로그램 정상 종료
    }
    if (num < 0) { // 입력값이 음수이면
        printf("음수는 사용하지 않습니다\n"); // 에러 메시지 출력
        return 0; // 프로그램 정상 종료
    }

    // 정수의 각 자릿수를 스택에 push
    while (num > 0) { // num이 0보다 큰 동안 반복 (모든 자릿수를 처리할 때까지)
        if (is_full(&s)) { // push 하기 전에 스택이 꽉 찼는지 확인
            printf("\n경고: 입력한 정수가 너무 큽니다. %d자리까지만 처리됩니다.\n", MAX_STACK_SIZE);
            break; // 스택이 꽉 찼으면 반복 중단
        }
        push(&s, num % 10); // num의 마지막 자릿수(1의 자리)를 스택에 push
        num /= 10;          // num을 10으로 나누어 마지막 자릿수를 제거
    }

    // 스택에서 pop하면서 출력하여 숫자를 거꾸로 만듦
    printf("반전된 정수 배열: ");
    while (!is_empty(&s)) { // 스택이 비어있지 않은 동안 반복
        printf("%d", pop(&s)); // 스택에서 맨 위 요소를 pop하여 출력
    }
    printf("\n"); // 줄바꿈 출력

    return 0; // 프로그램 정상 종료
}

