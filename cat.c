#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> // ������ ����

#define ROOM_WIDTH 15
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

void printGameState(const char* name, int soup_count, int affinity, int cp, int mood);
void drawRoom(int cat_x, int prevPos, int hasScratcher, int hasTower);
void openShop(int* cp, int* hasToyMouse, int* hasLaser, int* hasScratcher, int* hasTower);
void triggerMiniGame(int* mood);

int main() {
    char name[20];
    int soup_count = 0;
    int affinity = 2;
    int cp = 0;
    int mood = 3;
    int cat_x = HME_POS;
    int prevPos = -1;
    int hasScratcher = 0;
    int hasTower = 0;
    int hasToyMouse = 0;
    int hasLaser = 0;
    int turnCount = 0;

    srand((unsigned int)time(NULL));

    printf("****�߿��̿� ����****\n\n");
    printf("  /\\_/\\     \n");
    printf(" ( o.o )    \n");
    printf("  > ^ <     \n\n");

    printf("\n�߿����� �̸��� ���� �ּ���: ");
    scanf_s("%19s", name, (unsigned)_countof(name));
    printf("�߿����� �̸��� %s�Դϴ�.\n", name);

    Sleep(2500);
    system("cls");

    while (1) {
        turnCount++;

        if (turnCount % 3 == 0) {
            triggerMiniGame(&mood);
        }

        printGameState(name, soup_count, affinity, cp, mood);

        int moodRoll = rand() % 6 + 1;
        int threshold = 6 - affinity;
        printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
        printf("%d��(��) ���Խ��ϴ�.\n", moodRoll);
        if (moodRoll <= threshold && mood > 0) {
            mood--;
            printf("�ƹ� ���� ���� ����� �������ϴ�. ����̴ϱ��.\n");
            printf("%s�� ����� �������ϴ�: %d -> %d\n", name, mood + 1, mood);
        }

        drawRoom(cat_x, prevPos, hasScratcher, hasTower);

        int userChoice = -1;
        int menuNum = 0;
        int optionMouse = -1;
        int optionLaser = -1;

        printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?\n");
        printf("  %d. �ƹ��͵� ���� ����\n", menuNum++);
        printf("  %d. �ܾ� �ֱ�\n", menuNum++);
        if (hasToyMouse) {
            optionMouse = menuNum;
            printf("  %d. �峭�� ��� ��� �ֱ�\n", menuNum++);
        }
        if (hasLaser) {
            optionLaser = menuNum;
            printf("  %d. ������ �����ͷ� ��� �ֱ�\n", menuNum++);
        }

        while (1) {
            printf(">> ");
            if (scanf_s("%d", &userChoice) != 1 || userChoice < 0 || userChoice >= menuNum) {
                printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
                while (getchar() != '\n');
            }
            else break;
        }

        if (userChoice == 0) {
            if (mood > 0) {
                mood--;
                printf("%s�� ����� ���������ϴ�: %d -> %d\n", name, mood + 1, mood);
            }
            int roll = rand() % 6 + 1;
            if (roll <= 5 && affinity > 0) {
                affinity--;
                printf("������� ���谡 �������ϴ�.\n");
            }
        }
        else if (userChoice == 1) {
            printf("%s�� ����� �״���Դϴ�: %d\n", name, mood);
            int roll = rand() % 6 + 1;
            if (roll >= 5 && affinity < 4) {
                affinity++;
                printf("ģ�е��� �����߽��ϴ�.\n");
            }
        }
        else if (userChoice == optionMouse) {
            if (mood < 3) {
                printf("�峭�� ��� %s�� ��� �־����ϴ�. %s�� ����� ���� ���������ϴ�: %d -> %d\n", name, name, mood, mood + 1);
                mood++;
            }
            int roll = rand() % 6 + 1;
            if (roll >= 4 && affinity < 4) {
                affinity++;
                printf("ģ�е��� �����߽��ϴ�.\n");
            }
        }
        else if (userChoice == optionLaser) {
            int old = mood;
            mood += 2;
            if (mood > 3) mood = 3;
            printf("������ �����ͷ� %s�� �ų��� ��� �־����ϴ�. %s�� ����� �� ���������ϴ�: %d -> %d\n", name, name, old, mood);
            int roll = rand() % 6 + 1;
            if (roll >= 2 && affinity < 4) {
                affinity++;
                printf("ģ�е��� �����߽��ϴ�.\n");
            }
        }

        prevPos = cat_x;

        if (mood == 0 && cat_x > HME_POS) cat_x--;
        else if (mood == 1 && (hasScratcher || hasTower)) {
            int target = hasScratcher ? 5 : 3;
            if (cat_x < target) cat_x++;
            else if (cat_x > target) cat_x--;
        }
        else if (mood == 3 && cat_x < BWL_POS) cat_x++;

        if (cat_x == HME_POS && prevPos == HME_POS && mood < 3) mood++;
        if (hasScratcher && cat_x == 5 && mood < 3) mood++;
        if (hasTower && cat_x == 3 && mood < 3) {
            mood += 2;
            if (mood > 3) mood = 3;
        }

        if (cat_x == BWL_POS) {
            int randomSoup = rand() % 3;
            char soupName[20];
            if (randomSoup == 0) snprintf(soupName, sizeof(soupName), "���� ����");
            else if (randomSoup == 1) snprintf(soupName, sizeof(soupName), "����� ����");
            else snprintf(soupName, sizeof(soupName), "����ݸ� ����");

            soup_count++;
            cp++;
            printf("�߿��̰� %s�� ��������ϴ�!\n", soupName);
        }

        openShop(&cp, &hasToyMouse, &hasLaser, &hasScratcher, &hasTower);

        Sleep(2500);
        system("cls");
    }

    return 0;
}

void drawRoom(int cat_x, int prevPos, int hasScratcher, int hasTower) {
    printf("\n");
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n#");
    for (int i = 1; i < ROOM_WIDTH - 1; i++) {
        if (i == HME_POS) printf("H");
        else if (hasTower && i == 3) printf("T");
        else if (hasScratcher && i == 5) printf("S");
        else if (i == BWL_POS) printf("B");
        else printf(" ");
    }
    printf("#\n#");
    for (int i = 1; i < ROOM_WIDTH - 1; i++) {
        if (i == cat_x) printf("C");
        else if (i == prevPos && prevPos != cat_x) printf(".");
        else printf(" ");
    }
    printf("#\n");
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n\n");
}

void openShop(int* cp, int* hasToyMouse, int* hasLaser, int* hasScratcher, int* hasTower) {
    // TODO: ���� ��� ���� ����
}

void triggerMiniGame(int* mood) {
    const char* answers[] = { "��ũ��ó", "ĹŸ��", "����", "�峭��", "������" };
    const char* clues[] = { "��������", "������", "����", "������", "������" };
    int total = 5;
    int index = rand() % total;

    printf("���� ����Ʈ �߻�! �˶����� �ʼ� ����!\n");
    printf("�˶��̰� ���ϴ� ������ �ʼ��� [%s]�Դϴ�.\n", clues[index]);
    printf("������ �Է��ϼ���: ");

    char input[50];
    scanf_s("%49s", input, (unsigned)_countof(input));

    if (strcmp(input, answers[index]) == 0) {
        if (*mood < 3) (*mood)++;
        printf("�����Դϴ�! ����� ���������ϴ�.\n");
    }
    else {
        if (*mood > 0) (*mood)--;
        printf("�����Դϴ�! ����� ���������ϴ�.\n");
    }
}

void printGameState(const char* name, int soup_count, int affinity, int cp, int mood) {
    const char* moodText[] = { "����� �ſ� ���޴ϴ�.", "�ɽ����մϴ�.", "�Ļ��� �����ϴ�.", "������ �θ��ϴ�." };
    const char* affinityText[] = {
        "�翡 ���� ������ �Ⱦ��մϴ�.",
        "���� ���Ǳ� ����Դϴ�.",
        "�׷����� ������ �����Դϴ�.",
        "�Ǹ��� ����� ���� �ް� �ֽ��ϴ�.",
        "���� �������Դϴ�."
    };

    printf("=============== ���� ���� ===============\n");
    printf("������� ���� ����: %d��\n", soup_count);
    printf("CP: %d ����Ʈ\n", cp);
    printf("%s�� ���(0~3): %d\n", name, mood);
    printf("%s\n", moodText[mood]);
    printf("������� ����(0~4): %d\n", affinity);
    printf("  %s\n", affinityText[affinity]);
    printf("=========================================\n");
}
