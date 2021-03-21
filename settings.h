#pragma once

#include <time.h>		// 时间作为随机生成种子
#include <conio.h>		// 获取键盘信息用
#include <graphics.h>	// 引用图形库头文件
#include <cstring>
#include <cstdio>

const char MANAGER_NAME[20] = "root";         //管理员账户密码
const char MANAGER_PASSWORD[20] = "1";

const int SCREEN_H = 600;
const int SCREEN_W = 800;

const int YEAR = 2021;			//初始年月日星期
const int MONTH = 1;	
const int DAY = 1;
const int WEEKDAY = 5;

enum Room_Type {
	A1, A2, B1, B2		//A为钟点房	B为短租房
};

typedef struct text {			//字符串类型
	int x1, x2, y1, y2;
	char text[500];
	int len;
	int fps;		//光标闪烁频率
}Text, *PText;

typedef struct time {
	int year, month, day;
	int weekday;
	int hour;
}Time;

const Time START_DAY = {2021, 1, 1, 5, 0};

typedef struct reamrk {
	char message[500];
	int star;
}Remark, * PRemark;

typedef struct order {
	char client_id[20];
	char order_id[10];
	char room_id[10];
	Room_Type type;
	double price;
	Time start, end;
	Remark remark;
	struct order* pre;
	struct order* next;
}Order, * POrder;

typedef struct client {
	char id[20];
	char password[30];
	char name[30];
	char phone[15];
	bool gender;		//true为男	false为女
	int VIP;
	int num_bill;
	double pay;
	POrder head_order;
	struct client* next;
}Client, * PClient;

typedef struct room {
	char id[10];
	bool Is_Use;
	Room_Type type;
	double price;
	double discount;
	PClient client;
	Time start, end;
	struct room *next;
}Room, * PRoom;