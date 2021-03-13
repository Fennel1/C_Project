
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
	P_Head_Client = (PClient)malloc(sizeof(Client));
	P_Head_Client->next = NULL;
	P_Now_Client = P_Head_Client;
	
	//Client_Init();
	//Order_Init();

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

PRoom Room_Init()
{
	//创建读入所需的临时变量
	char temp_id[10];
	int temp_Is_Use;
	Room_Type temp_type;
	double temp_price;
	double temp_discount;
	PClient temp_client;
	Time temp_start, temp_end;
	//创建链表
	Room* P_Head_Room = (Room*)malloc(sizeof(Room));//头节点
	Room* P_Now_Room = P_Head_Room;
	Room* P_Temp_Room = P_Head_Room;
	FILE* r = fopen("room.txt", "r");
	if (r == NULL)
	{
		printf("打开文件失败");
		return NULL;
	}
	while (fscanf(r, "%s %d %d %lf %lf %d %d %d %d %d %d %d %d %d %d", temp_id, &temp_Is_Use, &temp_type, &temp_price, &temp_discount, &temp_start.year, &temp_start.month, &temp_start.day, &temp_start.weekday, &temp_start.hour, &temp_end.year, &temp_end.month, &temp_end.day, &temp_end.weekday, &temp_end.hour) != EOF)
	{
		P_Temp_Room = (Room*)malloc(sizeof(Room));
		//把临时变量存储的值放进链表中
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
		//进入下一个节点
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