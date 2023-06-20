#include <time.h>
#include "start.h"

int GameState;

void ShowMenu()
{
    printf("게임 메뉴\n");
    printf("1. 지렁이 게임 시작\n");
    printf("2. 사과 많이먹기 게임 시작\n");
    printf("3. 게임 종료\n");
}

void StartSnakeGame()
{
    CHECKERROR(Initialize()); // 게임 초기화 함수 호출 및 에러 체크

    unsigned long time_end = GetTickCount(); // 현재 시간 기록
    unsigned long deltaTime = GetTickCount(); // 이전 프레임부터 경과한 시간

    while (GameState)
    {
        deltaTime = GetTickCount() - time_end; // 경과 시간 계산
        time_end = GetTickCount(); // 현재 시간 갱신

        DrawBuffer(deltaTime); // 화면 그리기
        ProcessInput(); // 입력 처리
        if (deltaTime < 33)
            Sleep(33 - deltaTime); // 일정 시간 딜레이
    }

    // 게임 상태 체크 및 메모리 해제
    CHECKERROR(Release());

    exit(1);
}

void StartAppleGame()
{
    CHECKERROR(Initialize()); // 게임 초기화 함수 호출 및 에러 체크

    unsigned long time_end = GetTickCount(); // 현재 시간 기록
    unsigned long deltaTime = GetTickCount(); // 이전 프레임부터 경과한 시간

    time_t startTime, currentTime;
    GameState = 1;
    startTime = time(NULL);

    while (GameState)
    {
        currentTime = time(NULL);
        deltaTime = GetTickCount() - time_end; // 경과 시간 계산
        time_end = GetTickCount(); // 현재 시간 갱신

        DrawBuffer(deltaTime); // 화면 그리기
        ProcessInput(); // 입력 처리
        if (deltaTime < 33)
            Sleep(33 - deltaTime); // 일정 시간 딜레이
        if (currentTime - startTime >= 20) // 제한 시간 20초가 지나면 게임이 종료되고 Game Over 출력
        {
            setCursorPos(90, 24);
            SetColor(0, 4);
            printf(" Game Over \n");
            break;
        }
        setCursorPos(90, 10);
        int remainingTime = 20 - (currentTime - startTime);
        printf("남은 시간: %d초 \n", remainingTime);
    }

    // 게임 상태 체크 및 메모리 해제
    CHECKERROR(Release());

    exit(1);
}
