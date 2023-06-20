#include "screen.h"
#include <Windows.h>

int screenWIdth = 70;  // 화면의 너비를 저장하는 변수입니다.
int screenHeight = 20;  // 화면의 높이를 저장하는 변수입니다.

void setScreenSize(int width, int height)
{
	screenWIdth = width;  // 화면의 너비를 설정합니다.
	screenHeight = height;  // 화면의 높이를 설정합니다.
}

void setCursorIcon(int isActive)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);  // 현재 콘솔 커서 정보를 가져옵니다.
	cursorInfo.bVisible = (isActive != 0);  // isActive 값에 따라 커서의 표시 여부를 설정합니다.
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);  // 콘솔 커서 정보를 설정합니다.
}

void setCursorPos(int x, int y)
{
	/* 가로 74 세로 22 */
	COORD pos = { x, y };  // 커서의 위치를 x, y 좌표로 설정합니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  // 콘솔 커서의 위치를 설정합니다.
}

void setCursorVisibility(int isVisible)
{
	setCursorIcon(isVisible);  // 커서의 표시 여부를 설정합니다.
}

void SetColor(unsigned short backgroundColor, unsigned short textColor)
{
	unsigned short color = textColor;  // 텍스트 색상 값을 설정합니다.
	color = color + (backgroundColor << 4);  // 배경 색상 값을 설정합니다.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);  // 텍스트 색상과 배경 색상을 설정합니다.
}

void ClearBuffer()
{
	int y = 0;
	while (y < screenHeight + 2)  // 화면의 높이 + 2까지 반복합니다.
	{
		int x = 0;
		while (x < screenWIdth + 2)  // 화면의 너비 + 2까지 반복합니다.
		{
			if (y == 0 || y == (screenHeight + 1))
				ScreenBuffer[x + (y * (screenWIdth + 3))] = '-';  // 첫 번째 행과 마지막 행에는 '-'를 설정합니다.
			else
			{
				if (x == 0 || x == (screenWIdth + 1))
					ScreenBuffer[x + (y * (screenWIdth + 3))] = '|';  // 첫 번째 열과 마지막 열에는 '|'를 설정합니다.
				else
					ScreenBuffer[x + (y * (screenWIdth + 3))] = ' ';  // 나머지 영역에는 공백을 설정합니다.
			}
			x = x + 1;
		}
		ScreenBuffer[x + (y * (screenWIdth + 3))] = '\n';  // 줄 바꿈 문자를 설정합니다.
		y = y + 1;
	}
	ScreenBuffer[(y * (screenWIdth + 3))] = '\0';  // 널 종료 문자를 설정합니다.
}

int WriteToBuffer(int x, int y, const char* str)
{
	int i = 0;

	while (i < strlen(str))
	{
		ScreenBuffer[x + (y * (screenWIdth + 3)) + i] = str[i];  // 화면 버퍼에 문자열을 씁니다.
		i = i + 1;
	}
	return 0;
}
