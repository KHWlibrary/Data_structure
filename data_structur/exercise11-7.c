#include <stdio.h>      // 입출력을 위한 헤더 파일
#include <stdlib.h>     // 동적 메모리 할당을 위한 헤더 파일
#include <limits.h>     // INT_MAX 사용을 위한 헤더 파일

#define TRUE 1          // TRUE를 1로 정의
#define FALSE 0         // FALSE를 0으로 정의
#define MAX_VERTICES 100 // 최대 정점 개수 정의
#define INF 100000      // 무한대 (연결되지 않은 경우 사용할 값)

// 인접 리스트에 사용할 간선 노드 구조체 정의
typedef struct Node {
    int vertex;         // 연결된 정점 번호
    int weight;         // 간선의 가중치
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;

// 그래프 구조체 정의 (인접 리스트 방식)
typedef struct GraphType {
    int n;              // 정점의 개수
    Node* adj[MAX_VERTICES]; // 각 정점의 인접 리스트를 가리키는 포인터 배열
} GraphType;

// 시작 정점으로부터 각 정점까지의 최단 거리 저장 배열
int distance[MAX_VERTICES];

// 정점이 방문되었는지 여부를 저장하는 배열
int found[MAX_VERTICES];

// 간선 삽입 함수: u에서 v로 weight 가중치를 가진 간선을 추가
void insert_edge(GraphType* g, int u, int v, int w) {
    Node* node = (Node*)malloc(sizeof(Node)); // 새로운 노드 동적 할당
    node->vertex = v;     // 도착 정점 번호 저장
    node->weight = w;     // 가중치 저장
    node->next = g->adj[u]; // 현재 u의 인접 리스트에 삽입
    g->adj[u] = node;     // 리스트 헤드를 새 노드로 갱신
}

// 아직 방문하지 않은 정점 중 가장 작은 distance 값을 가진 정점 선택
int choose(int distance[], int n, int found[]) {
    int min = INT_MAX;    // 최소값을 찾기 위해 초기값 설정
    int minpos = -1;      // 최소 위치 인덱스 저장
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i]; // 더 작은 값을 찾으면 갱신
            minpos = i;
        }
    }
    return minpos; // 최소 거리 정점 반환
}

// 현재 상태를 출력하는 디버깅 함수
void print_status(GraphType* g) {
    static int step = 1;  // 단계별 출력용 변수
    printf("STEP %d:\n", step++);

    // 거리 배열 출력
    printf(" distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf("  * ");  // 무한대는 *로 표시
        else
            printf("%3d ", distance[i]); // 정렬된 정수 출력
    }

    // 방문 여부 배열 출력
    printf("\n found:    ");
    for (int i = 0; i < g->n; i++)
        printf("%3d ", found[i]);
    printf("\n\n");
}

// Dijkstra 최단 경로 알고리즘 (인접 리스트 기반)
void shortest_path(GraphType* g, int start) {
    // 거리 및 방문 배열 초기화
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;   // 모든 거리를 무한대로 초기화
        found[i] = FALSE;    // 방문 여부 초기화
    }

    distance[start] = 0;     // 시작 정점은 거리 0으로 설정

    // 정점의 수만큼 반복
    for (int i = 0; i < g->n; i++) {
        print_status(g);     // 현재 상태 출력

        int u = choose(distance, g->n, found); // 최소 거리 정점 선택
        found[u] = TRUE;      // 선택된 정점을 방문 처리

        // 선택된 정점 u의 모든 인접 정점에 대해 거리 갱신 시도
        for (Node* p = g->adj[u]; p != NULL; p = p->next) {
            int v = p->vertex; // 인접 정점 번호
            if (!found[v] && distance[u] + p->weight < distance[v]) {
                distance[v] = distance[u] + p->weight; // 거리 갱신
            }
        }
    }
}

// main 함수: 그래프 생성 및 최단 경로 실행
int main(void) {
    GraphType g;
    g.n = 7; // 정점의 개수 설정

    // 인접 리스트 초기화
    for (int i = 0; i < g.n; i++)
        g.adj[i] = NULL;

    insert_edge(&g, 0, 1, 50); insert_edge(&g, 0, 2, 45); insert_edge(&g, 0, 3, 10);
    insert_edge(&g, 1, 3, 15); insert_edge(&g, 1, 2, 10);
    insert_edge(&g, 2, 4, 30); 
    insert_edge(&g, 3, 0, 20); insert_edge(&g, 3, 4, 15); 
    insert_edge(&g, 4, 1, 20); insert_edge(&g, 4, 2, 35); 
    insert_edge(&g, 5, 4, 3); 

    shortest_path(&g, 0); // 정점 0에서 시작하는 최단 경로 계산

    return 0; // 프로그램 종료
}
    