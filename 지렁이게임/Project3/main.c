#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "screen.h"
#include "util.h"
#include "snake.h"
#include "start.h"
#include "Initialize.h"

int main()
{
    int choice;
    ShowMenu(); // 게임 메뉴를 출력합니다.
    scanf_s("%d", &choice); // 사용자로부터 선택을 입력받습니다.

    if (choice == 1)
    {
        printf("지렁이 게임을 시작합니다.\n");
        StartSnakeGame(); // 지렁이 게임을 시작합니다.
    }
    else if (choice == 2)
    {
        printf("사과 많이먹기 게임을 시작합니다.\n");
        StartAppleGame(); // 사과 많이먹기 게임을 시작합니다
    }
    else if (choice == 3)
    {
        printf("게임을 종료합니다.\n");
        return 0; // 프로그램을 종료합니다.
    }
    else
    {
        printf("잘못된 선택입니다. 다시 시도하세요.\n");
        while (getchar() != '\n'); // 버퍼를 비워주기 위해 입력 버퍼에 남은 문자들을 제거합니다.
        getchar(); // 다음 입력을 받기 위해 엔터 키 입력을 기다립니다.
        main(); // 선택을 다시 받기 위해 메인 함수를 재귀적으로 호출합니다.
    }
}
