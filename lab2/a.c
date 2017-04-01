#include<stdio.h>
int main(void)
{
	int  p1, p2;
	p1 = fork();
	if(!p1)
	{
		printf("b\t");
	}
	else
	{
		p2 = fork();
		if(!p2)
		{
			printf("c\t");
		}
		else
		{
			printf("a\t");
		}
	}
	return 0;
}
