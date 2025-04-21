// �̷� Ž�� ���α׷�
#include<stdio.h>      // ǥ�� ����� �Լ�
#include<stdlib.h>     // exit �Լ� �� �ý��� �Լ�
#include<string.h>     // ���ڿ� ó�� �Լ�
#define MAZE_SIZE 6    // �̷��� ũ�⸦ 6x6���� ����

// ===== ���� �ڵ� ���� =====
#define MAX_STACK_SIZE 100    // ������ �ִ� ũ�� ����

// ��ǥ�� ������ ����ü ����
typedef struct {
	short r;   // �� (row)
	short c;   // �� (column)
} element;

// ���� ����ü ����
typedef struct {
	element data[MAX_STACK_SIZE];  // ��ҵ��� ������ �迭
	int top;                       // ������ top �ε���
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;  // top�� -1�� �����Ͽ� �� ���·� �ʱ�ȭ
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int is_empty(StackType* s)
{
	return(s->top == -1);  // top�� -1�̸� ����ִ� ����
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));  // top�� �ִ� �ε����̸� ��ȭ
}

// ���ÿ� ��Ҹ� �߰��ϴ� �Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {  // ������ ���� á����
		fprintf(stderr, "���� ��ȭ ����\n");  // ���� �޽��� ���
		return;
	}
	else
		s->data[++(s->top)] = item;  // top ���� �� item ����
}

// ���ÿ��� ��Ҹ� �����ϴ� �Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {  // ������ ���������
		fprintf(stderr, "���� ���� ����\n");  // ���� �޽��� ���
		exit(1);  // ���α׷� ������ ����
	}
	else
		return s->data[(s->top)--];  // top ��ġ ��� ��ȯ �� top ����
}

// ������ top ��Ҹ� Ȯ���ϴ� �Լ� (�������� ����)
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���ð��鿡��\n");
		exit(1);
	}
	else
		return s->data[s->top];  // top ��ġ�� ��� ��ȯ
}
// ===== ���� �ڵ� �� =====

// ���� ��ġ (�ʱ� ���� ����) ����
element here = { 1,0 }, entry = { 1,0 };

// �̷� ���� (6x6 �迭�� ����)
char maze[MAZE_SIZE][MAZE_SIZE] = {
	{ '1', '1', '1', '1', '1', '1' },
	{ 'e', '0', '1', '0', '0', '1' },
	{ '1', '0', '0', '0', '1', '1' },
	{ '1', '0', '1', '0', '1', '1' },
	{ '1', '0', '1', '0', '1', 'x' },
	{ '1', '1', '1', '1', '1', '1' },
};
// '1'�� ��, '0'�� ���, 'e'�� �Ա�, 'x'�� �ⱸ

// ������ ��ġ(r, c)�� ��ȿ�� ������� Ȯ�� �� ���ÿ� push
void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return 0;  // �ε����� ������ ���� ���̹Ƿ� ����
	// ��('1')�� �ƴϰ� �湮�� ���� ���� ��ġ('.')�� �ƴϸ�
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;  // �ӽ� ��ġ ����ü ����
		tmp.r = r;    // �� ����
		tmp.c = c;    // �� ����
		push(s, tmp); // ���ÿ� push
	}
}

// �̷� ���¸� ����ϴ� �Լ�
void maze_printf(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");  // �ٹٲ�
	for (int r = 0; r < MAZE_SIZE; r++) {        // �� ��ȸ
		for (int c = 0; c < MAZE_SIZE; c++) {    // �� ��ȸ
			printf("%c", maze[r][c]);           // �� ��ġ�� ���� ���
		}
		printf("\n");  // �� �� ������ �ٹٲ�
	}
}

// ���� �Լ�
int main(void)
{
	int r, c;            // ���� ��ġ ��ǥ �����
	StackType s;         // ���� ���� ����

	init_stack(&s);      // ���� �ʱ�ȭ
	here = entry;        // ���� ��ġ�� �Ա�(entry)�� �ʱ�ȭ

	// �ⱸ('x')�� ã�� ������ �ݺ�
	while (maze[here.r][here.c] != 'x') {
		r = here.r;  // ���� ��ġ�� ��
		c = here.c;  // ���� ��ġ�� ��
		maze[r][c] = '.';  // ���� ��ġ�� ������ ��η� ǥ��
		maze_printf(maze);  // ���� �̷� ���� ���

		// �����¿� �������� �̵� ������ ��ġ���� ���ÿ� push
		push_loc(&s, r - 1, c);  // ����
		push_loc(&s, r + 1, c);  // �Ʒ���
		push_loc(&s, r, c - 1);  // ����
		push_loc(&s, r, c + 1);  // ������

		if (is_empty(&s)) {      // �� �̻� �� ���� ������
			printf("����\n");     // ���� �޽��� ���
			return;              // ���α׷� ����
		}
		else
			here = pop(&s);  // ���� ��ġ�� �̵� (���ÿ��� pop)
	}

	printf("����\n");  // �ⱸ�� �����ϸ� ���� �޽��� ���
	return 0;         // ���α׷� ����
}
