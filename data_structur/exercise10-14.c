#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 1000

typedef struct Graph {
	int n;	//정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}Graph;

//그래프 초기화
void init(Graph* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)		//행
		for (c = 0; c < MAX_VERTICES; c++)	//열
			g->adj_mat[r][c] = 0;
}
//정점 삽입 연산
void insert_vertex(Graph* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과\n");
		return;
	}
	g->n++;
}

//간선 삽입 연산
void insert_edge(Graph* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류\n");
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

//인접 행열 출력 함수
void print_adj_mat(Graph* g)
{
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}
void main()
{
	Graph* g;
	g = (Graph*)malloc(sizeof(Graph));
	init(g);
	for (int i = 0; i < 4; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 1);
	insert_edge(g, 1, 0);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 1, 3);
	insert_edge(g, 3, 1);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 2);
	insert_edge(g, 3, 4);
	insert_edge(g, 4, 3);
	insert_edge(g, 3, 5);
	insert_edge(g, 5, 3);
	insert_edge(g, 5, 7);
	insert_edge(g, 7, 5);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 5);
	insert_edge(g, 6, 7);
	insert_edge(g, 7, 6);
	insert_edge(g, 7, 8);
	insert_edge(g, 8, 7);
	insert_edge(g, 7, 9);
	insert_edge(g, 9, 7);
	print_adj_mat(g);

	free(g);
}