#include<stdio.h>
int main(void)
{
	int i = 0, j = 0, k = 0, p1, p2;
	p1 = fork();
	if(!p1)
	{
		for(i = 0; i < 10; i ++)
		{
			lockf(1, 1, 0);
			printf("p1 is working %d\n", i);	
			lockf(1, 0, 0);
			sleep(1);
		}
	}
	else
	{
		p2 = fork();
		if(!p2)
		{		
			for(j = 0.; j < 10; j ++)
			{
				lockf(1, 1, 0);	
				printf("p2 is working %d\n", j );	
				lockf(1, 0, 0);
				sleep(1);
			}
		}
		else
		{
			for(k = 0; k < 10; k ++)
			{
				lockf(1, 1, 0);
				printf("father is working %d\n", k);
				lockf(1, 0, 0);
				sleep(1);
			}
		
		}
	}
	return 0;
}
