#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int recursive(int n)
{
	if (n != 1) recursive(n - 1);
	printf("%d\n", n);

}

int main(void)
{
	int n;
	printf("정수값 입력: ");
	scanf("%d", &n);
	printf("결과값: %d\n", recursive(n));
}