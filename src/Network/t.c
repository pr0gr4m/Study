#include <stdio.h>

int main(void)
{
	int i, clnt_cnt = 5;

	for (i = 0; i < clnt_cnt; i++)
	{
		if(i == 1)
		{
			while (i++ < clnt_cnt - 1)
				printf("%d cp to %d \n", i + 1, i);
			break;
		}
	}

	return 0;
}
