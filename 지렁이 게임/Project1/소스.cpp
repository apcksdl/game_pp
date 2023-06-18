include <stdio.h>
#include <string.h>
int main()
{
	int i, sum;
	for (i = 1; i < 100; i++)
	{
		if ((i % 3) == 0)
		{
			continue;
		}
		sum += i;
	}
	return 0;
}