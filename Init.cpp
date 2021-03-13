
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

PRoom P_Head_Room;
PClient P_Head_Client;
POrder P_Head_Order;

void Init()			//程序初始化
{
	initgraph(SCREEN_W, SCREEN_H);	//窗口大小

	setbkcolor(RGB(50, 50, 50));	//背景颜色
	cleardevice();

	setbkmode(TRANSPARENT);			//设置背景为透明

	P_Head_Room = Room_Init();
	P_Head_Client = Client_Init();
	P_Head_Order = Order_Init();

}

void Exit()			//退出程序
{
	EndBatchDraw();
	closegraph();
	exit(0);
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
	P_Head_Room = (Room*)malloc(sizeof(Room));//头节点
	P_Head_Room->next = NULL;
	PRoom P_Now_Room = P_Head_Room;
	FILE* r = fopen("room.txt", "r");
	if (r == NULL)
	{
		printf("打开文件失败");
		return NULL;
	}
	PRoom P_Temp_Room = (Room*)malloc(sizeof(Room));
	while (fscanf(r, "%s %d %d %lf %lf %d %d %d %d %d %d %d %d %d %d", temp_id,&temp_Is_Use,&temp_type,&temp_price,&temp_discount,&temp_start.year,&temp_start.month,&temp_start.day,&temp_start.weekday,&temp_start.hour, &temp_end.year, &temp_end.month, &temp_end.day, &temp_end.weekday, &temp_end.hour) != EOF)
	{
		
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
		P_Temp_Room = (Room*)malloc(sizeof(Room));
	}
	return P_Head_Room;
}

PClient Client_Init()
{
	//创建读入所需的临时变量
	char temp_id[20];
	char temp_password[30];
	char temp_name[30];
	char temp_phone[15];
	int temp_gender;
	int temp_VIP;
	int temp_num_bill;
	int temp_pay;
	//创建链表
	P_Head_Client = (Client*)malloc(sizeof(Client));//头节点
	P_Head_Client->next = NULL;
	Client* P_Now_Client = P_Head_Client;
	
	FILE* r = fopen("client.txt", "r");
	if (r == NULL)
	{
		printf("打开文件失败");
		return NULL;
	}

	Client* P_Temp_Client = (Client*)malloc(sizeof(Client));
	while (fscanf(r, "%s %s %s %s %d %d %d %d", temp_id, temp_password, temp_name, temp_phone,&temp_gender,&temp_VIP,&temp_num_bill,&temp_pay) != EOF)
	{
		strcpy(P_Temp_Client->id, temp_id);
		strcpy(P_Temp_Client->password, temp_password);
		strcpy(P_Temp_Client->name, temp_name);
		strcpy(P_Temp_Client->phone, temp_phone);
		P_Temp_Client->gender = temp_gender;
		P_Temp_Client->VIP = temp_VIP;
		P_Temp_Client->num_bill = temp_num_bill;
		P_Temp_Client->pay = temp_pay;
		P_Temp_Client->head_order = NULL;
		//进入下一个节点
		P_Temp_Client->next = NULL;
		P_Now_Client->next = P_Temp_Client;
		P_Now_Client = P_Temp_Client;
		P_Temp_Client = (Client*)malloc(sizeof(Client));
	}
	return P_Head_Client;
}

POrder Order_Init()
{
	//创建读入所需的临时变量
	char temp_client_id[20];
	char temp_order_id[10];
	char temp_room_id[10];
	Room_Type temp_type;
	double temp_price;
	Time temp_start, temp_end;
	Remark temp_remark;
	//创建链表
	P_Head_Order = (Order*)malloc(sizeof(Order));//头节点
	P_Head_Order->next = NULL;
	POrder P_Now_Order = P_Head_Order;
	FILE* r = fopen("order.txt", "r");
	if (r == NULL)
	{
		printf("打开文件失败");
		return NULL;
	}
	POrder P_Temp_Order = (Order*)malloc(sizeof(Order));
	while (fscanf(r, "%s %s %s %d %lf %d %d %d %d %d %d %d %d %d %d %s %d",temp_client_id, temp_order_id, temp_room_id,&temp_type,&temp_price, &temp_start.year, &temp_start.month, &temp_start.day, &temp_start.weekday, &temp_start.hour, &temp_end.year, &temp_end.month, &temp_end.day, &temp_end.weekday, &temp_end.hour,temp_remark.message,&temp_remark.star) != EOF)
	{
		strcpy(P_Temp_Order->client_id, temp_client_id);
		strcpy(P_Temp_Order->order_id, temp_order_id);
		strcpy(P_Temp_Order->room_id, temp_room_id);
		P_Temp_Order->type = temp_type;
		P_Temp_Order->price = temp_price;
		P_Temp_Order->start.year = temp_start.year;
		P_Temp_Order->start.month = temp_start.month;
		P_Temp_Order->start.day = temp_start.day;
		P_Temp_Order->start.weekday = temp_start.weekday;
		P_Temp_Order->start.hour = temp_start.hour;
		P_Temp_Order->end.year = temp_end.year;
		P_Temp_Order->end.month = temp_end.month;
		P_Temp_Order->end.day = temp_end.day;
		P_Temp_Order->end.weekday = temp_end.weekday;
		P_Temp_Order->end.hour = temp_end.hour;
		strcpy(P_Temp_Order->remark.message, temp_remark.message);
		P_Temp_Order->remark.star = temp_remark.star;
		//进入下一个节点
		P_Temp_Order->next = NULL;
		P_Now_Order->next = P_Temp_Order;
		P_Now_Order = P_Temp_Order;
		P_Temp_Order = (Order*)malloc(sizeof(Order));
	}
	return P_Head_Order;
}

POrder Client_Order_Init(PClient client)
{
	//创建读入所需的临时变量
	char temp_client_id[20];
	char temp_order_id[10];
	char temp_room_id[10];
	Room_Type temp_type;
	double temp_price;
	Time temp_start, temp_end;
	Remark temp_remark;
	//创建链表
	P_Head_Order = (Order*)malloc(sizeof(Order));//头节点
	Order* P_Now_Order = P_Head_Order;
	Order* P_Temp_Order = P_Head_Order;
	FILE* r = fopen("order.txt", "r");
	if (r == NULL)
	{
		printf("打开文件失败");
		return NULL;
	}
	while (fscanf(r, "%s %s %s %d %lf %d %d %d %d %d %d %d %d %d %d %s %d", temp_client_id, temp_order_id, temp_room_id, &temp_type, &temp_price, &temp_start.year, &temp_start.month, &temp_start.day, &temp_start.weekday, &temp_start.hour, &temp_end.year, &temp_end.month, &temp_end.day, &temp_end.weekday, &temp_end.hour, temp_remark.message, &temp_remark.star) != EOF)
	{
		strcpy(P_Temp_Order->client_id, temp_client_id);
		strcpy(P_Temp_Order->order_id, temp_order_id);
		strcpy(P_Temp_Order->room_id, temp_room_id);
		P_Temp_Order->type = temp_type;
		P_Temp_Order->price = temp_price;
		P_Temp_Order->start.year = temp_start.year;
		P_Temp_Order->start.month = temp_start.month;
		P_Temp_Order->start.day = temp_start.day;
		P_Temp_Order->start.weekday = temp_start.weekday;
		P_Temp_Order->start.hour = temp_start.hour;
		P_Temp_Order->end.year = temp_end.year;
		P_Temp_Order->end.month = temp_end.month;
		P_Temp_Order->end.day = temp_end.day;
		P_Temp_Order->end.weekday = temp_end.weekday;
		P_Temp_Order->end.hour = temp_end.hour;
		strcpy(P_Temp_Order->remark.message, temp_remark.message);
		P_Temp_Order->remark.star = temp_remark.star;
		//进入下一个节点
		P_Temp_Order->next = NULL;
		P_Now_Order->next = P_Temp_Order;
		P_Now_Order = P_Temp_Order;
	}
	P_Now_Order->next = NULL;
	return P_Head_Order;
}