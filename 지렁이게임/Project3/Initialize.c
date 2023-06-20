#include "screen.h"
#include "snake.h"
#include "Initialize.h"

int GameState;
int GameStartSnakeLength;
int ActiveSnakeNum;
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

// ���� ���¿� ���õ� �������� �ʱ�ȭ�մϴ�.
void InitializeGameState()
{
    GameState = 1; // ���� ���¸� 1�� �����Ͽ� ������ ���� ������ ��Ÿ���ϴ�.
    GameStartSnakeLength = 3; // �ʱ� ���� ���̸� 3���� �����մϴ�.
    ActiveSnakeNum = GameStartSnakeLength; // Ȱ��ȭ�� ���� ���� �ʱ� ���� ���̷� �����մϴ�.
    Score = 0; // ������ 0���� �ʱ�ȭ�մϴ�.
}

// ȭ�� ������ ���õ� �Լ����� ȣ���Ͽ� ȭ���� �ʱ�ȭ�մϴ�.
void InitializeScreen()
{
    setScreenSize(70, 20); // ȭ�� ũ�⸦ 70x20���� �����մϴ�.
    setCursorVisibility(0); // Ŀ���� ������ �ʵ��� �����մϴ�.
    SetColor(14, 0); // ȭ�� ������ �����մϴ�.
    ClearBuffer(); // ȭ�� ���۸� ����ϴ�.
}

// ����� ��ź�� �ʱ�ȭ �� ��ġ Ȯ���� �����մϴ�.
void InitializeFoodAndBombs()
{
    InitApple(); // ����� �ʱ�ȭ�մϴ�.
    InitBomb(); // ��ź�� �ʱ�ȭ�մϴ�.

    int i = 0;
    while (i < GameStartSnakeLength)
    {
        // �ʱ� ���� ��ġ�� ����� ��ź�� ��ġ�� ��ġ���� Ȯ���մϴ�.
        if ((snakeSkin[i].posX == apple.posX && snakeSkin[i].posY == apple.posY) ||
            (snakeSkin[i].posX == bomb[0].posX && snakeSkin[i].posY == bomb[0].posY) ||
            (snakeSkin[i].posX == bomb[1].posX && snakeSkin[i].posY == bomb[1].posY) ||
            (snakeSkin[i].posX == bomb[2].posX && snakeSkin[i].posY == bomb[2].posY))
        {
            // ��ġ�� ��� ����� ��ź�� ��ġ�� �缳���ϰ� i�� 0���� �ʱ�ȭ�Ͽ� �ٽ� Ȯ���մϴ�.
            InitApple();
            InitBomb();
            i = 0;
        }
        else
        {
            // ��ġ�� �ʴ� ��� i�� �������� ���� ��Ҹ� Ȯ���մϴ�.
            i = i + 1;
        }
    }
}

// ���� ���׸�Ʈ �迭�� �ʱ�ȭ�մϴ�.
void InitializeSnakeSegments()
{
    int i = 0;
    while (i < MAX_SNAKE_LENGTH)
    {
        // ��� ���׸�Ʈ�� ��ġ�� ���¸� �ʱ�ȭ�մϴ�.
        snakeSkin[i].posX = 35;
        snakeSkin[i].posY = 10;
        snakeSkin[i].isActive = 0;
        i = i + 1;
    }
}

// �ʱ� ���� ���̸�ŭ ���׸�Ʈ�� Ȱ��ȭ�ϰ� ��ġ�� �����մϴ�.
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