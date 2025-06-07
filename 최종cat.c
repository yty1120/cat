#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 

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
        drawRoom(cat_x, prevPos, hasScratcher, hasTower);

        // ==================== [2-5 상호작용 입력 기능 추가] ====================
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
            } else break;
        }
      // ==================== [2-6 행동 처리 기능 추가] ====================
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
// ===================================================================

    }

    return 0;
}




