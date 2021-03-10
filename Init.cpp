
#include "functions.h"

extern MOUSEMSG M_msg;				// �����Ϣ\

extern PClient P_Head_Client;		//�û�����
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//��ʱ������Ķ���
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;

void Init()			//�����ʼ��
{
	initgraph(SCREEN_W, SCREEN_H);	//���ڴ�С

	setbkcolor(RGB(50, 50, 50));	//������ɫ
	cleardevice();

	setbkmode(TRANSPARENT);			//���ñ���Ϊ͸��

	Room_Init();
	Client_Init();
	Order_Init();

}

void Exit()			//�˳�����
{
	EndBatchDraw();
	closegraph();
}

void out_Room(Room* head)
{
	Room* p = head->next;
	FILE* w = fopen("room_data.txt", "w");
	if (w == NULL)
	{
		printf("���ļ�ʧ��");
		return;
	}
	while (p)
	{
		fprintf(w, "%s ", p->id);
	}
	fprintf(w, "\n");
	fclose(w);
	return;
}

PRoom Room_Init()//Ŀǰֻ�ܶ�ȡ����id
{
	char temp_id[10];

	Room* P_Head_Room = (Room*)malloc(sizeof(Room));//ͷ�ڵ�
	Room* P_Now_Room = P_Head_Room;
	Room* P_Temp_Room = P_Head_Room;
	FILE* r = fopen("room_data.txt", "r");
	if (r == NULL)
	{
		printf("���ļ�ʧ��");
		return NULL;
	}
	while (fscanf(r, "%s", temp_id) != EOF)
	{
		P_Now_Room = (Room*)malloc(sizeof(Room));
		strcpy(P_Now_Room->id, temp_id);
		P_Temp_Room->next = P_Now_Room;
		P_Temp_Room = P_Now_Room;
	}
	P_Now_Room->next = NULL;
	return P_Head_Room;
}

PClient Client_Init()
{

}

POrder Order_Init()
{

}