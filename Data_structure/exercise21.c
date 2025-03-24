#include <stdio.h>
#define WHITE 0 // 0을 WHITE라 정의
#define BLACK 1 // 1을 BLACK이라 정의
// [참고] YELLOW는 불필요하여 제거하였습니다.(처음부터 2로 초기화 했습니다)

int screen[10][10] = // 배열 초기화 후 바로 초기값을 넣어줍니다.

{ {2,2,2,2,2,2,2,2,2,2},

 {2,2,2,2,2,2,2,2,2,2},

 {2,2,2,0,0,0,0,2,2,2},

 {2,2,2,2,0,0,0,2,2,2},

 {2,2,2,2,0,0,0,2,2,2},

 {2,2,2,2,0,0,0,0,2,2},

 {2,2,2,2,0,2,2,2,2,2},

 {2,2,2,2,0,2,2,2,2,2},

 {2,2,2,2,0,2,2,2,2,2},

 {2,2,2,2,2,2,2,2,2,2} };

// screen 배열을 읽어들이기(순환 호출에서 쓰임)

char read_pixel(int x, int y)

{

    return screen[x][y];

}

// 해당 x, y 위치를 color(BLACK)로 채우기(순환 호출에서 쓰임)

void write_pixel(int x, int y, int color)

{

    screen[x][y] = color;

}

// 영역 채우기 알고리즘 

void flood_fill(int x, int y)

{
    if (x < 0 || x >= 10 || y < 0 || y >= 10) // 배열 범위 검사 추가
        return;

    if (read_pixel(x, y) == WHITE) // read_pixel 함수 호출의 결과로 0을 발견하면

    {

        write_pixel(x, y, BLACK); // write_pixel 함수를 호출해서 BLACK(1)로 채우기
        flood_fill(x - 1, y); // 순환호출(x-1번째 위치)
        flood_fill(x + 1, y); // 순환호출(x+1번째 위치) 
        flood_fill(x, y - 1); // 순환호출(y-1번째 위치)
        flood_fill(x, y + 1); // 순환호출(y+1번째 위치)
    }

}

void result_print()

{

    int i, j; // 인덱스 i, j 선언
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {

            printf("%d ", screen[i][j]); // 10x10 크기의 배열 출력(보여주기)

        }

        printf("\n");

    }

}

int main()

{



    printf("영역 채우기 대상 도형\n-------------------\n");

    result_print(); // 초기값으로 지정된 배열을 출력 



    flood_fill(4, 4); // 채우기 실행(시작 위치: 4,4)



    printf("안쪽을 채우는 순환 호출 함수 작동\n-------------------\n");

    result_print(); // flood_fill 함수 호출 뒤 결과(배열) 출력 



    return 0;
}