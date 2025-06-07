#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

#define ROOM_WIDTH 15
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

// 상태창 출력 기능
void printGameState(int soup_count, int affinity, int mood);


void drawRoom(int cat_x);

int main() {
    int soup_count = 0;    // 만든 수프 개수
    int affinity = 2;      // 집사와의 친밀도
    int mood = 3;          // 고양이 기분 (0~3)
    int cat_x = HME_POS;   // 고양이 위치

    srand((unsigned int)time(NULL));

    while (1) {
        //  기분 시스템 - 주사위로 기분 변화
        int moodRoll = rand() % 6 + 1;
        int threshold = 6 - affinity;
        printf("주사위를 굴립니다... %d 나옴\n", moodRoll);

        if (moodRoll <= threshold && mood > 0) {
            mood--;
            printf("기분이 나빠졌습니다! 현재 기분: %d\n", mood);
        }

        printGameState(soup_count, affinity, mood); // 상태창 출력
        drawRoom(cat_x); // 방 출력

        //  고양이 위치 이동 기분에 따라 이동
        if (mood == 0 && cat_x > HME_POS) cat_x--;
        else if (mood == 3 && cat_x < BWL_POS) cat_x++;

        Sleep(2500);
        system("cls");
    }

    return 0;
}

//  상태창 출력 기능
void printGameState(int soup_count, int affinity, int mood) {
    const char* moodText[] = {
        "기분이 매우 나쁩니다.",
        "심심해합니다.",
        "식빵을 굽습니다.",
        "골골송을 부릅니다."
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
    printf("집사와의 관계(0~4): %d - %s\n", affinity, affinityText[affinity]);
    printf("고양이의 기분(0~3): %d - %s\n", mood, moodText[mood]);
    printf("=========================================\n");
}


void drawRoom(int cat_x) {
    printf("\n");
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n#");
    for (int i = 1; i < ROOM_WIDTH - 1; i++) {
        if (i == HME_POS) printf("H");
        else if (i == BWL_POS) printf("B");
        else printf(" ");
    }
    printf("#\n#");
    for (int i = 1; i < ROOM_WIDTH - 1; i++) {
        if (i == cat_x) printf("C");
        else printf(" ");
    }
    printf("#\n");
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n\n");
}

