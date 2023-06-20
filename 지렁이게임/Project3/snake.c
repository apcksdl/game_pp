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

#define MAX_SNAKE_LENGTH 1400 // �ִ� ���� ���̸� ��Ÿ����, ���� �迭(snakeSkin)�� �ִ� ũ�⸦ ����
#define MAX_BOMB_NUM 3 // ��ź�� �ִ� ������ ����

struct GameObject
{
    int posX;
    int posY;
    int isActive;
};

struct GameObject snakeSkin[MAX_SNAKE_LENGTH];
struct GameObject apple;
struct GameObject bomb[MAX_BOMB_NUM];

// ���� �ʱ�ȭ �Լ�
int Initialize()
{
    // ���� ���¿� ���õ� �������� �ʱ�ȭ�մϴ�.
    InitializeGameState();

    // ȭ�� ������ ���õ� �Լ����� ȣ���Ͽ� ȭ���� �ʱ�ȭ�մϴ�.
    InitializeScreen();

    srand(time(NULL));

    // ����� ��ź�� �ʱ�ȭ �� ��ġ Ȯ���� �����մϴ�.
    InitializeFoodAndBombs();

    // ���� ���׸�Ʈ �迭�� �ʱ�ȭ�մϴ�.
    InitializeSnakeSegments();

    // �ʱ� ���� ���̸�ŭ ���׸�Ʈ�� Ȱ��ȭ�ϰ� ��ġ�� �����մϴ�.
    ActivateInitialSnakeSegments();

    // �ʱ�ȭ �۾��� �Ϸ�Ǿ����Ƿ� 0�� ��ȯ�մϴ�.
    return 0;
}

int Release()
{
    return 0;
}

// ����� �Է� ó�� �Լ�
void ProcessInput()
{
    if (_kbhit())  // Ű �Է� ���θ� Ȯ���մϴ�.
    {
        char key = _getch();  // Ű�� �о�ɴϴ�.
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
            GameState = 0;  // 'q' Ű�� ������ ���� ���¸� ����� �����մϴ�.
            break;
        }
    }
}

// ��� �ʱ�ȭ �Լ�
void InitApple()
{
    apple.posX = rand() % 68 + 1;  // 1���� 68 ������ ������ X ��ǥ�� �����մϴ�.
    apple.posY = rand() % 18 + 1;  // 1���� 18 ������ ������ Y ��ǥ�� �����մϴ�.
    apple.isActive = 1;  // ����� Ȱ��ȭ ���·� �����մϴ�.
}

// ��ź �ʱ�ȭ �Լ�
void InitBomb()
{
    for (int i = 0; i < MAX_BOMB_NUM; i++)
    {
        bomb[i].posX = rand() % 68 + 1;  // 1���� 68 ������ ������ X ��ǥ�� �����մϴ�.
        bomb[i].posY = rand() % 18 + 1;  // 1���� 18 ������ ������ Y ��ǥ�� �����մϴ�.
        bomb[i].isActive = 1;  // ��ź�� Ȱ��ȭ ���·� �����մϴ�.
    }

    // ��ź�� ��ġ�� ����� ��ġ�� �ʵ��� �����մϴ�.
    while ((bomb[0].posX == apple.posX && bomb[0].posY == apple.posY) ||
        (bomb[1].posX == apple.posX && bomb[1].posY == apple.posY) ||
        (bomb[2].posX == apple.posX && bomb[2].posY == apple.posY))
    {
        for (int i = 0; i < MAX_BOMB_NUM; i++)
        {
            bomb[i].posX = rand() % 68 + 1;  // 1���� 68 ������ ������ X ��ǥ�� �ٽ� �����մϴ�.
            bomb[i].posY = rand() % 18 + 1;  // 1���� 18 ������ ������ Y ��ǥ�� �ٽ� �����մϴ�.
        }
    }
}

void MoveApple()
{
    int prevX = apple.posX;  // ���� ����� X ��ǥ�� �����մϴ�.
    int prevY = apple.posY;  // ���� ����� Y ��ǥ�� �����մϴ�.

    do {
        apple.posX = rand() % 68 + 1;  // 1���� 68 ������ ������ X ��ǥ�� �����մϴ�.
        apple.posY = rand() % 18 + 1;  // 1���� 18 ������ ������ Y ��ǥ�� �����մϴ�.
    } while ((apple.posX == prevX && apple.posY == prevY) ||
        (apple.posX == bomb[0].posX && apple.posY == bomb[0].posY) ||
        (apple.posX == bomb[1].posX && apple.posY == bomb[1].posY) ||
        (apple.posX == bomb[2].posX && apple.posY == bomb[2].posY));
    InitBomb();  // ����� �� ��ġ�� ������ �Ŀ� ��ź�� �ʱ�ȭ�մϴ�.
}


void MoveSnake(int dir)
{
    int i = GameStartSnakeLength - 1;  // ���� �������� �������� ��ġ�� �����ϱ� ���� �ε��� �����Դϴ�.
    int tailX = snakeSkin[i].posX;  // ������ ���� X ��ǥ�� �����մϴ�.
    int tailY = snakeSkin[i].posY;  // ������ ���� Y ��ǥ�� �����մϴ�.

    while (i > 0)
    {
        snakeSkin[i].posX = snakeSkin[i - 1].posX;  // �� �� ������ ���� ������ ��ġ�� �̵��մϴ�.
        snakeSkin[i].posY = snakeSkin[i - 1].posY;
        i = i - 1;  // �ε����� ���ҽ��Ѽ� ���� �� �������� �̵��մϴ�.
    }

    switch (dir)
    {
    case 0:
        snakeSkin[0].posX = snakeSkin[0].posX;  // ������� �̵��ϹǷ� X ��ǥ�� �����˴ϴ�.
        snakeSkin[0].posY = snakeSkin[0].posY - 1;  // Y ��ǥ�� 1��ŭ ���ҽ�ŵ�ϴ�.
        break;
    case 1:
        snakeSkin[0].posX = snakeSkin[0].posX - 1;  // �������� �̵��ϹǷ� X ��ǥ�� 1��ŭ ���ҽ�ŵ�ϴ�.
        snakeSkin[0].posY = snakeSkin[0].posY;  // Y ��ǥ�� �����˴ϴ�.
        break;
    case 2:
        snakeSkin[0].posX = snakeSkin[0].posX;  // �ϴ����� �̵��ϹǷ� X ��ǥ�� �����˴ϴ�.
        snakeSkin[0].posY = snakeSkin[0].posY + 1;  // Y ��ǥ�� 1��ŭ ������ŵ�ϴ�.
        break;
    case 3:
        snakeSkin[0].posX = snakeSkin[0].posX + 1;  // ���������� �̵��ϹǷ� X ��ǥ�� 1��ŭ ������ŵ�ϴ�.
        snakeSkin[0].posY = snakeSkin[0].posY;  // Y ��ǥ�� �����˴ϴ�.
        break;
    }

    if (GameStartSnakeLength > 1)
    {
        snakeSkin[GameStartSnakeLength].posX = tailX;  // ���� ������ X ��ǥ�� ���� ������ X ��ǥ�� �����մϴ�.
        snakeSkin[GameStartSnakeLength].posY = tailY;  // ���� ������ Y ��ǥ�� ���� ������ Y ��ǥ�� �����մϴ�.
        snakeSkin[GameStartSnakeLength].isActive = 1;  // ���ο� ���� ������ Ȱ��ȭ ���·� �����մϴ�.
    }
}


int DeltaTimeSum = 0;  // DeltaTime�� ���� �����ϴ� �����Դϴ�.

int DrawBuffer(int DeltaTime)
{
    setCursorPos(0, 0);  // Ŀ���� ��ġ�� (0, 0)���� �����մϴ�.
    SetColor(14, 0);  // ȭ�鿡 ��µ� �ؽ�Ʈ�� ������ �����մϴ�.
    printf("%s", ScreenBuffer);  // ScreenBuffer�� ����մϴ�.

    DeltaTimeSum = DeltaTimeSum + DeltaTime;  // DeltaTimeSum�� ���� DeltaTime�� ���մϴ�.
    if (DeltaTimeSum >= 200)  // DeltaTimeSum�� 200 �̻��� ���
    {
        int nextPosX = snakeSkin[0].posX;  // �� �Ӹ��� ���� X ��ǥ�� �����ϴ� �����Դϴ�.
        int nextPosY = snakeSkin[0].posY;  // �� �Ӹ��� ���� Y ��ǥ�� �����ϴ� �����Դϴ�.

        switch (SnakeDirection)  // ���� ���� ���⿡ ���� ���� ��ǥ�� �����մϴ�.
        {
        case 0:
            nextPosY = nextPosY - 1;  // ���� �̵��ϹǷ� Y ��ǥ�� 1��ŭ ���ҽ�ŵ�ϴ�.
            break;
        case 1:
            nextPosX = nextPosX - 1;  // �������� �̵��ϹǷ� X ��ǥ�� 1��ŭ ���ҽ�ŵ�ϴ�.
            break;
        case 2:
            nextPosY = nextPosY + 1;  // �Ʒ��� �̵��ϹǷ� Y ��ǥ�� 1��ŭ ������ŵ�ϴ�.
            break;
        case 3:
            nextPosX = nextPosX + 1;  // ���������� �̵��ϹǷ� X ��ǥ�� 1��ŭ ������ŵ�ϴ�.
            break;
        }

        if (IsOutOfBounds(nextPosX, nextPosY))  // ���� ��ǥ�� ��踦 ������� Ȯ���մϴ�.
        {
            GameState = 0;  // ���� ���¸� ���� ���·� �����մϴ�.
        }
        else
        {
            MoveSnake(SnakeDirection);  // ���� �̵���ŵ�ϴ�.
            DeltaTimeSum = 0;  // DeltaTimeSum�� �ʱ�ȭ�մϴ�.
        }
    }

    setCursorPos(apple.posX, apple.posY);  // ����� ��ġ�� Ŀ���� �̵���ŵ�ϴ�.
    SetColor(0b1110, 0b0100);  // ����� ������ �����մϴ�.
    printf("*");  // ����� ����մϴ�.

    for (int i = 0; i < MAX_BOMB_NUM; i++)  // ��� ��ź�� ���� �ݺ��մϴ�.
    {
        setCursorPos(bomb[i].posX, bomb[i].posY);  // ��ź�� ��ġ�� Ŀ���� �̵���ŵ�ϴ�.
        SetColor(0b1110, 0b0000);  // ��ź�� ������ �����մϴ�.
        printf("@");  // ��ź�� ����մϴ�.
    }

    int i = 0;
    while (i < GameStartSnakeLength)  // ���� ���� �� ���� ���̸�ŭ �ݺ��մϴ�.
    {
        setCursorPos(snakeSkin[i].posX, snakeSkin[i].posY);  // �� ������ ��ġ�� Ŀ���� �̵���ŵ�ϴ�.
        SetColor(0b1110, 0b0010);  // �� ������ ������ �����մϴ�.
        printf("0");  // �� ������ ����մϴ�.
        i = i + 1;
    }

    if (snakeSkin[0].posX == apple.posX && snakeSkin[0].posY == apple.posY)  // ���� �Ӹ��� ����� �浹�� ���
    {
        int tailIndex = GameStartSnakeLength;  // ���� ������ �ε����� �����մϴ�.
        snakeSkin[tailIndex].isActive = 1;  // ���ο� ���� ������ Ȱ��ȭ ���·� �����մϴ�.
        GameStartSnakeLength = GameStartSnakeLength + 1;  // ���� ���̸� 1��ŭ ������ŵ�ϴ�.
        MoveApple();  // ����� �̵���ŵ�ϴ�.

        Score++;  // ������ 1��ŭ ������ŵ�ϴ�.

        setCursorPos(90, 11);  // ���� ��� ��ġ�� Ŀ���� �̵���ŵ�ϴ�.
        SetColor(0b0000, 0b1111);  // ������ ������ �����մϴ�.
        printf("Score: %d\n", Score);  // ������ ����մϴ�.
    }

    for (int i = 0; i < MAX_BOMB_NUM; i++)  // ��� ��ź�� ���� �ݺ��մϴ�.
    {
        if (snakeSkin[0].posX == bomb[i].posX && snakeSkin[0].posY == bomb[i].posY)  // ���� �Ӹ��� ��ź�� �浹�� ���
        {
            GameState = 0;  // ���� ���¸� ���� ���·� �����մϴ�.
        }
    }

    SetColor(0b0000, 0b1111);  // �ؽ�Ʈ�� ������ �����մϴ�.
    setCursorPos(0, 22);  // Ŀ���� (0, 22) ��ġ�� �̵���ŵ�ϴ�.
    if (DeltaTime != 0)  // DeltaTime�� 0�� �ƴ� ���
        printf("time : %d                 \nfps : %d                  \n", DeltaTime, 1000 / DeltaTime);
    // DeltaTime�� �ʴ� ������ ��(fps)�� ����մϴ�.

    if (GameState == 0) {  // ���� ���°� 0�� ��� (���� ���� ����)
        setCursorPos(90, 24);  // Ŀ���� (90, 24) ��ġ�� �̵���ŵ�ϴ�.
        SetColor(0, 4);  // �ؽ�Ʈ�� ������ �����մϴ�.
        printf(" Game Over \n");  // " Game Over "�� ����մϴ�.
    }

    return 0;  // DrawBuffer �Լ��� ��ȯ ���� 0���� �����ϰ� ��ȯ�մϴ�.
}
    