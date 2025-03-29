#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int recursive(int n)
{
	printf("%d\n", n);
	if (n < 1) return -1;
	else return(recursive(n - 3) + 1);
}

int main(void)
{
	int n;
	printf("숫자를 입력해주세요: ");
	scanf("%d", &n);

	printf("결과값은 %d입니다. ", recursive(n));
}