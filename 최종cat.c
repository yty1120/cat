#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define ROOM_WIDTH 15
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

void printGameState(const char* name, int soup_count, int affinity, int cp);
void drawRoom(int cat_x, int prevPos);


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


int main() {
    char name[20];
    int soup_count = 0;
    int affinity = 2;
    int cp = 0;
    int cat_x = HME_POS;
    int prevPos = -1;

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
        

       
        drawRoom(cat_x, prevPos);
       

        int userChoice;
        while (1) {
            printf("어떤 상호작용을 하시겠습니까? 0. 아무것도 하지 않음  1. 긁어 주기\n>> ");
            if (scanf_s("%d", &userChoice) != 1 || (userChoice != 0 && userChoice != 1)) {
                printf("잘못된 입력입니다. 다시 입력해주세요.\n");
                while (getchar() != '\n');
            }
            else break;
        }


        
        if (userChoice == 1) {
            printf("%s의 턱을 긁어주었습니다.\n", name);
            printf("2/6의 확률로 친밀도가 높아집니다.\n");
        }

        int diceRoll = rand() % 6 + 1;
        printf("\n주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", diceRoll);

        if (diceRoll >= (6 - affinity)) {
            if (cat_x < BWL_POS) {
                cat_x++;
                printf("야옹이가 냄비 쪽으로 이동합니다.\n");
            }
            else {
                printf("냄비 벽에 막혀 이동하지 못했습니다.\n");
            }
        }
        else {
            if (cat_x > HME_POS) {
                cat_x--;
                printf("야옹이가 집 쪽으로 이동합니다.\n");
            }
            else {
                printf("집 벽에 막혀 이동하지 못했습니다.\n");
            }
        }

        if (userChoice == 1) {
            if (diceRoll >= 5) {
                if (affinity < 4) {
                    affinity++;
                    printf("친밀도가 높아집니다.\n");
                }
                else {
                    printf("이미 최고 친밀도입니다.\n");
                }
            }
            else {
                printf("친밀도는 그대로입니다.\n");
            }
        }
       

        prevPos = cat_x;

        // ==================== [2-7. CP 생산 기능 추가] ====================
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
        // ================================================================

        Sleep(2500);
        system("cls");
    }

    return 0;
}


void drawRoom(int cat_x, int prevPos) {
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
        else if (i == prevPos && prevPos != cat_x) printf(".");
        else printf(" ");
    }
    printf("#\n");
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n\n");
}




