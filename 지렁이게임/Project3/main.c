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
    ShowMenu(); // ���� �޴��� ����մϴ�.
    scanf_s("%d", &choice); // ����ڷκ��� ������ �Է¹޽��ϴ�.

    if (choice == 1)
    {
        printf("������ ������ �����մϴ�.\n");
        StartSnakeGame(); // ������ ������ �����մϴ�.
    }
    else if (choice == 2)
    {
        printf("��� ���̸Ա� ������ �����մϴ�.\n");
        StartAppleGame(); // ��� ���̸Ա� ������ �����մϴ�
    }
    else if (choice == 3)
    {
        printf("������ �����մϴ�.\n");
        return 0; // ���α׷��� �����մϴ�.
    }
    else
    {
        printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        while (getchar() != '\n'); // ���۸� ����ֱ� ���� �Է� ���ۿ� ���� ���ڵ��� �����մϴ�.
        getchar(); // ���� �Է��� �ޱ� ���� ���� Ű �Է��� ��ٸ��ϴ�.
        main(); // ������ �ٽ� �ޱ� ���� ���� �Լ��� ��������� ȣ���մϴ�.
    }
}
