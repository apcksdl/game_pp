#include "screen.h"
#include "snake.h"
#include "Initialize.h"

int GameState;
int GameStartSnakeLength;
int ActiveSnakeNum;
int SnakeDirection;
int Score;

#define MAX_SNAKE_LENGTH 1400 // 최대 뱀의 길이를 나타내며, 뱀의 배열(snakeSkin)의 최대 크기를 제한
#define MAX_BOMB_NUM 3 // 폭탄의 최대 개수를 정의

struct GameObject
{
    int posX;
    int posY;
    int isActive;
};

struct GameObject snakeSkin[MAX_SNAKE_LENGTH];
struct GameObject apple;
struct GameObject bomb[MAX_BOMB_NUM];

// 게임 상태와 관련된 변수들을 초기화합니다.
void InitializeGameState()
{
    GameState = 1; // 게임 상태를 1로 설정하여 게임이 진행 중임을 나타냅니다.
    GameStartSnakeLength = 3; // 초기 뱀의 길이를 3으로 설정합니다.
    ActiveSnakeNum = GameStartSnakeLength; // 활성화된 뱀의 수를 초기 뱀의 길이로 설정합니다.
    Score = 0; // 점수를 0으로 초기화합니다.
}

// 화면 설정과 관련된 함수들을 호출하여 화면을 초기화합니다.
void InitializeScreen()
{
    setScreenSize(70, 20); // 화면 크기를 70x20으로 설정합니다.
    setCursorVisibility(0); // 커서를 보이지 않도록 설정합니다.
    SetColor(14, 0); // 화면 색상을 설정합니다.
    ClearBuffer(); // 화면 버퍼를 지웁니다.
}

// 사과와 폭탄의 초기화 및 위치 확인을 수행합니다.
void InitializeFoodAndBombs()
{
    InitApple(); // 사과를 초기화합니다.
    InitBomb(); // 폭탄을 초기화합니다.

    int i = 0;
    while (i < GameStartSnakeLength)
    {
        // 초기 뱀의 위치가 사과와 폭탄의 위치와 겹치는지 확인합니다.
        if ((snakeSkin[i].posX == apple.posX && snakeSkin[i].posY == apple.posY) ||
            (snakeSkin[i].posX == bomb[0].posX && snakeSkin[i].posY == bomb[0].posY) ||
            (snakeSkin[i].posX == bomb[1].posX && snakeSkin[i].posY == bomb[1].posY) ||
            (snakeSkin[i].posX == bomb[2].posX && snakeSkin[i].posY == bomb[2].posY))
        {
            // 겹치는 경우 사과와 폭탄의 위치를 재설정하고 i를 0으로 초기화하여 다시 확인합니다.
            InitApple();
            InitBomb();
            i = 0;
        }
        else
        {
            // 겹치지 않는 경우 i를 증가시켜 다음 요소를 확인합니다.
            i = i + 1;
        }
    }
}

// 뱀의 세그먼트 배열을 초기화합니다.
void InitializeSnakeSegments()
{
    int i = 0;
    while (i < MAX_SNAKE_LENGTH)
    {
        // 모든 세그먼트의 위치와 상태를 초기화합니다.
        snakeSkin[i].posX = 35;
        snakeSkin[i].posY = 10;
        snakeSkin[i].isActive = 0;
        i = i + 1;
    }
}

// 초기 뱀의 길이만큼 세그먼트를 활성화하고 위치를 설정합니다.
void ActivateInitialSnakeSegments()
{
    int i = 0;
    while (i < GameStartSnakeLength)
    {
        snakeSkin[i].posX = 35 - i;
        snakeSkin[i].posY = 10;
        snakeSkin[i].isActive = 1;
        i = i + 1;
    }
}