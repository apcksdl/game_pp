#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "screen.h"
#include "snake.h"
#include "util.h"
#include <time.h>

int GameState;
int GameStartSnakeLength;
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

// 게임 초기화 함수
int Initialize()
{
    // 게임 상태와 관련된 변수들을 초기화합니다.
    InitializeGameState();

    // 화면 설정과 관련된 함수들을 호출하여 화면을 초기화합니다.
    InitializeScreen();

    srand(time(NULL));

    // 사과와 폭탄의 초기화 및 위치 확인을 수행합니다.
    InitializeFoodAndBombs();

    // 뱀의 세그먼트 배열을 초기화합니다.
    InitializeSnakeSegments();

    // 초기 뱀의 길이만큼 세그먼트를 활성화하고 위치를 설정합니다.
    ActivateInitialSnakeSegments();

    // 초기화 작업이 완료되었으므로 0을 반환합니다.
    return 0;
}

int Release()
{
    return 0;
}

// 사용자 입력 처리 함수
void ProcessInput()
{
    if (_kbhit())  // 키 입력 여부를 확인합니다.
    {
        char key = _getch();  // 키를 읽어옵니다.
        switch (key)
        {
        case 'w':
            if (SnakeDirection != 2)
                SnakeDirection = 0;
            break;
        case 'a':
            if (SnakeDirection != 3)
                SnakeDirection = 1;
            break;
        case 's':
            if (SnakeDirection != 0)
                SnakeDirection = 2;
            break;
        case 'd':
            if (SnakeDirection != 1)
                SnakeDirection = 3;
            break;
        case 'q':
            GameState = 0;  // 'q' 키를 누르면 게임 상태를 종료로 변경합니다.
            break;
        }
    }
}

// 사과 초기화 함수
void InitApple()
{
    apple.posX = rand() % 68 + 1;  // 1부터 68 사이의 랜덤한 X 좌표를 설정합니다.
    apple.posY = rand() % 18 + 1;  // 1부터 18 사이의 랜덤한 Y 좌표를 설정합니다.
    apple.isActive = 1;  // 사과를 활성화 상태로 설정합니다.
}

// 폭탄 초기화 함수
void InitBomb()
{
    for (int i = 0; i < MAX_BOMB_NUM; i++)
    {
        bomb[i].posX = rand() % 68 + 1;  // 1부터 68 사이의 랜덤한 X 좌표를 설정합니다.
        bomb[i].posY = rand() % 18 + 1;  // 1부터 18 사이의 랜덤한 Y 좌표를 설정합니다.
        bomb[i].isActive = 1;  // 폭탄을 활성화 상태로 설정합니다.
    }

    // 폭탄의 위치가 사과와 겹치지 않도록 조정합니다.
    while ((bomb[0].posX == apple.posX && bomb[0].posY == apple.posY) ||
        (bomb[1].posX == apple.posX && bomb[1].posY == apple.posY) ||
        (bomb[2].posX == apple.posX && bomb[2].posY == apple.posY))
    {
        for (int i = 0; i < MAX_BOMB_NUM; i++)
        {
            bomb[i].posX = rand() % 68 + 1;  // 1부터 68 사이의 랜덤한 X 좌표를 다시 설정합니다.
            bomb[i].posY = rand() % 18 + 1;  // 1부터 18 사이의 랜덤한 Y 좌표를 다시 설정합니다.
        }
    }
}

void MoveApple()
{
    int prevX = apple.posX;  // 이전 사과의 X 좌표를 저장합니다.
    int prevY = apple.posY;  // 이전 사과의 Y 좌표를 저장합니다.

    do {
        apple.posX = rand() % 68 + 1;  // 1부터 68 사이의 랜덤한 X 좌표를 설정합니다.
        apple.posY = rand() % 18 + 1;  // 1부터 18 사이의 랜덤한 Y 좌표를 설정합니다.
    } while ((apple.posX == prevX && apple.posY == prevY) ||
        (apple.posX == bomb[0].posX && apple.posY == bomb[0].posY) ||
        (apple.posX == bomb[1].posX && apple.posY == bomb[1].posY) ||
        (apple.posX == bomb[2].posX && apple.posY == bomb[2].posY));
    InitBomb();  // 사과의 새 위치를 설정한 후에 폭탄을 초기화합니다.
}


void MoveSnake(int dir)
{
    int i = GameStartSnakeLength - 1;  // 뱀의 꼬리부터 역순으로 위치를 변경하기 위한 인덱스 변수입니다.
    int tailX = snakeSkin[i].posX;  // 꼬리의 이전 X 좌표를 저장합니다.
    int tailY = snakeSkin[i].posY;  // 꼬리의 이전 Y 좌표를 저장합니다.

    while (i > 0)
    {
        snakeSkin[i].posX = snakeSkin[i - 1].posX;  // 각 뱀 조각을 이전 조각의 위치로 이동합니다.
        snakeSkin[i].posY = snakeSkin[i - 1].posY;
        i = i - 1;  // 인덱스를 감소시켜서 다음 뱀 조각으로 이동합니다.
    }

    switch (dir)
    {
    case 0:
        snakeSkin[0].posX = snakeSkin[0].posX;  // 상단으로 이동하므로 X 좌표는 유지됩니다.
        snakeSkin[0].posY = snakeSkin[0].posY - 1;  // Y 좌표를 1만큼 감소시킵니다.
        break;
    case 1:
        snakeSkin[0].posX = snakeSkin[0].posX - 1;  // 왼쪽으로 이동하므로 X 좌표를 1만큼 감소시킵니다.
        snakeSkin[0].posY = snakeSkin[0].posY;  // Y 좌표는 유지됩니다.
        break;
    case 2:
        snakeSkin[0].posX = snakeSkin[0].posX;  // 하단으로 이동하므로 X 좌표는 유지됩니다.
        snakeSkin[0].posY = snakeSkin[0].posY + 1;  // Y 좌표를 1만큼 증가시킵니다.
        break;
    case 3:
        snakeSkin[0].posX = snakeSkin[0].posX + 1;  // 오른쪽으로 이동하므로 X 좌표를 1만큼 증가시킵니다.
        snakeSkin[0].posY = snakeSkin[0].posY;  // Y 좌표는 유지됩니다.
        break;
    }

    if (GameStartSnakeLength > 1)
    {
        snakeSkin[GameStartSnakeLength].posX = tailX;  // 꼬리 조각의 X 좌표를 이전 꼬리의 X 좌표로 설정합니다.
        snakeSkin[GameStartSnakeLength].posY = tailY;  // 꼬리 조각의 Y 좌표를 이전 꼬리의 Y 좌표로 설정합니다.
        snakeSkin[GameStartSnakeLength].isActive = 1;  // 새로운 꼬리 조각을 활성화 상태로 설정합니다.
    }
}


int DeltaTimeSum = 0;  // DeltaTime의 합을 저장하는 변수입니다.

int DrawBuffer(int DeltaTime)
{
    setCursorPos(0, 0);  // 커서의 위치를 (0, 0)으로 설정합니다.
    SetColor(14, 0);  // 화면에 출력될 텍스트의 색상을 설정합니다.
    printf("%s", ScreenBuffer);  // ScreenBuffer를 출력합니다.

    DeltaTimeSum = DeltaTimeSum + DeltaTime;  // DeltaTimeSum에 현재 DeltaTime을 더합니다.
    if (DeltaTimeSum >= 200)  // DeltaTimeSum이 200 이상일 경우
    {
        int nextPosX = snakeSkin[0].posX;  // 뱀 머리의 다음 X 좌표를 저장하는 변수입니다.
        int nextPosY = snakeSkin[0].posY;  // 뱀 머리의 다음 Y 좌표를 저장하는 변수입니다.

        switch (SnakeDirection)  // 뱀의 현재 방향에 따라 다음 좌표를 설정합니다.
        {
        case 0:
            nextPosY = nextPosY - 1;  // 위로 이동하므로 Y 좌표를 1만큼 감소시킵니다.
            break;
        case 1:
            nextPosX = nextPosX - 1;  // 왼쪽으로 이동하므로 X 좌표를 1만큼 감소시킵니다.
            break;
        case 2:
            nextPosY = nextPosY + 1;  // 아래로 이동하므로 Y 좌표를 1만큼 증가시킵니다.
            break;
        case 3:
            nextPosX = nextPosX + 1;  // 오른쪽으로 이동하므로 X 좌표를 1만큼 증가시킵니다.
            break;
        }

        if (IsOutOfBounds(nextPosX, nextPosY))  // 다음 좌표가 경계를 벗어나는지 확인합니다.
        {
            GameState = 0;  // 게임 상태를 종료 상태로 설정합니다.
        }
        else
        {
            MoveSnake(SnakeDirection);  // 뱀을 이동시킵니다.
            DeltaTimeSum = 0;  // DeltaTimeSum을 초기화합니다.
        }
    }

    setCursorPos(apple.posX, apple.posY);  // 사과의 위치로 커서를 이동시킵니다.
    SetColor(0b1110, 0b0100);  // 사과의 색상을 설정합니다.
    printf("*");  // 사과를 출력합니다.

    for (int i = 0; i < MAX_BOMB_NUM; i++)  // 모든 폭탄에 대해 반복합니다.
    {
        setCursorPos(bomb[i].posX, bomb[i].posY);  // 폭탄의 위치로 커서를 이동시킵니다.
        SetColor(0b1110, 0b0000);  // 폭탄의 색상을 설정합니다.
        printf("@");  // 폭탄을 출력합니다.
    }

    int i = 0;
    while (i < GameStartSnakeLength)  // 게임 시작 시 뱀의 길이만큼 반복합니다.
    {
        setCursorPos(snakeSkin[i].posX, snakeSkin[i].posY);  // 뱀 조각의 위치로 커서를 이동시킵니다.
        SetColor(0b1110, 0b0010);  // 뱀 조각의 색상을 설정합니다.
        printf("0");  // 뱀 조각을 출력합니다.
        i = i + 1;
    }

    if (snakeSkin[0].posX == apple.posX && snakeSkin[0].posY == apple.posY)  // 뱀의 머리가 사과와 충돌한 경우
    {
        int tailIndex = GameStartSnakeLength;  // 꼬리 조각의 인덱스를 저장합니다.
        snakeSkin[tailIndex].isActive = 1;  // 새로운 꼬리 조각을 활성화 상태로 설정합니다.
        GameStartSnakeLength = GameStartSnakeLength + 1;  // 뱀의 길이를 1만큼 증가시킵니다.
        MoveApple();  // 사과를 이동시킵니다.

        Score++;  // 점수를 1만큼 증가시킵니다.

        setCursorPos(90, 11);  // 점수 출력 위치로 커서를 이동시킵니다.
        SetColor(0b0000, 0b1111);  // 점수의 색상을 설정합니다.
        printf("Score: %d\n", Score);  // 점수를 출력합니다.
    }

    for (int i = 0; i < MAX_BOMB_NUM; i++)  // 모든 폭탄에 대해 반복합니다.
    {
        if (snakeSkin[0].posX == bomb[i].posX && snakeSkin[0].posY == bomb[i].posY)  // 뱀의 머리가 폭탄과 충돌한 경우
        {
            GameState = 0;  // 게임 상태를 종료 상태로 설정합니다.
        }
    }

    SetColor(0b0000, 0b1111);  // 텍스트의 색상을 설정합니다.
    setCursorPos(0, 22);  // 커서를 (0, 22) 위치로 이동시킵니다.
    if (DeltaTime != 0)  // DeltaTime이 0이 아닐 경우
        printf("time : %d                 \nfps : %d                  \n", DeltaTime, 1000 / DeltaTime);
    // DeltaTime과 초당 프레임 수(fps)를 출력합니다.

    if (GameState == 0) {  // 게임 상태가 0인 경우 (게임 오버 상태)
        setCursorPos(90, 24);  // 커서를 (90, 24) 위치로 이동시킵니다.
        SetColor(0, 4);  // 텍스트의 색상을 설정합니다.
        printf(" Game Over \n");  // " Game Over "를 출력합니다.
    }

    return 0;  // DrawBuffer 함수의 반환 값을 0으로 설정하고 반환합니다.
}
    