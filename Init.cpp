
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//以时间排序的订单
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;

void Init()			//程序初始化
{
	initgraph(SCREEN_W, SCREEN_H);	//窗口大小

	setbkcolor(RGB(50, 50, 50));	//背景颜色
	cleardevice();

	setbkmode(TRANSPARENT);			//设置背景为透明

	Room_Init();
	Client_Init();
	Order_Init();

}

void Exit()			//退出程序
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
		printf("打开文件失败");
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

PRoom Room_Init()//目前只能读取房间id
{
	char temp_id[10];

	Room* P_Head_Room = (Room*)malloc(sizeof(Room));//头节点
	Room* P_Now_Room = P_Head_Room;
	Room* P_Temp_Room = P_Head_Room;
	FILE* r = fopen("room_data.txt", "r");
	if (r == NULL)
	{
		printf("打开文件失败");
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