/*
Author zhaossbnu
*/
#include<stdio.h>
#include<stdlib.h>
struct block
{
	int start;
	int len;
	int id;
	struct block *last;
	struct block *next;
}*blank = NULL, *allocated = NULL;

//��ʼ��δ�������ѷ����
void init()
{
	blank = (struct block *)malloc(sizeof(struct block));
	struct block* chushi = (struct block *)malloc(sizeof(struct block));
	blank->start = -1;
	blank->len = -1;
	blank->id = -1;
	chushi->start = 10240;
	chushi->len = 102400;
	chushi->id = 1;
	blank->last = NULL;
	blank->next = chushi;
	chushi->last = blank;
	chushi->next = NULL;

	allocated = (struct block *)malloc(sizeof(struct block));
	allocated->start = -1;
	allocated->len = -1;
	allocated->id = -1;
	allocated->last = NULL;
	allocated->next = NULL;
}

//�˳��� �ͷ�������������
void clear()
{
	struct block * current = blank;
	while(current != NULL)
	{
		struct block *p = current;
		current = current->next;
		free(p);
	}
	current = allocated;
	while(current != NULL)
	{
		struct block *p = current;
		current = current->next;
		free(p);
	}
}

//�ⲿ�˵���ʾ
int welcome1()
{
	int choose = 0;
	do
	{
		printf("��ѡ����(0-�˳� 1-�״���Ӧ 2-ѭ���״���Ӧ 3-�����Ӧ):");
		scanf("%d", &choose);
		if(choose != 0 && choose != 1 && choose != 2 && choose != 3)
			{
				printf("Error input!!!\n");
			}
	}while(choose != 0 && choose != 1 && choose != 2 && choose != 3);
	printf("\n");
	return choose;
}

//�ڲ��˵���ʾ
int welcome2()
{
	int choose =0;
	do
	{
		printf("ѡ������(0-�˳� 1-�������� 2-�������� 3-��ʾ����):");
		scanf("%d", &choose);
	}while(choose != 0 && choose != 1 && choose != 2 && choose != 3);
	printf("\n");
	return choose;
}

//��ʾ�ڴ�������
void print_mem()
{
	printf("���з��������£�\n");
	printf("��ʼ��ַ �������� ��־\n");
	struct block *current = blank->next;
	while(current != NULL)
	{
		printf("%d\t %d\t  %d\n", current->start,current->len, current->id);
		current = current->next;
	}
	printf("\n");
	printf("�ѷ�������\n");
	printf("��ʼ��ַ �������� ��־\n");
	current = allocated->next;
	while(current != NULL)
	{
		printf("%d\t %d\t  %d\n", current->start,current->len, current->id);
		current = current->next;
	}
	printf("\n");
}

//�����ڴ�
void recycle()
{
	int id = 0;
	int len = 0;
	printf("������ҵ��(����������):");
	scanf("%d", &id);
	struct block *current = allocated->next;
	bool in = false;
	while(current != NULL)
	{
		if(current->id == id)
		{
			in = true;
			break;
		}
		current = current->next;
	}
	if(!in)
	{
		printf("�Ҳ�����ҵ��\n\n");
		return ;
	}
	else
	{
		current->last->next = current->next;  //����ǰ�ڵ��Ƴ��ѷ����
		if(current ->next != NULL)
		{
			current->next->last = current->last;
		}
		struct block* p = blank->next;
		if(p == NULL)			//δ�����Ϊ��ʱ
		{
			current->id = 1;
			p = current;
			current->last = blank;
			blank->next = p;
			current->next = NULL;
			printf("\n");
			return ;
		}
		while(p != NULL)
		{
			//���߶��հ�
			if(p->start + p->len == current->start && p ->next != NULL && current->start + current->len == p->next->start)
			{
				p->len = p->len + current->len + p->next->len;
				struct block * p_a = p->next;
				if(p->next->next != NULL)
				{
					p->next->next->last = p;
				}
				p->next = p->next->next;
				free(current);
				free(p_a);
				printf("\n");
				return;
			}
			//ǰ���пհ�
			if(p->start + p->len == current->start)
			{
				p->len = p->len + current->len;
				free(current);
				printf("\n");
				return;
			}
			//�����пհ�
			if(current->start + current->len == p->start)
			{
				p->start = p->start - current->len;
				p->len += current->len;
				free(current);
				printf("\n");
				return;
			}
			//�޿հ�����֮������������ڵ��ǰ��
			if(current->start + current->len < p->start)
			{
				current->id = 1;
				current->next = p;
				current->last = p->last;
				p->last->next = current;
				p->last = current;
				printf("\n");
				return;
			}
			//�޿հ�����֮������������ڵ�ĺ���
			if(p->start + p->len < current->start && p->next != NULL && current->start + current->len < p->next->start)
			{
				current->id = 1;
				current->last = p;
				current->next = p->next;
				p->next->last = current;
				p->next = current;
				printf("\n");
				return;
			}
			//�Ѿ��ߵ���β
			if(p->next == NULL)
			{
				current->id = 1;
				p->next = current ;
				current->last = p;
				current->next = NULL;
				printf("\n");
				return;
			}
			p = p->next;
		}
	}
}

//�״���Ӧ
void first_adapt()
{
	init();
	int choose = welcome2();
	while(true)
	{
		switch(choose)
		{
		case 0:
			clear();
			return ;
		case 1:
			{
				int id = 0;
				int len = 0;
				printf("������ҵ��(����������):");
				scanf("%d", &id);
				struct block *current = allocated->next;
				bool can_in = true;   //������ҵ���Ƿ��ظ�
				while(current != NULL)
				{
					if(current->id == id)
					{
						can_in = false;
						break;
					}
					current = current->next;
				}
				if(!can_in)
				{
					printf("�����id�ظ���\n\n");
				}
				else
				{
					printf("������ҵ���賤��xk:");
					scanf("%d", &len);
					current = blank->next;
					//���÷���Ŀ����ϸ��Ϣ
					struct block * p = (struct block *)malloc(sizeof(struct block));
					p->id = id;
					p->len = len;
					p->last = NULL;
					p->next = NULL;
					if(current == NULL)
					{
						printf("�ڴ��ѱ��Ϸ���ϣ�\n\n");
						break ;
					}
					while(current != NULL)
					{
						if(current->len == len)		//��ǰ��պù�����
						{
							//���з���
							p->start = current->start;
							current->last->next = current->next;
							if(current ->next != NULL)
							{
								current->next->last = current->last;
							}
							else
							{
								current->next = NULL;
							}
							free(current);
							//���뵽�������
							struct block *a_current = allocated;
							while(a_current->next != NULL)
							{
								a_current = a_current->next;

							}
							a_current->next = p;
							p->last = a_current;
							break;
						}
						else if(current->len > len) //��ǰ�ڵ������Ҫ�Ĵ�С
						{
							//��ʼ���䲢�޸ĵ�ǰδ�������������Ϣ
							p->start = current->start + current->len -len ;
							current->len -= len;
							//���뵽�ѷ������
							struct block *current = allocated;
							while(current->next != NULL)
							{
								current = current->next;
							}
							current->next = p;
							p->last = current;
							break;
						}
						else
						{
							//��������Ѱ��
							current = current->next;
							if(current == NULL)         //�ҵ���β��δ�ҵ�  ˵���޷�����
							{
								printf("û����ô��Ŀ飡\n");
								break ;
							}
						}
					}
					printf("\n");
				}
			}
			break;
		case 2:
			recycle();
			break;
		case 3:
			print_mem();
			break;
		default:
			printf("Input Error!\n");
			break;
		}
		choose = welcome2();
	}
}

//ѭ���״���Ӧ
void rotation_first_adapt()
{
	init();
	int choose = welcome2();
	struct block* next_rotation = blank->next;   //��һ�η���ʱѭ���Ŀ�ʼ
	while(true)
	{
		switch(choose)
		{
		case 0:
			clear();
			return ;
		case 1:
			{
				int id = 0;
				int len = 0;
				printf("������ҵ��(����������):");
				scanf("%d", &id);
				struct block *current = allocated->next;
				bool can_in = true;   //������ҵ���Ƿ��ظ�
				while(current != NULL)
				{
					if(current->id == id)
					{
						can_in = false;
						break;
					}
					current = current->next;
				}
				if(!can_in)
				{
					printf("�����id�ظ���\n\n");
				}
				else
				{
					printf("������ҵ���賤��xk:");
					scanf("%d", &len);
					//����ϴ��ڴ汻�����ˣ�����������
					if(next_rotation == NULL)
					{
						next_rotation = current = blank->next;
					}
					else
					{
						current = next_rotation;    //����ǰ�ڵ�����Ϊ�ϴ����е�λ��
					}
					//���÷���Ŀ����ϸ��Ϣ
					struct block * p = (struct block *)malloc(sizeof(struct block));
					p->id = id;
					p->len = len;
					p->last = NULL;
					p->next = NULL;
					if(current == NULL)
					{
						printf("�ڴ��ѱ��Ϸ���ϣ�\n\n");
						break ;
					}
					while(current != NULL)
					{
						if(current->len == len)		//��ǰ��պù�����
						{
							//���з���
							p->start = current->start;
							current->last->next = current->next;
							if(current ->next != NULL)
							{
								current->next->last = current->last;
								//��δ�������β��������һ�ε�ѭ���ڵ�Ϊ��һ�ڵ�
								next_rotation = current->next;
							}
							else
							{
								//���ѵ��������β��������һ�ε�ѭ���ڵ�Ϊ����ʼ
								next_rotation = blank->next;
								current->next = NULL;
							}
							free(current);
							//���뵽�������
							struct block *a_current = allocated;
							while(a_current->next != NULL)
							{
								a_current = a_current->next;

							}
							a_current->next = p;
							p->last = a_current;
							printf("\n");
							break;
						}
						else if(current->len > len) //��ǰ�ڵ������Ҫ�Ĵ�С
						{
							//��ʼ���䲢�޸ĵ�ǰδ�������������Ϣ
							p->start = current->start + current->len -len ;
							current->len -= len;
							if(current ->next != NULL)
							{
								//��δ�������β��������һ�ε�ѭ���ڵ�Ϊ��һ�ڵ�
								next_rotation = current->next;
							}
							else
							{
								//���ѵ��������β��������һ�ε�ѭ���ڵ�Ϊ����ʼ
								next_rotation = blank->next;
							}
							//���뵽�ѷ������
							struct block *current = allocated;
							while(current->next != NULL)
							{
								current = current->next;
							}
							current->next = p;
							p->last = current;
							printf("\n");
							break;
						}
						else
						{
							//��������Ѱ��
							current = current->next;
							if(current == next_rotation)         //����һ�η���ĵط����Ҳ��� ˵���޷�����
							{
								printf("û����ô��Ŀ飡\n\n");
								break ;
							}
						}
					}
				}
			}
			break;
		case 2:
			recycle();
			break;
		case 3:
			print_mem();
			break;
		default:
			printf("Input Error!\n");
			break;
		}
		choose = welcome2();
	}
}

/*
�����Ӧ�㷨Ҫ��δ����ռ䰴��С�����˳�����У�
�������Ӵ����Ѷȣ��ʶ��Բ��ð���ַ���������
*/
//�����Ӧ
void best_adapt()
{
	init();
	int choose = welcome2();
	while(true)
	{
		switch(choose)
		{
		case 0:
			clear();
			return ;
		case 1:
			{
				int id = 0;
				int len = 0;
				printf("������ҵ��(����������):");
				scanf("%d", &id);
				struct block *current = allocated->next;
				bool can_in = true;   //������ҵ���Ƿ��ظ�
				while(current != NULL)
				{
					if(current->id == id)
					{
						can_in = false;
						break;
					}
					current = current->next;
				}
				if(!can_in)
				{
					printf("�����id�ظ���\n\n");
				}
				else
				{
					printf("������ҵ���賤��xk:");
					scanf("%d", &len);
					current = blank->next;
					//���÷���Ŀ����ϸ��Ϣ
					struct block * p = (struct block *)malloc(sizeof(struct block));
					p->id = id;
					p->len = len;
					p->last = NULL;
					p->next = NULL;
					if(current == NULL)
					{
						printf("�ڴ��ѱ��Ϸ���ϣ�\n\n");
						break ;
					}
					struct block * min = blank->next;
					while(min != NULL)
					{
						if(min->len >= len)
						{
							break;
						}
						if(min == NULL)
						{
							printf("û����ô��Ŀ飡\n\n");
							break;
						}
						min = min->next;
					}
					if(min == NULL)
					{
						break;
					}
					current = min;
					while(current != NULL)
					{
						if(current->len == len)		//��ǰ��պù�����
						{
							//���з���
							p->start = current->start;
							current->last->next = current->next;
							if(current ->next != NULL)
							{
								current->next->last = current->last;
							}

							free(current);
							//���뵽�������
							struct block *a_current = allocated;
							while(a_current->next != NULL)
							{
								a_current = a_current->next;
							}
							a_current->next = p;
							p->last = a_current;
							printf("\n");
							break;
						}
						else
						{
							//��������Ѱ��
							current = current->next;
							if(current != NULL && current->len >= len && current->len < min->len)
							{
								min = current;
                                continue;
							}
							if(current == NULL)
							{
								//��ʼ���䲢�޸ĵ�ǰδ�������������Ϣ
								p->start = min->start + min->len -len ;
								min->len -= len;
								//���뵽�ѷ������
								struct block *current = allocated;
								while(current->next != NULL)
								{
									current = current->next;
								}
								current->next = p;
								p->last = current;
								printf("\n");
								break;
							}
						}
					}
				}
			}
			break;
		case 2:
			recycle();
			break;
		case 3:
			print_mem();
			break;
		default:
			printf("Input Error!\n");
			break;
		}
		choose = welcome2();
	}

}

int main(void)
{
	int choose = welcome1();
	while(true)
	{
		switch(choose)
		{
		case 0:
			printf("ллʹ��~\n");
			return 0;
		case 1:
			first_adapt();
			break;
		case 2:
			rotation_first_adapt();
			break;
		case 3:
			best_adapt();
			break;
		default :
			printf("Error input!!!\n");
			break;
		}
		choose = welcome1();
	}
	return 0;
}
