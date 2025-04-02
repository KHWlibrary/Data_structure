#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define WHITE 0
#define BLACK 1
#define YELLOW 2

int screen[WIDTH][HEIGHT];
//
char read_pixel(int x, int y)
{
	return screen[x][y];
}
//
void write_pixel(int x, int y, int color)
{
	screen[x][y] = color;
}
//영역 채우기 알고리즘
void flood_fill(int x, int y)
{
	if (read_pixel(x, y) == WHITE)
	{
		write_pixel(x, y, BLACK);
		read_pixel(x+1, y);;
		read_pixel(x, y+1);;
		read_pixel(x-1, y);;
		read_pixel(x, y-1);;

	}
}