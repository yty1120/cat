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
void performAction(int cat_x, int* mood, int* soup_count, int* cp, const char* name, int hasScratcher, int hasTower); // 행동 처리

int main() {
    char name[20];
    int soup_count = 0;
    int affinity = 2;
    int cp = 0;
    int mood = 3;
    int cat_x = HME_POS;
    int prevPos = -1;
    int hasScratcher = 1;  // 테스트용
    int hasTower = 1;      // 테스트용

    srand((unsigned int)time(NULL));

    printf("****야옹이와 수프****\n\n");
    printf("  /\\_/\\     \n");
    printf(" ( o.o )    \n");
    printf("  > ^ <     \n\n");

    printf("야옹이의 이름을 지어 주세요: ");
    scanf_s("%19s", name, (unsigned)_countof(name));
    printf("야옹이의 이름은 %s입니다.\n", name);

    Sleep(2000);
    system("cls");

    while (1) {
        printGameState(name, soup_count, affinity, cp, mood);
        drawRoom(cat_x, prevPos, hasScratcher, hasTower);

        prevPos = cat_x;

        // 이동 처리 (간단히 랜덤 방향)
        int dir = rand() % 3 - 1;  // -1, 0, +1
        if (cat_x + dir >= HME_POS && cat_x + dir <= BWL_POS) {
            cat_x += dir;
        }

        Sleep(2500);
        system("cls");
    }

    return 0;
}



void printGameState(const char* name, int soup_count, int affinity, int cp, int mood) {
    const char* moodText[] = {
        "기분이 매우 나쁩니다.", "심심해합니다.",
        "식빵을 굽습니다.", "골골송을 부릅니다."
    };
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
    printf("기분 설명: %s\n", moodText[mood]);
    printf("집사와의 관계(0~4): %d\n", affinity);
    printf("  %s\n", affinityText[affinity]);
    printf("=========================================\n");
}

void drawRoom(int cat_x, int prevPos, int hasScratcher, int hasTower) {
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



