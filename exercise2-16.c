#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sum(int n)
{
    if (n == 1) return 1;
    else return (n + sum(n - 1));
}

int main(void)
{
    int n;
    printf("숫자를 입력해주세요 : ");

    // scanf 반환값 체크
    if (scanf("%d", &n) != 1) {
        printf("입력 오류! 정수를 입력하세요.\n");
        return 1; // 프로그램 종료
    }

    // 1 이상의 숫자만 받도록 체크
    if (n <= 0) {
        printf("양수를 입력하세요.\n");
        return 1;
    }

    printf("result = %d\n", sum(n));
    return 0;
}
