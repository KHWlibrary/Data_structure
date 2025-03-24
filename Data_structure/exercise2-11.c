#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void asterisk(int i)
{
	if (i > 1)
	{
		asterisk(i / 2);
		asterisk(i / 2);
	}
	printf("*");
}
int main(void)
{
	int i;
	printf("정수를 입력하세요: ");
	scanf("%d", &i);
	printf("결과값 :");
	asterisk(i);		//void 함수는 반환값을 출력하지 않음
	printf("\n");
}