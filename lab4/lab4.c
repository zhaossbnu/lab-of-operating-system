#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<stdlib.h>

const int MSGKEY = 75;
struct msgform					
{
	long mtype;
	char mtext[1024];
}msg;
int msgqid;

cleanup()
{
	msgctl(msgqid,IPC_RMID,0);
	exit(0);
}

void client()
{
	int i = 10;
	msgqid = msgget(MSGKEY, 0777);
	
	for(i =10; i >= 1; i --)
	{
		msg.mtype = i;
		msgsnd(msgqid, &msg, 1032, 0);
		printf("(Client)sent:%d\n", i);
		
		sleep(1);

		msgrcv(msgqid, &msg ,1032, 100, 0);
		printf("(Client)sure\n");

	}
	//exit(0);
}

void server()
{
	msgqid = msgget(MSGKEY, 0777|IPC_CREAT);
	
	int i = 10;
	for(;;)
	{
		msgrcv(msgqid, &msg, 1032, i, 0);
		printf("(Server)received:%d\n", msg.mtype);
		long temp = msg.mtype;
		
		sleep(1);
		
		msg.mtype = 100;
		msgsnd(msgqid, &msg ,1032,0);
		printf("(Server)return\n");
				 
		if(temp == 1)
			break;
		i --;
	}	
	//exit(0);
}

int main(void)
{
	int  Server, Client;
	Client = fork();
	if(!Client)
	{
		client();		
	}
	else
	{
		Server = fork();
		if(!Server)
		{
			server();
		}
	}
	msgctl(msgqid,IPC_RMID,0);
	wait(0);
	wait(0);
	return 0;
}
