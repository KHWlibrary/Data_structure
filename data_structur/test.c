#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 100

// �� ��� ���� (����� ���� ����Ʈ + �Ÿ� + �ð� ����ġ)
typedef struct Station {
    char name[NAME_LEN];
    struct Station* next;
    struct Station* prev;
    int nextDistance; // ���� �������� �Ÿ�
    int prevDistance; // ���� �������� �Ÿ�
    int timeWeight;   // ���� �������� �ð� ����ġ (��: ��)
} Station;

// �뼱 ����
typedef struct Line {
    int lineNumber;
    Station* head;
} Line;

// �뼱 ����
Line* createLine(int lineNumber) {
    Line* line = (Line*)malloc(sizeof(Line));
    line->lineNumber = lineNumber;
    line->head = NULL;
    return line;
}

// �� �߰� (�Ÿ� �� �ð� ����ġ ����)
void addStation(Line* line, const char* stationName, int distanceFromPrev, int timeWeight) {
    Station* newStation = (Station*)malloc(sizeof(Station));
    strcpy(newStation->name, stationName);
    newStation->next = NULL;
    newStation->prev = NULL;
    newStation->nextDistance = 0; // �ʱ�ȭ, ���� �� ���� �� ����
    newStation->prevDistance = distanceFromPrev;
    newStation->timeWeight = timeWeight; // �ð� ����ġ ����

    if (line->head == NULL) {
        line->head = newStation;
    }
    else {
        Station* current = line->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStation;
        current->nextDistance = distanceFromPrev; // ���� ������ ���� �������� �Ÿ� ����
        current->timeWeight = timeWeight;         // ���� ������ ���� �������� �ð� ����ġ ����
        newStation->prev = current;
    }
}

// �뼱 ��� (������)
void printLine(Line* line) {
    printf("%dȣ�� (������): ", line->lineNumber);
    Station* current = line->head;
    while (current != NULL) {
        printf("%s", current->name);
        if (current->next != NULL)
            printf(" -[D:%dkm, T:%dmin]-> ", current->nextDistance, current->timeWeight); // �Ÿ��� �ð� ����ġ ���
        current = current->next;
    }
    printf("\n");
}

// �뼱 ��� (������)
void printLineReverse(Line* line) {
    printf("%dȣ�� (������): ", line->lineNumber);
    Station* current = line->head;
    if (current == NULL) {
        printf("����\n");
        return;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    while (current != NULL) {
        printf("%s", current->name);
        // ������ ��� ��, ���� �������� �Ÿ��� �ð� ����ġ�� ���
        // prevDistance�� ���� �������� �Ÿ�, prevStation->timeWeight�� ���� ������ ���� �������� �ð�
        if (current->prev != NULL)
            printf(" -[D:%dkm, T:%dmin]-> ", current->prevDistance, current->prev->timeWeight);
        current = current->prev;
    }
    printf("\n");
}


// �޸� ����
void freeLine(Line* line) {
    Station* current = line->head;
    while (current != NULL) {
        Station* temp = current;
        current = current->next;
        free(temp);
    }
    free(line);
}

// �뼱 ���� (�� �̸��� �Ÿ�/�ð� �迭�κ��� ����)
void setupLine(Line* line, const char* stations[], const int distances[], int count) {
    for (int i = 0; i < count; i++) {
        // ù ��° ���� ���� ���� �����Ƿ� distance�� timeWeight�� 0���� ����
        int distance = (i == 0) ? 0 : distances[i - 1];
        int timeWeight = (i == 0) ? 0 : distances[i - 1]; // ���⼭�� �Ÿ� �迭�� �ð� ����ġ�� ��Ȱ��
        // ���� ��Ȳ������ ������ �ð� �迭�� ����ϴ� ���� �����ϴ�.
        addStation(line, stations[i], distance, timeWeight);
    }
}

int main() {
    const char* line1Stations[] = {
        "�ҿ��", "����õ", "����", "����õ�߾�", "����",
        "����", "����", "����", "���", "����",
        "������", "ȸ��", "������", "����", "������",
        "����", "â��", "��õ", "����", "�����",
        "����", "���̹�", "�ܴ��", "ȸ��", "û����",
        "���⵿", "�ż���", "������", "���빮", "����5��",
        "����3��", "����", "��û", "���￪", "����",
        "���", "�뷮��", "���", "�ű�", "������",
        "�ŵ���", "����", "����", "����", "������",
        "�¼�", "����", "�һ�", "��õ", "�ߵ�",
        "�۳�", "�ΰ�", "����", "���", "����",
        "����", "�־�", "��ȭ", "������", "����",
        "����õ", "��õ"
    };
    int line1Count = sizeof(line1Stations) / sizeof(line1Stations[0]);
    const int line1Distances[] = { 3, 2, 2, 1, 2, 2, 3, 2, 2, 2,
        2, 3, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2 }; // ���� �Ÿ� (���� �ð� ����ġ�ε� ���)

    const char* line2Stations[] = {
        "��û", "�������Ա�", "������3��", "������4��", "���빮���繮ȭ����",
        "�Ŵ�", "��սʸ�", "�սʸ�", "�Ѿ��", "�Ҽ�",
        "����", "�Ǵ��Ա�", "����", "����", "��ǳ���",
        "���", "��ǻ���", "���տ��", "�Ｚ", "����",
        "����", "����", "����", "����", "���",
        "���", "������", "������Ա�", "��õ", "�Ÿ�",
        "�Ŵ��", "���ε����д���", "�븲", "�ŵ���", "����",
        "��������û", "���", "����", "ȫ���Ա�", "����",
        "�̴�", "����", "������"
    };
    int line2Count = sizeof(line2Stations) / sizeof(line2Stations[0]);
    const int line2Distances[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1 }; // ���� �Ÿ� (���� �ð� ����ġ�ε� ���)

    const char* line3Stations[] = {
        "��ȭ", "�ֿ�", "���߻�", "����", "�鼮",
        "���", "ȭ��", "����", "����", "���",
        "����", "���Ĺ�", "���ų�", "�ұ�", "���",
        "ȫ��", "������", "������", "�溹��", "�ȱ�",
        "����3��", "������3��", "�湫��", "�����Ա�", "���",
        "��ȣ", "����", "�б���", "�Ż�", "���",
        "����͹̳�", "����", "�����͹̳�", "����", "�ź�",
        "����", "��ġ", "�п���", "��û", "�Ͽ�",
        "����", "��������", "��������", "����"
    };
    int line3Count = sizeof(line3Stations) / sizeof(line3Stations[0]);
    const int line3Distances[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2 }; // ���� �Ÿ� (���� �ð� ����ġ�ε� ���)

    const char* line4Stations[] = {
        "����", "����", "����������", "���", "���",
        "���", "â��", "�ֹ�", "����", "�̾�",
        "�̾ƻ�Ÿ�", "����", "���ſ����Ա�", "�Ѽ����Ա�", "��ȭ",
        "���빮", "���빮���繮ȭ��ȭ����", "�湫��", "��", "ȸ��",
        "���￪", "�����Ա�", "�ﰢ��", "�ſ��", "����",
        "����", "�ѽŴ��Ա�", "���", "����"
    };
    int line4Count = sizeof(line4Stations) / sizeof(line4Stations[0]);
    const int line4Distances[] = { 3, 3, 4, 2, 3, 3, 4, 2, 3,
        3, 4, 2, 3, 3, 4, 2, 3, 3, 4,
        2, 3, 3, 4, 2, 3, 3, 4, 2, 3, 3, 4, 2 }; // ���� �Ÿ� (���� �ð� ����ġ�ε� ���)


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
    printf("\n"); // �ٹٲ� �߰�
    printLine(line2);
    printLineReverse(line2);
    printf("\n"); // �ٹٲ� �߰�
    printLine(line3);
    printLineReverse(line3);
    printf("\n"); // �ٹٲ� �߰�
    printLine(line4);
    printLineReverse(line4);
    printf("\n"); // �ٹٲ� �߰�

    freeLine(line1);
    freeLine(line2);
    freeLine(line3);
    freeLine(line4);

    return 0;
}