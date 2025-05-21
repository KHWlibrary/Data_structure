#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 100

// 역 노드 정의 (양방향 연결 리스트 + 거리 + 시간 가중치)
typedef struct Station {
    char name[NAME_LEN];
    struct Station* next;
    struct Station* prev;
    int nextDistance; // 다음 역까지의 거리
    int prevDistance; // 이전 역까지의 거리
    int timeWeight;   // 다음 역까지의 시간 가중치 (예: 분)
} Station;

// 노선 정의
typedef struct Line {
    int lineNumber;
    Station* head;
} Line;

// 노선 생성
Line* createLine(int lineNumber) {
    Line* line = (Line*)malloc(sizeof(Line));
    line->lineNumber = lineNumber;
    line->head = NULL;
    return line;
}

// 역 추가 (거리 및 시간 가중치 포함)
void addStation(Line* line, const char* stationName, int distanceFromPrev, int timeWeight) {
    Station* newStation = (Station*)malloc(sizeof(Station));
    strcpy(newStation->name, stationName);
    newStation->next = NULL;
    newStation->prev = NULL;
    newStation->nextDistance = 0; // 초기화, 다음 역 연결 시 설정
    newStation->prevDistance = distanceFromPrev;
    newStation->timeWeight = timeWeight; // 시간 가중치 설정

    if (line->head == NULL) {
        line->head = newStation;
    }
    else {
        Station* current = line->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStation;
        current->nextDistance = distanceFromPrev; // 현재 역에서 다음 역까지의 거리 설정
        current->timeWeight = timeWeight;         // 현재 역에서 다음 역까지의 시간 가중치 설정
        newStation->prev = current;
    }
}

// 노선 출력 (정방향)
void printLine(Line* line) {
    printf("%d호선 (정방향): ", line->lineNumber);
    Station* current = line->head;
    while (current != NULL) {
        printf("%s", current->name);
        if (current->next != NULL)
            printf(" -[D:%dkm, T:%dmin]-> ", current->nextDistance, current->timeWeight); // 거리와 시간 가중치 출력
        current = current->next;
    }
    printf("\n");
}

// 노선 출력 (역방향)
void printLineReverse(Line* line) {
    printf("%d호선 (역방향): ", line->lineNumber);
    Station* current = line->head;
    if (current == NULL) {
        printf("없음\n");
        return;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    while (current != NULL) {
        printf("%s", current->name);
        // 역방향 출력 시, 이전 역까지의 거리와 시간 가중치를 사용
        // prevDistance는 이전 역까지의 거리, prevStation->timeWeight는 이전 역에서 현재 역까지의 시간
        if (current->prev != NULL)
            printf(" -[D:%dkm, T:%dmin]-> ", current->prevDistance, current->prev->timeWeight);
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

// 노선 설정 (역 이름과 거리/시간 배열로부터 생성)
void setupLine(Line* line, const char* stations[], const int distances[], int count) {
    for (int i = 0; i < count; i++) {
        // 첫 번째 역은 이전 역이 없으므로 distance와 timeWeight를 0으로 설정
        int distance = (i == 0) ? 0 : distances[i - 1];
        int timeWeight = (i == 0) ? 0 : distances[i - 1]; // 여기서는 거리 배열을 시간 가중치로 재활용
        // 실제 상황에서는 별도의 시간 배열을 사용하는 것이 좋습니다.
        addStation(line, stations[i], distance, timeWeight);
    }
}

int main() {
    const char* line1Stations[] = {
        "소요산", "동두천", "보산", "동두천중앙", "지행",
        "덕정", "덕계", "양주", "녹양", "가능",
        "의정부", "회룡", "망월사", "도봉", "도봉산",
        "방학", "창동", "녹천", "월계", "광운대",
        "석계", "신이문", "외대앞", "회기", "청량리",
        "제기동", "신설동", "동묘앞", "동대문", "종로5가",
        "종로3가", "종각", "시청", "서울역", "남영",
        "용산", "노량진", "대방", "신길", "영등포",
        "신도림", "구로", "구일", "개봉", "오류동",
        "온수", "역곡", "소사", "부천", "중동",
        "송내", "부개", "부평", "백운", "동암",
        "간석", "주안", "도화", "제물포", "도원",
        "동인천", "인천"
    };
    int line1Count = sizeof(line1Stations) / sizeof(line1Stations[0]);
    const int line1Distances[] = { 3, 2, 2, 1, 2, 2, 3, 2, 2, 2,
        2, 3, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2 }; // 예시 거리 (이제 시간 가중치로도 사용)

    const char* line2Stations[] = {
        "시청", "을지로입구", "을지로3가", "을지로4가", "동대문역사문화공원",
        "신당", "상왕십리", "왕십리", "한양대", "뚝섬",
        "성수", "건대입구", "구의", "강변", "잠실나루",
        "잠실", "잠실새내", "종합운동장", "삼성", "선릉",
        "역삼", "강남", "교대", "서초", "방배",
        "사당", "낙성대", "서울대입구", "봉천", "신림",
        "신대방", "구로디지털단지", "대림", "신도림", "문래",
        "영등포구청", "당산", "합정", "홍대입구", "신촌",
        "이대", "아현", "충정로"
    };
    int line2Count = sizeof(line2Stations) / sizeof(line2Stations[0]);
    const int line2Distances[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1 }; // 예시 거리 (이제 시간 가중치로도 사용)

    const char* line3Stations[] = {
        "대화", "주엽", "정발산", "마두", "백석",
        "대곡", "화정", "원당", "원흥", "삼송",
        "지축", "구파발", "연신내", "불광", "녹번",
        "홍제", "무악재", "독립문", "경복궁", "안국",
        "종로3가", "을지로3가", "충무로", "동대입구", "약수",
        "금호", "옥수", "압구정", "신사", "잠원",
        "고속터미널", "교대", "남부터미널", "양재", "매봉",
        "도곡", "대치", "학여울", "대청", "일원",
        "수서", "가락시장", "경찰병원", "오금"
    };
    int line3Count = sizeof(line3Stations) / sizeof(line3Stations[0]);
    const int line3Distances[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2 }; // 예시 거리 (이제 시간 가중치로도 사용)

    const char* line4Stations[] = {
        "진접", "오남", "별내별가람", "당고개", "상계",
        "노원", "창동", "쌍문", "수유", "미아",
        "미아사거리", "길음", "성신여대입구", "한성대입구", "혜화",
        "동대문", "동대문역사문화문화공원", "충무로", "명동", "회현",
        "서울역", "숙대입구", "삼각지", "신용산", "이촌",
        "동작", "총신대입구", "사당", "남태"
    };
    int line4Count = sizeof(line4Stations) / sizeof(line4Stations[0]);
    const int line4Distances[] = { 3, 3, 4, 2, 3, 3, 4, 2, 3,
        3, 4, 2, 3, 3, 4, 2, 3, 3, 4,
        2, 3, 3, 4, 2, 3, 3, 4, 2, 3, 3, 4, 2 }; // 예시 거리 (이제 시간 가중치로도 사용)


    Line* line1 = createLine(1);
    Line* line2 = createLine(2);
    Line* line3 = createLine(3);
    Line* line4 = createLine(4);

    setupLine(line1, line1Stations, line1Distances, line1Count);
    setupLine(line2, line2Stations, line2Distances, line2Count);
    setupLine(line3, line3Stations, line3Distances, line3Count);
    setupLine(line4, line4Stations, line4Distances, line4Count);

    printLine(line1);
    printLineReverse(line1);
    printf("\n"); // 줄바꿈 추가
    printLine(line2);
    printLineReverse(line2);
    printf("\n"); // 줄바꿈 추가
    printLine(line3);
    printLineReverse(line3);
    printf("\n"); // 줄바꿈 추가
    printLine(line4);
    printLineReverse(line4);
    printf("\n"); // 줄바꿈 추가

    freeLine(line1);
    freeLine(line2);
    freeLine(line3);
    freeLine(line4);

    return 0;
}