#include<stdio.h>
int main(void)
{
	int i = 0, j = 0, k = 0, p1, p2;
	p1 = fork();
	if(!p1)
	{
		lockf(1, 1, 0);
		for(i = 0; i < 10; i ++)
		{
			printf("p1 is working %d\n", i);
			sleep(1);
		}
		lockf(1, 0, 0);
	}
	else
	{
		p2 = fork();
		if(!p2)
		{
			lockf(1, 1, 0);
			for(j = 0.; j < 10; j ++)
			{
				printf("p2 is working %d\n", j );
				sleep(1);
			}
			lockf(1, 0, 0);
		}
		else
		{
			lockf(1, 1, 0);
			for(k = 0; k < 10; k ++)
			{
				printf("father is working %d\n", k);
				sleep(1);
			}
			lockf(1, 0, 0);
		}
	}
	return 0;
}
