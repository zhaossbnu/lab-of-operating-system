#include<stdio.h>
int main(void)
{
	int  p1, p2;
	printf("before p1 fork\t");
	p1 = fork();
	if(!p1)
	{

	}
	else
	{
		printf("before p2 fork\t");
		p2 = fork();
		if(!p2)
		{

		}
		else
		{

		}
	}
	return 0;
}
