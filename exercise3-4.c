#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

/*크기 10 배열 two선언 여기에 2의 제곱 값을 저장2^0~2^9까지*/
int main(void)
{
	int* p;
	p = (int*)malloc(SIZE * sizeof(int));
	if (p == NULL) {
		fprintf(stderr, "메모리가 부족해서 할당할 수 없습니다.\n"); //fprintf출력대상이 파일 스트림
		exit(1);
	}

	for (int i = 0; i < SIZE;i++)
		p[i] = 1 << i;		//2의 i승 저장

	for (int i = 0; i < SIZE;i++)
	{
		printf("%d ", p[i]);
	}

	free(p);
	return 0;
}