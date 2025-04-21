// 미로 탐색 프로그램
#include<stdio.h>      // 표준 입출력 함수
#include<stdlib.h>     // exit 함수 등 시스템 함수
#include<string.h>     // 문자열 처리 함수
#define MAZE_SIZE 6    // 미로의 크기를 6x6으로 정의

// ===== 스택 코드 시작 =====
#define MAX_STACK_SIZE 100    // 스택의 최대 크기 정의

// 좌표를 저장할 구조체 정의
typedef struct {
	short r;   // 행 (row)
	short c;   // 열 (column)
} element;

// 스택 구조체 정의
typedef struct {
	element data[MAX_STACK_SIZE];  // 요소들을 저장할 배열
	int top;                       // 스택의 top 인덱스
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;  // top을 -1로 설정하여 빈 상태로 초기화
}

// 스택이 비어있는지 확인하는 함수
int is_empty(StackType* s)
{
	return(s->top == -1);  // top이 -1이면 비어있는 상태
}

// 스택이 가득 찼는지 확인하는 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));  // top이 최대 인덱스이면 포화
}

// 스택에 요소를 추가하는 함수
void push(StackType* s, element item)
{
	if (is_full(s)) {  // 스택이 가득 찼으면
		fprintf(stderr, "스택 포화 에러\n");  // 에러 메시지 출력
		return;
	}
	else
		s->data[++(s->top)] = item;  // top 증가 후 item 삽입
}

// 스택에서 요소를 제거하는 함수
element pop(StackType* s)
{
	if (is_empty(s)) {  // 스택이 비어있으면
		fprintf(stderr, "스택 공백 에러\n");  // 에러 메시지 출력
		exit(1);  // 프로그램 비정상 종료
	}
	else
		return s->data[(s->top)--];  // top 위치 요소 반환 후 top 감소
}

// 스택의 top 요소를 확인하는 함수 (제거하지 않음)
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택공백에러\n");
		exit(1);
	}
	else
		return s->data[s->top];  // top 위치의 요소 반환
}
// ===== 스택 코드 끝 =====

// 현재 위치 (초기 진입 지점) 설정
element here = { 1,0 }, entry = { 1,0 };

// 미로 정보 (6x6 배열로 정의)
char maze[MAZE_SIZE][MAZE_SIZE] = {
	{ '1', '1', '1', '1', '1', '1' },
	{ 'e', '0', '1', '0', '0', '1' },
	{ '1', '0', '0', '0', '1', '1' },
	{ '1', '0', '1', '0', '1', '1' },
	{ '1', '0', '1', '0', '1', 'x' },
	{ '1', '1', '1', '1', '1', '1' },
};
// '1'은 벽, '0'은 통로, 'e'는 입구, 'x'는 출구

// 지정한 위치(r, c)가 유효한 통로인지 확인 후 스택에 push
void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return 0;  // 인덱스가 음수면 범위 밖이므로 리턴
	// 벽('1')이 아니고 방문한 적이 없는 위치('.')가 아니면
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;  // 임시 위치 구조체 생성
		tmp.r = r;    // 행 저장
		tmp.c = c;    // 열 저장
		push(s, tmp); // 스택에 push
	}
}

// 미로 상태를 출력하는 함수
void maze_printf(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");  // 줄바꿈
	for (int r = 0; r < MAZE_SIZE; r++) {        // 행 순회
		for (int c = 0; c < MAZE_SIZE; c++) {    // 열 순회
			printf("%c", maze[r][c]);           // 각 위치의 문자 출력
		}
		printf("\n");  // 한 줄 끝나면 줄바꿈
	}
}

// 메인 함수
int main(void)
{
	int r, c;            // 현재 위치 좌표 저장용
	StackType s;         // 스택 변수 선언

	init_stack(&s);      // 스택 초기화
	here = entry;        // 현재 위치를 입구(entry)로 초기화

	// 출구('x')를 찾을 때까지 반복
	while (maze[here.r][here.c] != 'x') {
		r = here.r;  // 현재 위치의 행
		c = here.c;  // 현재 위치의 열
		maze[r][c] = '.';  // 현재 위치를 지나간 경로로 표시
		maze_printf(maze);  // 현재 미로 상태 출력

		// 상하좌우 방향으로 이동 가능한 위치들을 스택에 push
		push_loc(&s, r - 1, c);  // 위쪽
		push_loc(&s, r + 1, c);  // 아래쪽
		push_loc(&s, r, c - 1);  // 왼쪽
		push_loc(&s, r, c + 1);  // 오른쪽

		if (is_empty(&s)) {      // 더 이상 갈 곳이 없으면
			printf("실패\n");     // 실패 메시지 출력
			return;              // 프로그램 종료
		}
		else
			here = pop(&s);  // 다음 위치로 이동 (스택에서 pop)
	}

	printf("성공\n");  // 출구에 도달하면 성공 메시지 출력
	return 0;         // 프로그램 종료
}
