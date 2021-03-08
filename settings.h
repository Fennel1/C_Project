#pragma once

#include <time.h>		// 时间作为随机生成种子
#include <conio.h>		// 获取键盘信息用
#include <graphics.h>	// 引用图形库头文件

const char MANAGER_NAME[20] = "root";         //管理员账户密码
const char MANAGER_PASSWORD[20] = "1";

const int SCREEN_H = 600;
const int SCREEN_W = 800;

enum Room_Type {
	A1, A2, B1, B2		//A为钟点房	B为短租房
};

typedef struct text {			//字符串类型
	int x1, x2, y1, y2;
	wchar_t text[30];
	int len;
	int fps;		//光标闪烁频率
}Text, *PText;

typedef struct time {
	int year, month, day;
	int hour;
}Time;

typedef struct reamrk {
	wchar_t message[500];
	int star;
}Remark, * PRemark;

typedef struct order {
	wchar_t order_id[10];
	wchar_t room_id[10];
	Room_Type type;
	double price;
	Time start, end;
	PRemark remark;
	struct order *next;
}Order, * POrder;

typedef struct client {
	wchar_t id[20];
	wchar_t password[30];
	wchar_t name[30];
	wchar_t phone[15];
	bool gender;
	int VIP;
	int num_bill;
	int pay;
	POrder head_order;
	struct client* next;

}Client, * PClient;

typedef struct room {
	wchar_t id[10];
	bool Is_Use;
	Room_Type type;
	double price;
	double discount;
	PClient client;
	Time start, end;
	struct room *next;
}Room, * PRoom;

extern PClient P_Head_Client;		//用户链表
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//以时间排序的订单
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;