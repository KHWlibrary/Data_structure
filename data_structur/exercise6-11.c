#define _CRT_SECURE_NO_WARNINGS    // scanf 사용 시 보안 경고 무시
#define MAX_LIST_SIZE 100          // 리스트 최대 크기 정의
#include <stdio.h>
#include <stdlib.h>

// 요소(element) 자료형 정의 (여기서는 int)
typedef int element;

// 배열 리스트 타입 정의
typedef struct
{
	element array[MAX_LIST_SIZE]; // 데이터를 저장할 배열
	int size;                     // 현재 리스트에 저장된 요소 수
} ArrayListType;

// 오류 발생 시 메시지를 출력하고 프로그램 종료
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 리스트 초기화: 요소 수를 0으로 설정
void init(ArrayListType* L)
{
	L->size = 0;
}

// 리스트가 가득 찼는지 확인 (1: 가득참, 0: 여유있음)
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}

// 특정 위치(pos)의 요소를 반환
element get_entry(ArrayListType* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("위치 오류");  // 범위를 벗어난 경우 오류 처리
	return L->array[pos];
}

// 리스트의 모든 요소를 출력
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n"); // 끝 표시
}

// 리스트의 마지막에 새 요소 추가
void insert_last(ArrayListType* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) {
		error("리스트 오버플로우");  // 최대 크기 초과 시 오류
	}
	L->array[L->size++] = item;  // 요소 삽입 후 크기 증가
}

// 지정한 위치(pos)에 요소 삽입 (뒤 요소들 한 칸씩 뒤로 이동)
void insert(ArrayListType* L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		// 뒤에서부터 한 칸씩 이동
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;  // 지정된 위치에 새 값 삽입
		L->size++;             // 크기 증가
	}
}

// 지정한 위치(pos)의 요소 삭제 후 그 값을 반환
element delete(ArrayListType* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
		error("위치오류");  // 잘못된 위치 접근 시 오류
	item = L->array[pos];    // 삭제할 값 저장
	// 뒤의 요소들을 한 칸씩 앞으로 이동
	for (int i = pos; i < (L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;               // 크기 감소
	return item;             // 삭제된 값 반환
}

// 메인 함수
int main(void)
{
	ArrayListType list;      // 배열 리스트 변수 선언
	init(&list);             // 리스트 초기화

	int count, data;
	int i;
	int sum = 0;             // 데이터의 합 저장용 변수

	printf("노드의 개수: ");
	scanf("%d", &count);     // 입력할 데이터 개수 입력

	// 사용자가 입력한 개수만큼 데이터를 입력받고 리스트에 추가
	for (i = 0; i < count; i++)
	{
		printf("노드 #%d 데이터 : ", i + 1);
		scanf("%d", &data);
		insert_last(&list, data);  // 리스트에 데이터 추가
	}

	// 리스트에 저장된 모든 데이터의 합 계산
	for (i = 0; i < list.size; i++) {
		sum += list.array[i];
	}

	// 합계 출력
	printf("연결 리스트의 데이터 합 = %d\n", sum);

	return 0;
}
