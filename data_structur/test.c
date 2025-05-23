#define _CRT_SECURE_NO_WARNINGS // Visual Studio���� ���� ��� ��Ȱ��ȭ�մϴ�.

#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h> // strcpy, strcmp

#define NAME_LEN 100 // �� �̸��� �ִ� ����

// �� ��� ���� (���� ���� ����Ʈ + �Ÿ� �� �ð� ����ġ + ȯ�� ����)
typedef struct Station {
    char name[NAME_LEN];
    struct Station* next;         // ���� ���� ����Ű�� ������
    struct Station* prev;         // ���� ���� ����Ű�� ������
    int nextDistance;             // ���� ������ ���� �������� �Ÿ� ����ġ (km)
    int nextTimeWeight;           // ���� ������ ���� �������� �ð� ����ġ (��)
    struct Station* transfers[5]; // �ִ� 5���� ȯ�� �뼱 (����)
    int transferCount;            // ȯ�� �뼱 ��
} Station;

// �뼱 ����
typedef struct Line {
    int lineNumber;
    Station* head;                // �뼱�� ù ��
    Station* tail;                // �뼱�� ������ �� (������ Ž�� �� �߰��� ����)
} Line;

// �뼱 ���� �Լ�
Line* createLine(int lineNumber) {
    Line* line = (Line*)malloc(sizeof(Line));
    if (line == NULL) {
        perror("�޸� �Ҵ� ����");
        exit(EXIT_FAILURE);
    }
    line->lineNumber = lineNumber;
    line->head = NULL;
    line->tail = NULL; // tail�� �ʱ�ȭ
    return line;
}

// �� �߰� �Լ� (�Ÿ� �� �ð� ����ġ ����)
// stationName: �߰��� �� �̸�
// distToNext: ���� �߰��ϴ� ������ "����" �������� �Ÿ� (���� ���� nextDistance�� ����)
// timeToNext: ���� �߰��ϴ� ������ "����" �������� �ð� (���� ���� nextTimeWeight�� ����)
void addStation(Line* line, const char* stationName, int distToPrev, int timeToPrev) {
    Station* newStation = (Station*)malloc(sizeof(Station));
    if (newStation == NULL) {
        perror("�޸� �Ҵ� ����");
        exit(EXIT_FAILURE);
    }
    strcpy(newStation->name, stationName);
    newStation->next = NULL;
    newStation->prev = NULL;
    newStation->nextDistance = 0; // �ʱ�ȭ, ���� �� ���� �� ����
    newStation->nextTimeWeight = 0; // �ʱ�ȭ, ���� �� ���� �� ����
    newStation->transferCount = 0;   // ȯ�� ���� �ʱ�ȭ

    if (line->head == NULL) { // �뼱�� ù �� �߰�
        line->head = newStation;
        line->tail = newStation;
    }
    else { // �뼱�� �� �߰�
        line->tail->next = newStation;     // ���� ������ ���� ���� ������ �� �� ����
        line->tail->nextDistance = distToPrev; // ���� ������ ������ �� �������� �Ÿ� ����
        line->tail->nextTimeWeight = timeToPrev; // ���� ������ ������ �� �������� �ð� ����ġ ����
        newStation->prev = line->tail;     // �� ���� ���� ������ ���� ������ �� ����
        line->tail = newStation;           // �뼱�� ������ ���� �� ������ ����
    }
}

// ȯ�¿� ���� �Լ�
// station1�� station2�� ������ �̸��� ���� �ٸ� �뼱�� �� ����Դϴ�.
void connectTransfer(Station* station1, Station* station2) {
    if (station1->transferCount < 5 && station2->transferCount < 5) {
        station1->transfers[station1->transferCount++] = station2;
        station2->transfers[station2->transferCount++] = station1;
    }
    else {
        printf("����: ȯ�¿� ���� ���� (�ִ� ȯ�� �뼱 �� �ʰ�: %s, %s)\n", station1->name, station2->name);
    }
}

// �뼱 ���� (�� �̸�, �Ÿ� �迭, �ð� �迭�κ��� ��� ����)
// distances: �� ���� "����" �� ������ �Ÿ� (N-1��)
// timeWeights: �� ���� "����" �� ������ �ð� (N-1��)
void setupLine(Line* line, const char* stationNames[], const int distances[], const int timeWeights[], int count) {
    // ù ���� ����ġ�� �����Ƿ� (���� ���� �����Ƿ�) 0���� �߰�
    addStation(line, stationNames[0], 0, 0);

    // �� ��° �����ʹ� ���� ������ ����ġ�� ����Ͽ� �߰�
    for (int i = 1; i < count; i++) {
        // addStation�� distToPrev, timeToPrev�� ��ǻ� ���� ���� nextDistance, nextTimeWeight�� �˴ϴ�.
        addStation(line, stationNames[i], distances[i - 1], timeWeights[i - 1]);
    }
}

// �뼱 ��� (������)
void printLine(Line* line) {
    printf("%dȣ�� (������): ", line->lineNumber);
    Station* current = line->head;
    while (current != NULL) {
        printf("%s", current->name);
        if (current->transferCount > 0) {
            printf(" (ȯ��: ");
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

// �뼱 ��� (������)
void printLineReverse(Line* line) {
    printf("%dȣ�� (������): ", line->lineNumber);
    Station* current = line->tail; // tail���� ����
    while (current != NULL) {
        printf("%s", current->name);
        if (current->transferCount > 0) {
            printf(" (ȯ��: ");
            for (int i = 0; i < current->transferCount; i++) {
                printf("%s", current->transfers[i]->name);
                if (i < current->transferCount - 1) {
                    printf(", ");
                }
            }
            printf(")");
        }
        if (current->prev != NULL) {
            // ������ ��� ��, ���� ���� 'prev'�� ����Ű�� ���� 'nextDistance'�� 'nextTimeWeight'�� ���
            // �̴� 'prev' ������ '����' �������� ����ġ�� �ǹ��մϴ�.
            printf(" -[D:%dkm, T:%dmin]-> ", current->prev->nextDistance, current->prev->nextTimeWeight);
        }
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

int main() {
    // 1ȣ�� ������
    const char* line1Stations[] = {
        "�ҿ��", "����õ", "����", "����õ�߾�", "����", "����", "����", "����", "���", "����",
        "������", "ȸ��", "������", "����", "������", "����", "â��", "��õ", "����", "�����",
        "����", "���̹�", "�ܴ��", "ȸ��", "û����", "���⵿", "�ż���", "������", "���빮", "����5��",
        "����3��", "����", "��û", "���￪", "����", "���", "�뷮��", "���", "�ű�", "������",
        "�ŵ���", "����", "����", "����", "������", "�¼�", "����", "�һ�", "��õ", "�ߵ�",
        "�۳�", "�ΰ�", "����", "���", "����", "����", "�־�", "��ȭ", "������", "����",
        "����õ", "��õ"
    };
    int line1Count = sizeof(line1Stations) / sizeof(line1Stations[0]);
    // ���� �Ÿ��� �ƴ� ���� ���Դϴ�.
    const int line1Distances[] = { 3, 2, 2, 1, 2, 2, 3, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
    // ���� �ð��� �ƴ� ���� ���Դϴ�. (�Ÿ��� ���� ����)
    const int line1TimeWeights[] = { 3, 2, 2, 1, 2, 2, 3, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2,
                                    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };


    // 2ȣ�� ������
    const char* line2Stations[] = {
        "��û", "�������Ա�", "������3��", "������4��", "���빮���繮ȭ����", "�Ŵ�", "��սʸ�", "�սʸ�", "�Ѿ��", "�Ҽ�",
        "����", "�Ǵ��Ա�", "����", "����", "��ǳ���", "���", "��ǻ���", "���տ��", "�Ｚ", "����",
        "����", "����", "����", "����", "���", "���", "������", "������Ա�", "��õ", "�Ÿ�",
        "�Ŵ��", "���ε����д���", "�븲", "�ŵ���", "����", "��������û", "���", "����", "ȫ���Ա�", "����",
        "�̴�", "����", "������"
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

    // 3ȣ�� ������
    const char* line3Stations[] = {
        "��ȭ", "�ֿ�", "���߻�", "����", "�鼮", "���", "ȭ��", "����", "����", "���",
        "����", "���Ĺ�", "���ų�", "�ұ�", "���", "ȫ��", "������", "������", "�溹��", "�ȱ�",
        "����3��", "������3��", "�湫��", "�����Ա�", "���", "��ȣ", "����", "�б���", "�Ż�", "���",
        "����͹̳�", "����", "�����͹̳�", "����", "�ź�", "����", "��ġ", "�п���", "��û", "�Ͽ�",
        "����", "��������", "��������", "����"
    };
    int line3Count = sizeof(line3Stations) / sizeof(line3Stations[0]);
    const int line3Distances[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2 };
    const int line3TimeWeights[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                    2, 2, 2 };

    // 4ȣ�� ������
    const char* line4Stations[] = {
        "����", "����", "����������", "���", "���", "���", "â��", "�ֹ�", "����", "�̾�",
        "�̾ƻ�Ÿ�", "����", "���ſ����Ա�", "�Ѽ����Ա�", "��ȭ", "���빮", "���빮���繮ȭ����", "�湫��", "��", "ȸ��",
        "���￪", "�����Ա�", "�ﰢ��", "�ſ��", "����", "����", "�ѽŴ��Ա�", "���", "���·�"
    };
    int line4Count = sizeof(line4Stations) / sizeof(line4Stations[0]);
    const int line4Distances[] = { 3, 3, 4, 2, 3, 3, 4, 2, 3, 3,
                                   4, 2, 3, 3, 4, 2, 3, 3, 4, 2,
                                   3, 3, 4, 2, 3, 3, 4, 2 }; // ���·� ���Ĵ� �����Ͱ� �����Ƿ� ����
    const int line4TimeWeights[] = { 3, 3, 4, 2, 3, 3, 4, 2, 3, 3,
                                    4, 2, 3, 3, 4, 2, 3, 3, 4, 2,
                                    3, 3, 4, 2, 3, 3, 4, 2 }; // ���·� ���Ĵ� �����Ͱ� �����Ƿ� ����


    Line* line1 = createLine(1);
    Line* line2 = createLine(2);
    Line* line3 = createLine(3);
    Line* line4 = createLine(4);

    setupLine(line1, line1Stations, line1Distances, line1TimeWeights, line1Count);
    setupLine(line2, line2Stations, line2Distances, line2TimeWeights, line2Count);
    setupLine(line3, line3Stations, line3Distances, line3TimeWeights, line3Count);
    setupLine(line4, line4Stations, line4Distances, line4TimeWeights, line4Count);

    // ȯ�¿��� ã�� ���� ������ ����
    Station* ���빮1 = NULL;
    Station* ���빮4 = NULL;
    Station* ����3��1 = NULL;
    Station* ����3��3 = NULL;
    Station* ���￪1 = NULL;
    Station* ���￪4 = NULL;
    Station* �ŵ���1 = NULL;
    Station* �ŵ���2 = NULL;
    Station* ����2 = NULL;
    Station* ����3 = NULL;
    Station* �湫��3 = NULL;
    Station* �湫��4 = NULL;
    Station* ���빮���繮ȭ����2 = NULL;
    Station* ���빮���繮ȭ����4 = NULL;
    Station* ������3��2 = NULL;
    Station* ������3��3 = NULL;

    // �� �뼱���� ȯ�¿� ã��
    Station* current;

    current = line1->head;
    while (current != NULL) {
        if (strcmp(current->name, "���빮") == 0) ���빮1 = current;
        else if (strcmp(current->name, "����3��") == 0) ����3��1 = current;
        else if (strcmp(current->name, "���￪") == 0) ���￪1 = current;
        else if (strcmp(current->name, "�ŵ���") == 0) �ŵ���1 = current;
        current = current->next;
    }

    current = line2->head;
    while (current != NULL) {
        if (strcmp(current->name, "��û") == 0) { /* ��û 1ȣ���� 2ȣ�� ȯ���� �̹� ����� �뼱 ���� ���̹Ƿ� �߰����� ���� �ʿ� ���� */ }
        else if (strcmp(current->name, "������3��") == 0) ������3��2 = current;
        else if (strcmp(current->name, "���빮���繮ȭ����") == 0) ���빮���繮ȭ����2 = current;
        else if (strcmp(current->name, "�ŵ���") == 0) �ŵ���2 = current;
        else if (strcmp(current->name, "����") == 0) ����2 = current;
        current = current->next;
    }

    current = line3->head;
    while (current != NULL) {
        if (strcmp(current->name, "����3��") == 0) ����3��3 = current;
        else if (strcmp(current->name, "������3��") == 0) ������3��3 = current;
        else if (strcmp(current->name, "�湫��") == 0) �湫��3 = current;
        else if (strcmp(current->name, "����") == 0) ����3 = current;
        current = current->next;
    }

    current = line4->head;
    while (current != NULL) {
        if (strcmp(current->name, "���빮") == 0) ���빮4 = current;
        else if (strcmp(current->name, "���빮���繮ȭ����") == 0) ���빮���繮ȭ����4 = current;
        else if (strcmp(current->name, "�湫��") == 0) �湫��4 = current;
        else if (strcmp(current->name, "���￪") == 0) ���￪4 = current;
        current = current->next;
    }

    // ȯ�¿� ����
    if (���빮1 && ���빮4) connectTransfer(���빮1, ���빮4);
    if (����3��1 && ����3��3) connectTransfer(����3��1, ����3��3);
    if (���￪1 && ���￪4) connectTransfer(���￪1, ���￪4);
    if (�ŵ���1 && �ŵ���2) connectTransfer(�ŵ���1, �ŵ���2);
    if (����2 && ����3) connectTransfer(����2, ����3);
    if (�湫��3 && �湫��4) connectTransfer(�湫��3, �湫��4);
    if (���빮���繮ȭ����2 && ���빮���繮ȭ����4) connectTransfer(���빮���繮ȭ����2, ���빮���繮ȭ����4);
    if (������3��2 && ������3��3) connectTransfer(������3��2, ������3��3);


    printf("--- ����ö �뼱 ���� ---\n\n");

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

    // �޸� ����
    freeLine(line1);
    freeLine(line2);
    freeLine(line3);
    freeLine(line4);

    return 0;
}