#include<stdio.h>
#include<stdlib.h>

const int N =64;
int page_count = 0;		//进程总页数
int block_count = 0;	//进程在内存中的总块数
int p[N];				//块队列
struct Page
{
    int lNumber;	//页号
    int pNumber;	//物理块号
    int dNumber;	//在磁盘上的位置 
    int write;		//修改标志
    int flag;		//存在标志
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
	printf("淘汰主存%d中的页%d，从磁盘%d调入页%d.\n",page[out_page].pNumber, out_page, page[virtual_page_number].dNumber,virtual_page_number);
	page[out_page].pNumber = -1;
	if(page[out_page].write == 1)
	{
		printf("页面%d被改写过，写回磁盘成功！\n", out_page);
	}
	else
	{
		printf("页面%d未被改写过，不用写回磁盘！\n", out_page);
	}
}

void find(int choice, int address)
{
	int virtual_page_number = address>>10;
	int block_inner_add = address & 0x03FF;
	if(virtual_page_number >= page_count)
	{
		printf("该页不存在！！！\n\n");
		return ;
	}
	if(page[virtual_page_number].flag == 0)
	{
		printf("发生缺页中断！！！\n\n");
		exch_page(virtual_page_number);
		find(choice, address);
	}
	else
	{
		int phy_page_number = page[virtual_page_number].pNumber;
		int phy_address = (phy_page_number<<10)|block_inner_add;
		printf("逻辑地址是：%d对应的物理地址为：%d\n\n", address, phy_address);
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
    printf("输入页表信息，创建页表(以-1结束)：\n\n");

    while(true)
    {
        printf("请输入第 %d 页辅存地址:", page_count);
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

	printf("请依次输入每一页的主块号（以-1结束）：");
	
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

	printf("输入指令(1-修改，0-不修改，其他-程序结束)和逻辑地址：");
	int choice = 0 ,address = 0;
	while(scanf("%d%d", &choice, &address) && (choice == 0 || choice == 1))
	{
		find(choice, address);
		printf("输入指令(1-修改，0-不修改，其他-程序结束)和逻辑地址：");
	}
    return 0;
}


