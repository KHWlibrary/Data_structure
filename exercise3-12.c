/* 1개의 정수,최대 크기가 20인 문자열로 이루어진 구조체 저장할 수 있도록 동적 메모리를 할당 받고
여기에 정수 100과 문자열 "just testing저장", 동적 메모리를 반납하는 프로그램*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct{
	char string[20];		//최대크기 20인 문자열 
	int num;				//정수 값
}testdata;
int main(void)
{
	testdata* p;

	p = (testdata*)malloc( sizeof(testdata));
	if (p == NULL) {
		fprintf(stderr, "메모리가 부족해서 할당할 수 없습니다\n");
		exit(1);
	}
	
	strcpy_s(p->string, sizeof(p->string), "just testing");
	p->num = 100;

	printf("String: %s\n", p->string);
	printf("Number: %d\n", p->num);

	free(p);		//동적 메모리 해제
	return 0;

}