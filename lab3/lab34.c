#include<stdio.h>
int main(void)
{
	int   i = 0, p1, p2;
	p1 = fork();
	if(!p1)
	{
		for(i = 0; i < 10; i ++)
		{
			printf("p1 is working %d\n", i);
		}
	}
	else
	{
		printf("before p2 fork\n");
		p2 = fork();
		int j = 0;
		if(!p2)
		{
			for(j = 0.; j < 10; j ++)
			{
				printf("p2 is working %d\n", j );
			}
		}
		else
		{
			int k = 0;
			for(k = 0; k < 10; k ++)
			{
				printf("father is working %d", k);
			}
		}
	}
	return 0;
}
