#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

#define ROOM_WIDTH 15
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

//  상태창 출력 기능
void printGameState(const char* name, int soup_count, int affinity, int cp);

void drawRoom(int cat_x);

int main() {
    char name[20];
    int soup_count = 0;
    int affinity = 2;
    int cp = 0;
    int cat_x = HME_POS;

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
        printGameState(name, soup_count, affinity, cp);
        drawRoom(cat_x);

        // 테스트용 간단 이동
        cat_x++;
        if (cat_x > BWL_POS) cat_x = HME_POS;

        Sleep(2000);
        system("cls");
    }

    return 0;
}

// 상태창 출력 기능
void printGameState(const char* name, int soup_count, int affinity, int cp) {
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
    printf("집사와의 관계(0~4): %d\n", affinity);
    printf("  %s\n", affinityText[affinity]);
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

