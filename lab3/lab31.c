#include<stdio.h>
int main(void)
{
	int  p1, p2;
	p1 = fork();
	if(!p1)
	{
		printf("p1 is working\n");
	}
	else
	{
		p2 = fork();
		if(!p2)
		{
			printf("p2 is working\n");
		}
		else
		{
			printf("father is working\n");
		}
	}
	return 0;
}
