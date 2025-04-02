//1부터 n까지 합
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int sum(int n)
{
	printf("%d\n", n);
	if (n < 1) return 1;
	else return(n + sum(n - 1));
}

int main(void)
{
	int n;
	printf("n값을 입력해주세요: ");
	scanf("%d", &n);

	printf("result = %d\n", sum(n));

}