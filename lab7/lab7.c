#include<stdio.h>
#include<stdlib.h>

const int N =64;
int page_count = 0;		//������ҳ��
int block_count = 0;	//�������ڴ��е��ܿ���
int p[N];				//�����
struct Page
{
    int lNumber;	//ҳ��
    int pNumber;	//������
    int dNumber;	//�ڴ����ϵ�λ�� 
    int write;		//�޸ı�־
    int flag;		//���ڱ�־
}page[N];
void print()
{
	printf("page\tlNumber\tpNumber\twrite\tflag\n");
	for(int i = 0; i < page_count; i ++)
	{
		printf("%d\t", page[i].lNumber);
		printf("%d\t", page[i].pNumber);
		printf("%d\t",page[i].dNumber);
		printf("%d\t", page[i].write);
		printf("%d\n", page[i].flag);
	}
	printf("\n");
}
void exch_page(int virtual_page_number)
{
	int out_page = p[0];
	int i = 0;
	while(i < block_count -1)
	{
		p[i] = p[i + 1];
		i ++;
	}
	p[block_count - 1] = virtual_page_number;
	page[virtual_page_number].pNumber = page[out_page].pNumber;
	page[out_page].flag = 0;
	page[virtual_page_number].flag = 1;
	printf("��̭����%d�е�ҳ%d���Ӵ���%d����ҳ%d.\n",page[out_page].pNumber, out_page, page[virtual_page_number].dNumber,virtual_page_number);
	page[out_page].pNumber = -1;
	if(page[out_page].write == 1)
	{
		printf("ҳ��%d����д����д�ش��̳ɹ���\n", out_page);
	}
	else
	{
		printf("ҳ��%dδ����д��������д�ش��̣�\n", out_page);
	}
}

void find(int choice, int address)
{
	int virtual_page_number = address>>10;
	int block_inner_add = address & 0x03FF;
	if(virtual_page_number >= page_count)
	{
		printf("��ҳ�����ڣ�����\n\n");
		return ;
	}
	if(page[virtual_page_number].flag == 0)
	{
		printf("����ȱҳ�жϣ�����\n\n");
		exch_page(virtual_page_number);
		find(choice, address);
	}
	else
	{
		int phy_page_number = page[virtual_page_number].pNumber;
		int phy_address = (phy_page_number<<10)|block_inner_add;
		printf("�߼���ַ�ǣ�%d��Ӧ�������ַΪ��%d\n\n", address, phy_address);
		if(choice == 1)
		{
			page[virtual_page_number].write = 1;
		}
		print();
	}
}

int main(void)
{
    for(int i = 0; i < N; i ++)
    {
        page[i].lNumber = 0;
        page[i].pNumber = -1;
        page[i].dNumber = 0;
        page[i].write = 0;
        page[i].flag = 0;
    }
    printf("����ҳ����Ϣ������ҳ��(��-1����)��\n\n");

    while(true)
    {
        printf("������� %d ҳ�����ַ:", page_count);
        int disk_add = -1;
        scanf("%d", &disk_add);
        if(disk_add == -1)
        {
            break;
        }
        page[page_count].lNumber = page_count;
        page[page_count].dNumber = disk_add;
        page_count ++;
    }
	print();

	printf("����������ÿһҳ������ţ���-1��������");
	
	int i = 0;
	for(i = 0; i < page_count; i ++)
	{
		int pNumber = 0;
		scanf("%d", &pNumber);
		if(pNumber == -1)
		{
			break;
		}
		else
		{
			page[i].pNumber = pNumber;
			page[i].flag = 1;
			p[i] = i;
		}
	}
	block_count = i;
	print();

	printf("����ָ��(1-�޸ģ�0-���޸ģ�����-�������)���߼���ַ��");
	int choice = 0 ,address = 0;
	while(scanf("%d%d", &choice, &address) && (choice == 0 || choice == 1))
	{
		find(choice, address);
		printf("����ָ��(1-�޸ģ�0-���޸ģ�����-�������)���߼���ַ��");
	}
    return 0;
}


