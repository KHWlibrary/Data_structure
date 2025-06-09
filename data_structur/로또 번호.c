#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_NUMBERS 45
#define PICK_COUNT 6
#define LINE_COUNT 10
#define MAX_LINE_LENGTH 100
#define MAX_FREQUENT 10

typedef struct {
    int number;
    int count;
} LottoStat;

int frequentNumbers[MAX_FREQUENT];

// 배열에 값이 있는지 확인
int isInArray(int* arr, int size, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) return 1;
    }
    return 0;
}

// 정렬용 함수 (출현 횟수 기준 내림차순)
int compareStats(const void* a, const void* b) {
    return ((LottoStat*)b)->count - ((LottoStat*)a)->count;
}

// 번호 정렬
int compareNums(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// 상위 N개 통계 번호 읽기
int loadFrequentNumbers(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("파일 열기 실패");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    LottoStat stats[100];
    int index = 0;

    fgets(line, sizeof(line), file); // 헤더 스킵

    while (fgets(line, sizeof(line), file)) {
        int num, cnt;
        if (sscanf(line, "%d,%d", &num, &cnt) == 2) {
            stats[index].number = num;
            stats[index].count = cnt;
            index++;
        }
    }
    fclose(file);

    qsort(stats, index, sizeof(LottoStat), compareStats);

    for (int i = 0; i < MAX_FREQUENT && i < index; i++) {
        frequentNumbers[i] = stats[i].number;
    }

    return 1;
}

// 한 줄 생성
void generateLottoLine(int* result) {
    int count = 0;

    // 1. 자주 나온 번호 2~3개
    int pickFromFrequent = 2 + rand() % 2;
    while (count < pickFromFrequent) {
        int idx = rand() % MAX_FREQUENT;
        int num = frequentNumbers[idx];
        if (!isInArray(result, count, num)) {
            result[count++] = num;
        }
    }

    // 2. 연속된 번호 1쌍
    int base = 1 + rand() % 44;
    if (!isInArray(result, count, base) && !isInArray(result, count, base + 1)) {
        result[count++] = base;
        result[count++] = base + 1;
    }

    // 3. 나머지 무작위
    while (count < PICK_COUNT) {
        int num = 1 + rand() % TOTAL_NUMBERS;
        if (!isInArray(result, count, num)) {
            result[count++] = num;
        }
    }

    qsort(result, PICK_COUNT, sizeof(int), compareNums);
}

// 강조 출력
void printLottoLine(int* line) {
    for (int i = 0; i < PICK_COUNT; i++) {
        int val = line[i];
        int isFreq = isInArray(frequentNumbers, MAX_FREQUENT, val);
        int isConsecutive = (i > 0 && line[i] == line[i - 1] + 1);

        if (isFreq && isConsecutive)
            printf("[%d*+]", val);
        else if (isFreq)
            printf("[%d*]", val);
        else if (isConsecutive)
            printf("[%d+]", val);
        else
            printf("%d", val);
        printf(" ");
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    if (!loadFrequentNumbers("lotto_stats.csv")) {
        printf("로또 통계 파일을 불러오는 데 실패했습니다.\n");
        return 1;
    }

    printf("🎯 통계 기반 전략 로또 번호 10세트 🎯\n\n");

    for (int i = 0; i < LINE_COUNT; i++) {
        int line[PICK_COUNT] = { 0 };
        generateLottoLine(line);
        printf("%2d번 세트: ", i + 1);
        printLottoLine(line);
    }

    return 0;
}
