#include "util.h"

void CHECKERROR(int e)
{
	if (e == 1)
	{
		printf("\n[line:%d, %s] ������ �߻��Ͽ����ϴ�.\n", __LINE__, __func__);
		exit(1);
	}
}

int IsOutOfBounds(int posX, int posY)
{
	if (posX < 1 || posX >= 71 || posY < 1 || posY >= 21)
	{
		return 1; // ȭ���� ���
	}
	else
		return 0; // ȭ���� ����� ����
}
