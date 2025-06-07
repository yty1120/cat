#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> // 윈도우 전용

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

    printf("****야옹이와 수프****\n\n");
    printf("  /\\_/\\     \n");
    printf(" ( o.o )    \n");
    printf("  > ^ <     \n\n");

    printf("\n야옹이의 이름을 지어 주세요: ");
    scanf_s("%19s", name, (unsigned)_countof(name));
    printf("야옹이의 이름은 %s입니다.\n", name);

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
        printf("주사위를 굴립니다. 또르르...\n");
        printf("%d이(가) 나왔습니다.\n", moodRoll);
        if (moodRoll <= threshold && mood > 0) {
            mood--;
            printf("아무 이유 없이 기분이 나빠집니다. 고양이니까요.\n");
            printf("%s의 기분이 나빠집니다: %d -> %d\n", name, mood + 1, mood);
        }

        drawRoom(cat_x, prevPos, hasScratcher, hasTower);

        int userChoice = -1;
        int menuNum = 0;
        int optionMouse = -1;
        int optionLaser = -1;

        printf("어떤 상호작용을 하시겠습니까?\n");
        printf("  %d. 아무것도 하지 않음\n", menuNum++);
        printf("  %d. 긁어 주기\n", menuNum++);
        if (hasToyMouse) {
            optionMouse = menuNum;
            printf("  %d. 장난감 쥐로 놀아 주기\n", menuNum++);
        }
        if (hasLaser) {
            optionLaser = menuNum;
            printf("  %d. 레이저 포인터로 놀아 주기\n", menuNum++);
        }

        while (1) {
            printf(">> ");
            if (scanf_s("%d", &userChoice) != 1 || userChoice < 0 || userChoice >= menuNum) {
                printf("잘못된 입력입니다. 다시 입력해주세요.\n");
                while (getchar() != '\n');
            }
            else break;
        }

        if (userChoice == 0) {
            if (mood > 0) {
                mood--;
                printf("%s의 기분이 나빠졌습니다: %d -> %d\n", name, mood + 1, mood);
            }
            int roll = rand() % 6 + 1;
            if (roll <= 5 && affinity > 0) {
                affinity--;
                printf("집사와의 관계가 나빠집니다.\n");
            }
        }
        else if (userChoice == 1) {
            printf("%s의 기분은 그대로입니다: %d\n", name, mood);
            int roll = rand() % 6 + 1;
            if (roll >= 5 && affinity < 4) {
                affinity++;
                printf("친밀도가 증가했습니다.\n");
            }
        }
        else if (userChoice == optionMouse) {
            if (mood < 3) {
                printf("장난감 쥐로 %s와 놀아 주었습니다. %s의 기분이 조금 좋아졌습니다: %d -> %d\n", name, name, mood, mood + 1);
                mood++;
            }
            int roll = rand() % 6 + 1;
            if (roll >= 4 && affinity < 4) {
                affinity++;
                printf("친밀도가 증가했습니다.\n");
            }
        }
        else if (userChoice == optionLaser) {
            int old = mood;
            mood += 2;
            if (mood > 3) mood = 3;
            printf("레이저 포인터로 %s와 신나게 놀아 주었습니다. %s의 기분이 꽤 좋아졌습니다: %d -> %d\n", name, name, old, mood);
            int roll = rand() % 6 + 1;
            if (roll >= 2 && affinity < 4) {
                affinity++;
                printf("친밀도가 증가했습니다.\n");
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
            if (randomSoup == 0) snprintf(soupName, sizeof(soupName), "감자 수프");
            else if (randomSoup == 1) snprintf(soupName, sizeof(soupName), "양송이 수프");
            else snprintf(soupName, sizeof(soupName), "브로콜리 수프");

            soup_count++;
            cp++;
            printf("야옹이가 %s를 만들었습니다!\n", soupName);
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
    // TODO: 상점 기능 구현 예정
}

void triggerMiniGame(int* mood) {
    const char* answers[] = { "스크래처", "캣타워", "간식", "장난감", "레이저" };
    const char* clues[] = { "ㅅㅋㄹㅊ", "ㅋㅌㅇ", "ㄱㅅ", "ㅈㄴㄱ", "ㄹㅇㅈ" };
    int total = 5;
    int index = rand() % total;

    printf("돌발 퀘스트 발생! 쫀떡이의 초성 퀴즈!\n");
    printf("쫀떡이가 원하는 물건의 초성은 [%s]입니다.\n", clues[index]);
    printf("정답을 입력하세요: ");

    char input[50];
    scanf_s("%49s", input, (unsigned)_countof(input));

    if (strcmp(input, answers[index]) == 0) {
        if (*mood < 3) (*mood)++;
        printf("정답입니다! 기분이 좋아졌습니다.\n");
    }
    else {
        if (*mood > 0) (*mood)--;
        printf("오답입니다! 기분이 나빠졌습니다.\n");
    }
}

void printGameState(const char* name, int soup_count, int affinity, int cp, int mood) {
    const char* moodText[] = { "기분이 매우 나쁩니다.", "심심해합니다.", "식빵을 굽습니다.", "골골송을 부릅니다." };
    const char* affinityText[] = {
        "곁에 오는 것조차 싫어합니다.",
        "간식 자판기 취급입니다.",
        "그럭저럭 쓸만한 집사입니다.",
        "훌륭한 집사로 인정 받고 있습니다.",
        "집사 껌딱지입니다."
    };

    printf("=============== 현재 상태 ===============\n");
    printf("현재까지 만든 수프: %d개\n", soup_count);
    printf("CP: %d 포인트\n", cp);
    printf("%s의 기분(0~3): %d\n", name, mood);
    printf("%s\n", moodText[mood]);
    printf("집사와의 관계(0~4): %d\n", affinity);
    printf("  %s\n", affinityText[affinity]);
    printf("=========================================\n");
}
