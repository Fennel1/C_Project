
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
	P_Head_Client = (PClient)malloc(sizeof(Client));
	P_Head_Client->next = NULL;
	P_Now_Client = P_Head_Client;
	
	//Client_Init();
	//Order_Init();

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

PRoom Room_Init()
{
	//���������������ʱ����
	char temp_id[10];
	int temp_Is_Use;
	Room_Type temp_type;
	double temp_price;
	double temp_discount;
	PClient temp_client;
	Time temp_start, temp_end;
	//��������
	Room* P_Head_Room = (Room*)malloc(sizeof(Room));//ͷ�ڵ�
	Room* P_Now_Room = P_Head_Room;
	Room* P_Temp_Room = P_Head_Room;
	FILE* r = fopen("room.txt", "r");
	if (r == NULL)
	{
		printf("���ļ�ʧ��");
		return NULL;
	}
	while (fscanf(r, "%s %d %d %lf %lf %d %d %d %d %d %d %d %d %d %d", temp_id, &temp_Is_Use, &temp_type, &temp_price, &temp_discount, &temp_start.year, &temp_start.month, &temp_start.day, &temp_start.weekday, &temp_start.hour, &temp_end.year, &temp_end.month, &temp_end.day, &temp_end.weekday, &temp_end.hour) != EOF)
	{
		P_Temp_Room = (Room*)malloc(sizeof(Room));
		//����ʱ�����洢��ֵ�Ž�������
		strcpy(P_Temp_Room->id, temp_id);
		P_Temp_Room->Is_Use = temp_Is_Use;
		P_Temp_Room->type = temp_type;
		P_Temp_Room->price = temp_price;
		P_Temp_Room->discount = temp_discount;
		P_Temp_Room->start.year = temp_start.year;
		P_Temp_Room->start.month = temp_start.month;
		P_Temp_Room->start.day = temp_start.day;
		P_Temp_Room->start.weekday = temp_start.weekday;
		P_Temp_Room->start.hour = temp_start.hour;
		P_Temp_Room->end.year = temp_end.year;
		P_Temp_Room->end.month = temp_end.month;
		P_Temp_Room->end.day = temp_end.day;
		P_Temp_Room->end.weekday = temp_end.weekday;
		P_Temp_Room->end.hour = temp_end.hour;
		//������һ���ڵ�
		P_Temp_Room->next = NULL;
		P_Now_Room->next = P_Temp_Room;
		P_Now_Room = P_Temp_Room;
	}
	P_Now_Room->next = NULL;
	return P_Head_Room;
}

/*PClient Client_Init()
{

}

POrder Order_Init()
{

}
*/