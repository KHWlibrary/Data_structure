#define MAX_LIST_SIZE 100	//리스트의 최대크기
#include<stdio.h>
#include<stdlib.h>

typedef int element;		//항목의 정리
typedef struct 
{
	element array[MAX_LIST_SIZE];	//배열 정의
	int size;
}ArrayListType;

//오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", massage);
	exit(1);
}

//리스트 초기화 함수
void init(ArrayListType* L)
{
	L->size = 0;
}
//리스트가 가득 차 있으면 1을 반환
//그렇지 않으면 0을 반환
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];
}

//리스트 출력
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0;i < L->size;i++)
		printf("%d->", L->array[i]);
	printf("\n");
}
//항목 추가 연산
