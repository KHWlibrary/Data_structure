#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 보안 경고를 비활성화합니다.

#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h> // strcpy, strcmp

#define NAME_LEN 100 // 역 이름의 최대 길이

// 역 노드 정의 (이중 연결 리스트 + 거리 및 시간 가중치 + 환승 정보)
typedef struct Station {
    char name[NAME_LEN];
    struct Station* next;         // 다음 역을 가리키는 포인터
    struct Station* prev;         // 이전 역을 가리키는 포인터
    int nextDistance;             // 현재 역에서 다음 역까지의 거리 가중치 (km)
    int nextTimeWeight;           // 현재 역에서 다음 역까지의 시간 가중치 (분)
    struct Station* transfers[5]; // 최대 5개의 환승 노선 (예시)
    int transferCount;            // 환승 노선 수
} Station;

// 노선 정의
typedef struct Line {
    int lineNumber;
    Station* head;                // 노선의 첫 역
    Station* tail;                // 노선의 마지막 역 (역방향 탐색 및 추가에 용이)
} Line;

// 노선 생성 함수
Line* createLine(int lineNumber) {
    Line* line = (Line*)malloc(sizeof(Line));
    if (line == NULL) {
        perror("메모리 할당 실패");
        exit(EXIT_FAILURE);
    }
    line->lineNumber = lineNumber;
    line->head = NULL;
    line->tail = NULL; // tail도 초기화
    return line;
}

// 역 추가 함수 (거리 및 시간 가중치 포함)
// stationName: 추가할 역 이름
// distToNext: 현재 추가하는 역에서 "다음" 역까지의 거리 (이전 역의 nextDistance로 사용됨)
// timeToNext: 현재 추가하는 역에서 "다음" 역까지의 시간 (이전 역의 nextTimeWeight로 사용됨)
void addStation(Line* line, const char* stationName, int distToPrev, int timeToPrev) {
    Station* newStation = (Station*)malloc(sizeof(Station));
    if (newStation == NULL) {
        perror("메모리 할당 실패");
        exit(EXIT_FAILURE);
    }
    strcpy(newStation->name, stationName);
    newStation->next = NULL;
    newStation->prev = NULL;
    newStation->nextDistance = 0; // 초기화, 다음 역 연결 시 설정
    newStation->nextTimeWeight = 0; // 초기화, 다음 역 연결 시 설정
    newStation->transferCount = 0;   // 환승 정보 초기화

    if (line->head == NULL) { // 노선에 첫 역 추가
        line->head = newStation;
        line->tail = newStation;
    }
    else { // 노선에 역 추가
        line->tail->next = newStation;     // 현재 마지막 역의 다음 역으로 새 역 연결
        line->tail->nextDistance = distToPrev; // 현재 마지막 역에서 새 역까지의 거리 설정
        line->tail->nextTimeWeight = timeToPrev; // 현재 마지막 역에서 새 역까지의 시간 가중치 설정
        newStation->prev = line->tail;     // 새 역의 이전 역으로 현재 마지막 역 연결
        line->tail = newStation;           // 노선의 마지막 역을 새 역으로 갱신
    }
}

// 환승역 연결 함수
// station1과 station2는 동일한 이름을 가진 다른 노선의 역 노드입니다.
void connectTransfer(Station* station1, Station* station2) {
    if (station1->transferCount < 5 && station2->transferCount < 5) {
        station1->transfers[station1->transferCount++] = station2;
        station2->transfers[station2->transferCount++] = station1;
    }
    else {
        printf("오류: 환승역 연결 실패 (최대 환승 노선 수 초과: %s, %s)\n", station1->name, station2->name);
    }
}

// 노선 설정 (역 이름, 거리 배열, 시간 배열로부터 노드 생성)
// distances: 각 역과 "다음" 역 사이의 거리 (N-1개)
// timeWeights: 각 역과 "다음" 역 사이의 시간 (N-1개)
void setupLine(Line* line, const char* stationNames[], const int distances[], const int timeWeights[], int count) {
    // 첫 역은 가중치가 없으므로 (이전 역이 없으므로) 0으로 추가
    addStation(line, stationNames[0], 0, 0);

    // 두 번째 역부터는 이전 역과의 가중치를 사용하여 추가
    for (int i = 1; i < count; i++) {
        // addStation의 distToPrev, timeToPrev는 사실상 이전 역의 nextDistance, nextTimeWeight가 됩니다.
        addStation(line, stationNames[i], distances[i - 1], timeWeights[i - 1]);
    }
}

// 노선 출력 (정방향)
void printLine(Line* line) {
    printf("%d호선 (정방향): ", line->lineNumber);
    Station* current = line->head;
    while (current != NULL) {
        printf("%s", current->name);
        if (current->transferCount > 0) {
            printf(" (환승: ");
            for (int i = 0; i < current->transferCount; i++) {
                printf("%s", current->transfers[i]->name);
                if (i < current->transferCount - 1) {
                    printf(", ");
                }
            }
            printf(")");
        }
        if (current->next != NULL) {
            printf(" -[D:%dkm, T:%dmin]-> ", current->nextDistance, current->nextTimeWeight);
        }
        current = current->next;
    }
    printf("\n");
}

// 노선 출력 (역방향)
void printLineReverse(Line* line) {
    printf("%d호선 (역방향): ", line->lineNumber);
    Station* current = line->tail; // tail부터 시작
    while (current != NULL) {
        printf("%s", current->name);
        if (current->transferCount > 0) {
            printf(" (환승: ");
            for (int i = 0; i < current->transferCount; i++) {
                printf("%s", current->transfers[i]->name);
                if (i < current->transferCount - 1) {
                    printf(", ");
                }
            }
            printf(")");
        }
        if (current->prev != NULL) {
            // 역방향 출력 시, 현재 역의 'prev'가 가리키는 역의 'nextDistance'와 'nextTimeWeight'를 사용
            // 이는 'prev' 역에서 '현재' 역까지의 가중치를 의미합니다.
            printf(" -[D:%dkm, T:%dmin]-> ", current->prev->nextDistance, current->prev->nextTimeWeight);
        }
        current = current->prev;
    }
    printf("\n");
}

// 메모리 해제
void freeLine(Line* line) {
    Station* current = line->head;
    while (current != NULL) {
        Station* temp = current;
        current = current->next;
        free(temp);
    }
    free(line);
}

int main() {
    // 1호선 데이터
    const char* line1Stations[] = {
        "소요산", "동두천", "보산", "동두천중앙", "지행", "덕정", "덕계", "양주", "녹양", "가능",
        "의정부", "회룡", "망월사", "도봉", "도봉산", "방학", "창동", "녹천", "월계", "광운대",
        "석계", "신이문", "외대앞", "회기", "청량리", "제기동", "신설동", "동묘앞", "동대문", "종로5가",
        "종로3가", "종각", "시청", "서울역", "남영", "용산", "노량진", "대방", "신길", "영등포",
        "신도림", "구로", "구일", "개봉", "오류동", "온수", "역곡", "소사", "부천", "중동",
        "송내", "부개", "부평", "백운", "동암", "간석", "주안", "도화", "제물포", "도원",
        "동인천", "인천"
    };
    int line1Count = sizeof(line1Stations) / sizeof(line1Stations[0]);
    // 실제 거리가 아닌 예시 값입니다.
    const int line1Distances[] = { 3, 2, 2, 1, 2, 2, 3, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
    // 실제 시간이 아닌 예시 값입니다. (거리와 같게 설정)
    const int line1TimeWeights[] = { 3, 2, 2, 1, 2, 2, 3, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2,
                                    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };


    // 2호선 데이터
    const char* line2Stations[] = {
        "시청", "을지로입구", "을지로3가", "을지로4가", "동대문역사문화공원", "신당", "상왕십리", "왕십리", "한양대", "뚝섬",
        "성수", "건대입구", "구의", "강변", "잠실나루", "잠실", "잠실새내", "종합운동장", "삼성", "선릉",
        "역삼", "강남", "교대", "서초", "방배", "사당", "낙성대", "서울대입구", "봉천", "신림",
        "신대방", "구로디지털단지", "대림", "신도림", "문래", "영등포구청", "당산", "합정", "홍대입구", "신촌",
        "이대", "아현", "충정로"
    };
    int line2Count = sizeof(line2Stations) / sizeof(line2Stations[0]);
    const int line2Distances[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    const int line2TimeWeights[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    // 3호선 데이터
    const char* line3Stations[] = {
        "대화", "주엽", "정발산", "마두", "백석", "대곡", "화정", "원당", "원흥", "삼송",
        "지축", "구파발", "연신내", "불광", "녹번", "홍제", "무악재", "독립문", "경복궁", "안국",
        "종로3가", "을지로3가", "충무로", "동대입구", "약수", "금호", "옥수", "압구정", "신사", "잠원",
        "고속터미널", "교대", "남부터미널", "양재", "매봉", "도곡", "대치", "학여울", "대청", "일원",
        "수서", "가락시장", "경찰병원", "오금"
    };
    int line3Count = sizeof(line3Stations) / sizeof(line3Stations[0]);
    const int line3Distances[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2 };
    const int line3TimeWeights[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                    2, 2, 2 };

    // 4호선 데이터
    const char* line4Stations[] = {
        "진접", "오남", "별내별가람", "당고개", "상계", "노원", "창동", "쌍문", "수유", "미아",
        "미아사거리", "길음", "성신여대입구", "한성대입구", "혜화", "동대문", "동대문역사문화공원", "충무로", "명동", "회현",
        "서울역", "숙대입구", "삼각지", "신용산", "이촌", "동작", "총신대입구", "사당", "남태령"
    };
    int line4Count = sizeof(line4Stations) / sizeof(line4Stations[0]);
    const int line4Distances[] = { 3, 3, 4, 2, 3, 3, 4, 2, 3, 3,
                                   4, 2, 3, 3, 4, 2, 3, 3, 4, 2,
                                   3, 3, 4, 2, 3, 3, 4, 2 }; // 남태령 이후는 데이터가 없으므로 맞춤
    const int line4TimeWeights[] = { 3, 3, 4, 2, 3, 3, 4, 2, 3, 3,
                                    4, 2, 3, 3, 4, 2, 3, 3, 4, 2,
                                    3, 3, 4, 2, 3, 3, 4, 2 }; // 남태령 이후는 데이터가 없으므로 맞춤


    Line* line1 = createLine(1);
    Line* line2 = createLine(2);
    Line* line3 = createLine(3);
    Line* line4 = createLine(4);

    setupLine(line1, line1Stations, line1Distances, line1TimeWeights, line1Count);
    setupLine(line2, line2Stations, line2Distances, line2TimeWeights, line2Count);
    setupLine(line3, line3Stations, line3Distances, line3TimeWeights, line3Count);
    setupLine(line4, line4Stations, line4Distances, line4TimeWeights, line4Count);

    // 환승역을 찾기 위한 포인터 선언
    Station* 동대문1 = NULL;
    Station* 동대문4 = NULL;
    Station* 종로3가1 = NULL;
    Station* 종로3가3 = NULL;
    Station* 서울역1 = NULL;
    Station* 서울역4 = NULL;
    Station* 신도림1 = NULL;
    Station* 신도림2 = NULL;
    Station* 교대2 = NULL;
    Station* 교대3 = NULL;
    Station* 충무로3 = NULL;
    Station* 충무로4 = NULL;
    Station* 동대문역사문화공원2 = NULL;
    Station* 동대문역사문화공원4 = NULL;
    Station* 을지로3가2 = NULL;
    Station* 을지로3가3 = NULL;

    // 각 노선에서 환승역 찾기
    Station* current;

    current = line1->head;
    while (current != NULL) {
        if (strcmp(current->name, "동대문") == 0) 동대문1 = current;
        else if (strcmp(current->name, "종로3가") == 0) 종로3가1 = current;
        else if (strcmp(current->name, "서울역") == 0) 서울역1 = current;
        else if (strcmp(current->name, "신도림") == 0) 신도림1 = current;
        current = current->next;
    }

    current = line2->head;
    while (current != NULL) {
        if (strcmp(current->name, "시청") == 0) { /* 시청 1호선과 2호선 환승은 이미 연결된 노선 상의 역이므로 추가적인 연결 필요 없음 */ }
        else if (strcmp(current->name, "을지로3가") == 0) 을지로3가2 = current;
        else if (strcmp(current->name, "동대문역사문화공원") == 0) 동대문역사문화공원2 = current;
        else if (strcmp(current->name, "신도림") == 0) 신도림2 = current;
        else if (strcmp(current->name, "교대") == 0) 교대2 = current;
        current = current->next;
    }

    current = line3->head;
    while (current != NULL) {
        if (strcmp(current->name, "종로3가") == 0) 종로3가3 = current;
        else if (strcmp(current->name, "을지로3가") == 0) 을지로3가3 = current;
        else if (strcmp(current->name, "충무로") == 0) 충무로3 = current;
        else if (strcmp(current->name, "교대") == 0) 교대3 = current;
        current = current->next;
    }

    current = line4->head;
    while (current != NULL) {
        if (strcmp(current->name, "동대문") == 0) 동대문4 = current;
        else if (strcmp(current->name, "동대문역사문화공원") == 0) 동대문역사문화공원4 = current;
        else if (strcmp(current->name, "충무로") == 0) 충무로4 = current;
        else if (strcmp(current->name, "서울역") == 0) 서울역4 = current;
        current = current->next;
    }

    // 환승역 연결
    if (동대문1 && 동대문4) connectTransfer(동대문1, 동대문4);
    if (종로3가1 && 종로3가3) connectTransfer(종로3가1, 종로3가3);
    if (서울역1 && 서울역4) connectTransfer(서울역1, 서울역4);
    if (신도림1 && 신도림2) connectTransfer(신도림1, 신도림2);
    if (교대2 && 교대3) connectTransfer(교대2, 교대3);
    if (충무로3 && 충무로4) connectTransfer(충무로3, 충무로4);
    if (동대문역사문화공원2 && 동대문역사문화공원4) connectTransfer(동대문역사문화공원2, 동대문역사문화공원4);
    if (을지로3가2 && 을지로3가3) connectTransfer(을지로3가2, 을지로3가3);


    printf("--- 지하철 노선 정보 ---\n\n");

    printLine(line1);
    printLineReverse(line1);
    printf("\n");

    printLine(line2);
    printLineReverse(line2);
    printf("\n");

    printLine(line3);
    printLineReverse(line3);
    printf("\n");

    printLine(line4);
    printLineReverse(line4);
    printf("\n");

    // 메모리 해제
    freeLine(line1);
    freeLine(line2);
    freeLine(line3);
    freeLine(line4);

    return 0;
}