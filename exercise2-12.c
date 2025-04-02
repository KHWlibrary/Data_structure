#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void unknown()
{
	int ch;
	if ((ch = getchar()) != '\n')
		unknown();
	putchar(ch);
}

int main(void)
{
	printf("문자열을 입력하세요: ");
	unknown();
	
	return 0;
}