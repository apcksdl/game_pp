#include "screen.h"
#include <Windows.h>

int screenWIdth = 70;  // ȭ���� �ʺ� �����ϴ� �����Դϴ�.
int screenHeight = 20;  // ȭ���� ���̸� �����ϴ� �����Դϴ�.

void setScreenSize(int width, int height)
{
	screenWIdth = width;  // ȭ���� �ʺ� �����մϴ�.
	screenHeight = height;  // ȭ���� ���̸� �����մϴ�.
}

void setCursorIcon(int isActive)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);  // ���� �ܼ� Ŀ�� ������ �����ɴϴ�.
	cursorInfo.bVisible = (isActive != 0);  // isActive ���� ���� Ŀ���� ǥ�� ���θ� �����մϴ�.
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);  // �ܼ� Ŀ�� ������ �����մϴ�.
}

void setCursorPos(int x, int y)
{
	/* ���� 74 ���� 22 */
	COORD pos = { x, y };  // Ŀ���� ��ġ�� x, y ��ǥ�� �����մϴ�.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  // �ܼ� Ŀ���� ��ġ�� �����մϴ�.
}

void setCursorVisibility(int isVisible)
{
	setCursorIcon(isVisible);  // Ŀ���� ǥ�� ���θ� �����մϴ�.
}

void SetColor(unsigned short backgroundColor, unsigned short textColor)
{
	unsigned short color = textColor;  // �ؽ�Ʈ ���� ���� �����մϴ�.
	color = color + (backgroundColor << 4);  // ��� ���� ���� �����մϴ�.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);  // �ؽ�Ʈ ����� ��� ������ �����մϴ�.
}

void ClearBuffer()
{
	int y = 0;
	while (y < screenHeight + 2)  // ȭ���� ���� + 2���� �ݺ��մϴ�.
	{
		int x = 0;
		while (x < screenWIdth + 2)  // ȭ���� �ʺ� + 2���� �ݺ��մϴ�.
		{
			if (y == 0 || y == (screenHeight + 1))
				ScreenBuffer[x + (y * (screenWIdth + 3))] = '-';  // ù ��° ��� ������ �࿡�� '-'�� �����մϴ�.
			else
			{
				if (x == 0 || x == (screenWIdth + 1))
					ScreenBuffer[x + (y * (screenWIdth + 3))] = '|';  // ù ��° ���� ������ ������ '|'�� �����մϴ�.
				else
					ScreenBuffer[x + (y * (screenWIdth + 3))] = ' ';  // ������ �������� ������ �����մϴ�.
			}
			x = x + 1;
		}
		ScreenBuffer[x + (y * (screenWIdth + 3))] = '\n';  // �� �ٲ� ���ڸ� �����մϴ�.
		y = y + 1;
	}
	ScreenBuffer[(y * (screenWIdth + 3))] = '\0';  // �� ���� ���ڸ� �����մϴ�.
}

int WriteToBuffer(int x, int y, const char* str)
{
	int i = 0;

	while (i < strlen(str))
	{
		ScreenBuffer[x + (y * (screenWIdth + 3)) + i] = str[i];  // ȭ�� ���ۿ� ���ڿ��� ���ϴ�.
		i = i + 1;
	}
	return 0;
}
