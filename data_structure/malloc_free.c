#include<stdio.h>
#include <stdlib.h> //malloc, free

int main(void)
{
	int* p[3];	//포인터 배열 // 포인터 변수 3개
	int i, j;
	int num = 1;

	//동적 메모리 할당
	for (i = 0; i < 3; i++)//배열의 첨자
	{
		p[i] = (int*)malloc(sizeof(int) * 4);
	}
	/*p[0] = (int*)malloc(sizeof(int) * 4);
	p[1] = (int*)malloc(sizeof(int) * 4);
	p[2] = (int*)malloc(sizeof(int) * 4);*/

	for (i = 0;i < 3;i++)//행
	{
		for (j = 0; j < 4;j++)//열
		{
			p[i][j] = num++; //값을 저장
			printf("%4d", p[i][j]);
		}
		puts("");//줄바꿈
	}

	//동적 메모리 제거
	for (i = 0;i < 3;i++)//배열의 첨자
	{
		//free(포인터);
		free(p[i]);
	}
	return 0;
}

/*출력값
1 2  3  4
5 6  7  8
9 10 11 12*/