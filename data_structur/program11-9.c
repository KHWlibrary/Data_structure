#include <stdio.h>    // 표준 입출력 함수 사용을 위한 헤더 파일
#include <stdlib.h>   // 일반적인 유틸리티 함수들 (예: malloc, free 등)을 위한 헤더 파일

// 상수 정의
#define TRUE 1                 // 논리적 참을 의미 (선택됨)
#define FALSE 0                // 논리적 거짓을 의미 (선택되지 않음)
#define MAX_VERTICES 100       // 그래프에 포함될 수 있는 최대 정점 수
#define INF 1000L              // 간선이 없음을 나타내는 무한대 값 (연결되지 않음을 의미)

// 그래프 정보를 담는 구조체 정의
typedef struct GraphType {
	int n;                                   // 그래프 내 정점의 수
	int weight[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬: 각 정점 간 간선의 가중치를 저장
} GraphType;

// 전역 배열 선언
int selected[MAX_VERTICES]; // 각 정점이 최소 신장 트리에 포함되었는지 여부를 저장
int distance[MAX_VERTICES]; // 최소 신장 트리 집합까지의 최소 거리 값을 저장

// 현재 최소 거리 값을 갖는, 아직 선택되지 않은 정점을 찾아 반환하는 함수
int get_min_vertex(int n)
{
	int v, i;

	// 선택되지 않은 정점 중 첫 번째 정점을 초기값으로 설정
	for (i = 0; i < n; i++) {
		if (!selected[i]) {   // selected[i]가 FALSE(=0)라면 아직 선택되지 않은 정점
			v = i;
			break;
		}
	}

	// 선택되지 않은 정점 중에서 가장 작은 distance 값을 갖는 정점을 찾음
	for (i = 0; i < n; i++) {
		if (!selected[i] && distance[i] < distance[v]) {
			v = i;
		}
	}

	return v; // 최소 거리 값을 가진 정점의 인덱스를 반환
}

// Prim 알고리즘을 수행하여 최소 신장 트리를 만드는 함수
void prim(GraphType* g, int s)
{
	int i, u, v;

	// 시작 시 모든 정점까지의 거리를 무한대로 초기화
	for (u = 0; u < g->n; u++)
		distance[u] = INF;

	distance[s] = 0; // 시작 정점은 자기 자신까지의 거리이므로 0으로 설정

	// 모든 정점을 하나씩 트리에 추가할 때까지 반복
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n); // 최소 거리 정점을 선택
		selected[u] = TRUE;       // 해당 정점을 트리에 포함시킴

		// 만약 선택된 정점의 거리가 여전히 무한대라면, 그래프가 연결되어 있지 않음
		if (distance[u] == INF) return;

		printf("정점 %d 추가\n", u); // 트리에 추가된 정점을 출력

		// 선택된 정점 u와 연결된 모든 정점 v를 확인
		for (v = 0; v < g->n; v++) {
			// u와 v 사이에 간선이 존재하고 (가중치가 INF가 아님)
			// v가 아직 트리에 포함되지 않았고
			// u를 통해 v로 가는 경로가 현재 알려진 거리보다 짧다면
			if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
				distance[v] = g->weight[u][v]; // 더 짧은 거리로 갱신
			}
		}
	}
}

// 메인 함수: 프로그램의 시작점
int main(void)
{
	// 정점 7개로 구성된 가중치 인접 행렬 기반의 그래프 초기화
	// INF는 연결되지 않았음을 의미
	GraphType g = { 7,
	{{0,  29, INF, INF, INF, 10, INF},  // 정점 0과의 간선 가중치
	 {29, 0,  16,  INF, INF, INF, 15},  // 정점 1
	 {INF, 16, 0,  12, INF, INF, INF},  // 정점 2
	 {INF, INF, 12, 0,  22, INF, 18},   // 정점 3
	 {INF, INF, INF, 22, 0,  27, 25},   // 정점 4
	 {10, INF, INF, INF, 27, 0,  INF},  // 정점 5
	 {INF, 15, INF, 18, INF, 25, 0}}    // 정점 6
	};

	prim(&g, 0); // Prim 알고리즘 실행, 시작 정점은 0번

	return 0; // 프로그램 정상 종료
}
