#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int recursive(int n)
{
	printf("%d\n", n);
	if (1/n+2 < 0) return 0;
	else return(recursive(1/n+1));
}

int main(void)
{
	int n;
	printf("숫자를 입력하세요: ");
	scanf("%d", &n);
	printf("result = %d", recursive(n));

	return 0;
}