/*typedef를 이용하여 complex하는 새로운 자료형을 정의하라
complex자료형은 구조체로서 float 형real 변수, imaginary변수를 갖는다
complex 자료형으로 변수c1과 c2를 선언하라*/

#include<stdio.h>
#define MAX_TERMS 100
typedef struct {
	float real;
	float imaginary;
}complex;

int main(void) {
	complex c1, c2;

	c1.real = 1.33333;
	c1.imaginary = 12.1;
	
	c2.real = 2.55;
	c2.imaginary = 2.4442;

	printf("c1 = %.1f + %.1f\n", c1.real, c1.imaginary);
	printf("c2 = %.1f + %.1f", c2.real, c2.imaginary);
	
	return 0;
}