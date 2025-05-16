// Kruskal의 최소 비용 신장 트리 프로그램

#include<stdio.h>   // 표준 입출력 함수 사용을 위한 헤더
#include<stdlib.h>  // 동적 메모리 할당, qsort 등을 위한 헤더

// 상수 정의
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100  // 최대 정점 수
#define INF 1000          // 무한대 값을 의미하는 상수

int parent[MAX_VERTICES];  // 서로소 집합(Union-Find)에서 각 정점의 부모를 저장

// 서로소 집합 초기화 함수: 모든 정점의 부모를 -1로 설정 (자기 자신이 루트)
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

// 특정 노드 curr의 루트(최상위 부모)를 찾는 함수 (Find 연산)
// 이 구현은 경로 압축이 없는 기본 형태임
int set_find(int curr)
{
	if (parent[curr] != -1)     // 루트가 아니라면
		return curr;            // 현재 노드가 루트인 경우 그대로 반환
	while (parent[curr] != -1)   // 루트 노드를 찾기 위해 부모를 따라 올라감
		curr = parent[curr];
	return curr;                // 루트 노드 반환
}

// 두 집합을 합치는 함수 (Union 연산)
// a와 b가 속한 집합을 하나로 합침
void set_union(int a, int b)
{
	int root1 = set_find(a);   // 정점 a의 루트를 찾음
	int root2 = set_find(b);   // 정점 b의 루트를 찾음
	if (root1 != root2)        // 서로 다른 집합이라면
		parent[root1] = root2; // root1의 부모를 root2로 설정 → 집합 합침
}

// 간선을 나타내는 구조체
struct Edge {
	int start;   // 간선의 시작 정점
	int end;     // 간선의 끝 정점
	int weight;  // 간선의 가중치
};

// 그래프 구조체: 간선 리스트로 표현됨
typedef struct GraphType {
	int n;                         // 현재 간선의 수
	struct Edge edges[2 * MAX_VERTICES]; // 간선 배열 (최대 200개까지 저장 가능)
} GraphType;

// 그래프 초기화 함수: 간선 개수 0, 간선 배열 초기화
void graph_init(GraphType* g)
{
	g->n = 0;  // 간선 수 초기화
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;  // 기본적으로 간선 가중치를 무한대로 초기화
	}
}

// 간선을 그래프에 추가하는 함수
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;  // 시작 정점 설정
	g->edges[g->n].end = end;      // 끝 정점 설정
	g->edges[g->n].weight = w;     // 가중치 설정
	g->n++;                        // 간선 수 1 증가
}

// qsort에 사용될 비교 함수: 간선을 가중치 기준으로 오름차순 정렬
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);  // 가중치 기준 정렬
}

// Kruskal 알고리즘 실행 함수
void kruskal(GraphType* g)
{
	int edge_accepted = 0;  // 선택된 간선의 개수
	int uset, vset;         // 간선의 양 끝 정점이 속한 집합 번호
	struct Edge e;          // 현재 선택된 간선

	set_init(g->n);  // 서로소 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);  // 간선 정렬

	printf("크루스칼  최소 신장 트리 알고리즘 \n");

	int i = 0;  // 간선 배열 인덱스 초기화
	// 신장 트리는 정점 수 - 1개의 간선만 필요하므로, 그만큼 반복
	while (edge_accepted < (g->n - 1))
	{
		e = g->edges[i];           // 현재 간선 선택
		uset = set_find(e.start); // 시작 정점이 속한 집합
		vset = set_find(e.end);   // 끝 정점이 속한 집합

		if (uset != vset) {  // 두 정점이 다른 집합에 속한다면 사이클이 아님
			printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
			edge_accepted++;         // 간선 선택 수 증가
			set_union(uset, vset);  // 두 집합을 합침
		}
		i++;  // 다음 간선으로 이동
	}
}

// 메인 함수: 프로그램 시작점
int main(void)
{
	GraphType* g;  // 그래프 포인터 선언
	g = (GraphType*)malloc(sizeof(GraphType));  // 동적 메모리 할당
	graph_init(g);  // 그래프 초기화

	// 그래프에 간선 삽입 (시작, 끝, 가중치)
	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);

	kruskal(g);  // Kruskal 알고리즘 실행하여 MST 생성

	free(g);     // 동적 할당된 메모리 해제
	return 0;    // 프로그램 종료
}
