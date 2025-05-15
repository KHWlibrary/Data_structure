#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 1000  // 최대 정점 개수 정의

// 인접 리스트의 노드를 나타내는 구조체
typedef struct GraphNode {
	int vertex;  // 연결된 정점 번호
	struct GraphNode* link;  // 다음 노드를 가리키는 포인터
} GraphNode;

// 그래프 전체를 나타내는 구조체
typedef struct GraphType {
	int n;  // 현재 정점의 수
	GraphNode* adj_list[MAX_VERTICES];  // 인접 리스트 배열
} GraphType;

// 그래프 초기화 함수
void init(GraphType* g)
{
	int v;
	g->n = 0;  // 정점 수 초기화
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;  // 모든 인접 리스트 포인터 NULL로 초기화
}

// 정점 삽입 함수
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {  // 정점 수 초과 검사
		fprintf(stderr, "그래프: 정점의 개수 초과\n");
		return;
	}
	g->n++;  // 정점 수 증가
}

// 간선 삽입 함수 (단방향)
void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node;
	if (u >= g->n || v >= g->n) {  // 존재하지 않는 정점에 대한 간선 검사
		fprintf(stderr, "그래프: 정점 번호 오류\n");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));  // 새 노드 생성
	node->vertex = v;  // 연결할 정점 설정
	node->link = g->adj_list[u];  // 기존 리스트와 연결
	g->adj_list[u] = node;  // 새 노드를 리스트의 앞에 삽입
}

// 인접 리스트 출력 함수
void print_adj_mat(GraphType* g)
{
	for (int i = 0; i < g->n; i++) {  // 모든 정점에 대해
		GraphNode* p = g->adj_list[i];  // 정점 i의 인접 리스트 시작
		printf("정점 %d의 인접 리스트", i);
		while (p != NULL) {  // 인접 노드 순회
			printf("-> %d", p->vertex);  // 연결된 정점 출력
			p = p->link;  // 다음 노드로 이동
		}
		printf("\n");  // 한 정점의 인접 리스트 출력 후 줄바꿈
	}
}

// 브리지를 찾기 위한 DFS 함수
void dfs_bridge(GraphType* g, int u, int parent, int* visited, int* discovery, int* low, int* time) {
	visited[u] = 1;  // 정점 u 방문 표시
	discovery[u] = low[u] = ++(*time);  // discovery와 low 타임스탬프 설정

	GraphNode* p = g->adj_list[u];  // 인접 리스트 탐색
	while (p != NULL) {
		int v = p->vertex;
		if (!visited[v]) {  // 방문하지 않은 정점이라면
			dfs_bridge(g, v, u, visited, discovery, low, time);  // DFS 재귀 호출
			low[u] = (low[u] < low[v]) ? low[u] : low[v];  // low 갱신

			// 브리지 조건 검사: 자식 v에서 부모 u로 돌아갈 경로가 없는 경우
			if (low[v] > discovery[u]) {
				printf("브리지 간선: (%d, %d)\n", u, v);  // 브리지 출력
			}
		}
		else if (v != parent) {  // 방문했지만 부모가 아닌 경우(역방향 간선)
			low[u] = (low[u] < discovery[v]) ? low[u] : discovery[v];  // low 갱신
		}
		p = p->link;  // 다음 인접 노드로 이동
	}
}

// 모든 정점에서 브리지를 찾는 함수
void find_bridges(GraphType* g) {
	int visited[MAX_VERTICES] = { 0 };  // 방문 여부 배열
	int discovery[MAX_VERTICES] = { 0 };  // 발견 시간 배열
	int low[MAX_VERTICES] = { 0 };  // 최소 도달 시간 배열
	int time = 0;  // DFS 타임스탬프

	for (int i = 0; i < g->n; i++) {
		if (!visited[i])  // 방문하지 않은 정점에 대해서만 DFS 수행
			dfs_bridge(g, i, -1, visited, discovery, low, &time);  // 부모는 -1로 시작
	}
}

// 메인 함수
void main()
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));  // 그래프 동적 할당
	init(g);  // 그래프 초기화

	// 정점 0~9 삽입
	for (int i = 0; i < 10; i++)
		insert_vertex(g, i);

	// 무방향 그래프 생성 (양방향 간선 추가)
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

	print_adj_mat(g);  // 인접 리스트 출력

	printf("\n[브리지 탐색 결과]\n");  // 결과 출력 안내
	find_bridges(g);  // 브리지 탐색 수행

	free(g);  // 메모리 해제
}
