#include "util.h"

void CHECKERROR(int e)
{
	if (e == 1)
	{
		printf("\n[line:%d, %s] 에러가 발생하였습니다.\n", __LINE__, __func__);
		exit(1);
	}
}

int IsOutOfBounds(int posX, int posY)
{
	if (posX < 1 || posX >= 71 || posY < 1 || posY >= 21)
	{
		return 1; // 화면을 벗어남
	}
	else
		return 0; // 화면을 벗어나지 않음
}
