#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fib(int n)
{
	printf("fib(%d) is  call\n", n);
	if (n == 0) return 0;
	if (n == 1) return 1;
	return (fib(n - 1) + fib(n - 2));
}

int main(void)
{
	int n;
	printf("숫자를 입력해주세요 : ");
	scanf("%d", &n);

	printf("result = %d", fib(n));
	return 0;
}