#include <time.h>
#include "start.h"

int GameState;

void ShowMenu()
{
    printf("���� �޴�\n");
    printf("1. ������ ���� ����\n");
    printf("2. ��� ���̸Ա� ���� ����\n");
    printf("3. ���� ����\n");
}

void StartSnakeGame()
{
    CHECKERROR(Initialize()); // ���� �ʱ�ȭ �Լ� ȣ�� �� ���� üũ

    unsigned long time_end = GetTickCount(); // ���� �ð� ���
    unsigned long deltaTime = GetTickCount(); // ���� �����Ӻ��� ����� �ð�

    while (GameState)
    {
        deltaTime = GetTickCount() - time_end; // ��� �ð� ���
        time_end = GetTickCount(); // ���� �ð� ����

        DrawBuffer(deltaTime); // ȭ�� �׸���
        ProcessInput(); // �Է� ó��
        if (deltaTime < 33)
            Sleep(33 - deltaTime); // ���� �ð� ������
    }

    // ���� ���� üũ �� �޸� ����
    CHECKERROR(Release());

    exit(1);
}

void StartAppleGame()
{
    CHECKERROR(Initialize()); // ���� �ʱ�ȭ �Լ� ȣ�� �� ���� üũ

    unsigned long time_end = GetTickCount(); // ���� �ð� ���
    unsigned long deltaTime = GetTickCount(); // ���� �����Ӻ��� ����� �ð�

    time_t startTime, currentTime;
    GameState = 1;
    startTime = time(NULL);

    while (GameState)
    {
        currentTime = time(NULL);
        deltaTime = GetTickCount() - time_end; // ��� �ð� ���
        time_end = GetTickCount(); // ���� �ð� ����

        DrawBuffer(deltaTime); // ȭ�� �׸���
        ProcessInput(); // �Է� ó��
        if (deltaTime < 33)
            Sleep(33 - deltaTime); // ���� �ð� ������
        if (currentTime - startTime >= 20) // ���� �ð� 20�ʰ� ������ ������ ����ǰ� Game Over ���
        {
            setCursorPos(90, 24);
            SetColor(0, 4);
            printf(" Game Over \n");
            break;
        }
        setCursorPos(90, 10);
        int remainingTime = 20 - (currentTime - startTime);
        printf("���� �ð�: %d�� \n", remainingTime);
    }

    // ���� ���� üũ �� �޸� ����
    CHECKERROR(Release());

    exit(1);
}
