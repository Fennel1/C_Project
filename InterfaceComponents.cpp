
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表

extern POrder P_Head_Order;		//以时间排序的订单

extern PRoom P_Head_Room;

bool Button(int a, int b, const char str[])			//基本按钮模组
{
	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 15 && (size_t)x < a + 9 * strlen(str) + 20 && y > b && y < b + 30)		//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return false;
}

bool Button(int a, int b, const char str[], bool choose)			//基本按钮模组
{
	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (choose == true)
	{
		setfillcolor(RGB(30, 30, 30));
		solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);
	}

	if ((x > a - 15 && (size_t)x < a + 9 * strlen(str) + 20 && y > b && y < b + 30))		//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return false;
}

bool Button_Order(int a, int b, POrder order)			//订单模组
{
	static int x, y;

	char str1[100];
	char str2[100];
	sprintf(str1, "ID：%s                                           评价：%d★", order->order_id, order->remark.star);
	sprintf(str2, "入住时间：%d年%2d月%2d日        退房时间：%d年%2d月%2d日", order->start.year, order->start.month, order->start.day, order->end.year, order->end.month, order->end.day);

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 15, b, a + 600, b + 75);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 15 && (size_t)x < a + 600 && y > b && y < b + 75)		//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 600, b + 75);

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str1);
	outtextxy(a, b + 35, str2);

	return false;
}

bool Button_Remark(int a, int b, POrder order)			//订单模组
{
	static int x, y;

	char str1[100];
	char str2[100];
	sprintf(str1, "评价：%d★", order->remark.star);
	sprintf(str2, "留言：%-50s", order->remark.message);
	

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 15, b, a + 600, b + 75);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 15 && (size_t)x < a + 600 && y > b && y < b + 75)		//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 600, b + 75);

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str1);
	outtextxy(a, b + 35, str2);

	return false;
}

bool Button_Client(int a, int b, PClient client)			//用户模组
{
	static int x, y;

	char str1[100];
	char str2[100];
	if (client->gender == true) {
		sprintf(str1, "身份证号：%s                                 %s先生", client->id, client->name);
	}
	else {
		sprintf(str1, "身份证号：%s                                 %s女士", client->id, client->name);
	}
	sprintf(str2, "电话号码：%s                    VIP等级：%d", client->phone, client->VIP);

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 15, b, a + 600, b + 75);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 15 && (size_t)x < a + 600 && y > b && y < b + 75)		//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 600, b + 75);

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str1);
	outtextxy(a, b + 35, str2);

	return false;
}

bool Button_Room(int a, int b, PRoom room)			//基本按钮模组
{
	static int x, y;

	char str1[100];

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 15, b, a + 100, b + 75);

	x = M_msg.x;
	y = M_msg.y;

	sprintf(str1, "%s", room->id);

	if (x > a - 15 && (size_t)x < a + 100 && y > b && y < b + 75)		//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 100, b + 75);

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a + 15, b + 25, str1);

	return false;

}

bool Button_Delete_Order(int a, int b, POrder order)			//基本按钮模组
{
	static int x, y;

	char str1[100];
	char str2[100];
	char str3[100] = "删除";
	sprintf(str1, "ID：%s                                           评价：%d★", order->order_id, order->remark.star);
	sprintf(str2, "入住时间：%d年%2d月%2d日        退房时间：%d年%2d月%2d日", order->start.year, order->start.month, order->start.day, order->end.year, order->end.month, order->end.day);

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 15, b, a + 550, b + 75);
	solidrectangle(a + 555, b, a + 630, b + 75);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a + 555 && (size_t)x < a + 630 && y > b && y < b + 75)		//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a + 555, b, a + 630, b + 75);

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str1);
	outtextxy(a, b + 35, str2);
	outtextxy(a + 573, b + 25, str3);

	return false;
}

bool Button_Input(int a, int b, const char str[])			//输入按钮模组
{
	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 15 && (size_t)x < a + 9 * strlen(str) + 170 && y > b && y < b + 30)		//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

		if (M_msg.uMsg == WM_LBUTTONUP && x > a - 15 && (size_t)x < a + 9 * strlen(str) + 170 && y > b && y < b + 30)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return false;
}

bool Check_Time(int s_year, int s_month, int s_day, int e_year, int e_month, int e_day)
{
	if (s_year > e_year)	return false;
	else if (s_year == e_year && s_month > e_month)	return false;
	else if (s_year == e_year && s_month == e_month && s_day > e_day)	return false;
	else	return true;
}

void Draw_Calendar(int year, int month, PClient client)
{	
	time_t timep;			//获取系统时间
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);

	int now_year = 1900 + p->tm_year, now_month = 1 + p->tm_mon, now_day = p->tm_mday;

	int LeapYear[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int NoLeapYear[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int days = 0;

	if (month == 1 || month == 2) 
	{
		month += 12;
		year--;
	}

	bool flag = false;
	int weekday = (1 + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	int x = 205, y = 200;
	int cnt = 0;

	if (month == 13 || month == 14)
	{
		month -= 12;
		year++;
	}

	for (int week = 0; week <= 5; week++) {
		for (int day = 0; day <= 6; day++) {
			if (day == weekday) {
				flag = true;
			}
			if (flag)
			{
				cnt++;
				days++;
				if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
				{
					if (cnt == LeapYear[month]+1) {
						return;
					}
					if (Button_Calendar(x + day * 60, y + week * 60, days % (LeapYear[month] + 1)))
					{
						FlushBatchDraw();
						cleardevice();
						if (Check_Time(now_year, now_month, now_day, year, month, days)) {
							ReCommit_Order(client, year, month, days);
						}
						else {
							char title[] = "提交错误";
							char text[1][50];
							sprintf(text[0], "入住时间应在%d年%d月%d日之后", now_year, now_month, now_day);
							Popup_Window(250, 200, 300, 200, title, text, 1, 1);
							Commit_Order(client);
						}
						return;
					}
				}
				else
				{
					if (cnt == NoLeapYear[month]+1) {
						return;
					}
					if (Button_Calendar(x + day * 60, y + week * 60, days % (NoLeapYear[month] + 1)))
					{
						FlushBatchDraw();
						cleardevice();
						if (Check_Time(now_year, now_month, now_day, year, month, days)) {
							ReCommit_Order(client, year, month, days);
						}
						else {
							char title[] = "提交错误";
							char text[1][50];
							sprintf(text[0], "入住时间应在%d年%d月%d日之后", now_year, now_month, now_day);
							Popup_Window(250, 200, 300, 200, title, text, 1, 1);
							Commit_Order(client);
						}
						return;
					}
				}
			}
		}
	}
}

void reDraw_Calendar(int year, int month, int s_year, int s_month, int s_day, PClient client)
{

	int LeapYear[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int NoLeapYear[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int days = 0;

	if (month == 1 || month == 2)
	{
		month += 12;
		year--;
	}

	bool flag = false;
	int weekday = (1 + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	int x = 205, y = 200;
	int cnt = 0;

	if (month == 13 || month == 14)
	{
		month -= 12;
		year++;
	}

	for (int week = 0; week <= 5; week++) {
		for (int day = 0; day <= 6; day++) {
			if (day == weekday) {
				flag = true;
			}
			if (flag)
			{
				cnt++;
				days++;
				if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
				{
					if (cnt == LeapYear[month] + 1) {
						return;
					}
					if (year == s_year && month == s_month && days == s_day) 
					{
						setlinecolor(RGB(0, 255, 0));
						rectangle(x + day * 60 - 5, y + week * 60 - 5, x + day * 60 + 55, y + week * 60 + 55);
					}
					if (Button_Calendar(x + day * 60, y + week * 60, days % (LeapYear[month] + 1)))
					{
						if (Check_Time(s_year, s_month, s_day, year, month, days)) {
							char title[] = "确认当前日期吗？";
							char text[2][50];
							sprintf(text[0], "入住时间：%d年%d月%d日", s_year, s_month, s_day);
							sprintf(text[1], "退房时间：%d年%d月%d日", year, month, days);
							if (Popup_Window(250, 200, 300, 200, title, text, 2, 2))
							{
								Time start = { s_year, s_month, s_day, 0, 0 };
								Time end = { year, month, days, 0, 0 };
								int num[4] = { 0 };
								int* rooms_num = num;
								rooms_num = Display_rooms_number(num, start, end);
								FlushBatchDraw();
								cleardevice();
								Choose_room(client, rooms_num, start, end);
							}
							else
							{
								FlushBatchDraw();
								cleardevice();
								Commit_Order(client);
							}
						}
						else {
							char title[] = "提交错误";
							char text[1][50];
							sprintf(text[0], "退房时间应在%d年%d月%d日之后", s_year, s_month, s_day);
							Popup_Window(250, 200, 300, 200, title, text, 1, 1);
							Commit_Order(client);
						}
					}
				}
				else
				{
					if (cnt == NoLeapYear[month] + 1) {
						return;
					}
					if (year == s_year && month == s_month && days == s_day)
					{
						setlinecolor(RGB(0, 255, 0));
						rectangle(x + day * 60 - 5, y + week * 60 - 5, x + day * 60 + 55, y + week * 60 + 55);
					}
					if (Button_Calendar(x + day * 60, y + week * 60, days % (NoLeapYear[month] + 1)))
					{
						if (Check_Time(s_year, s_month, s_day, year, month, days)) {
							char title[] = "确认当前日期吗？";
							char text[2][50];
							sprintf(text[0], "入住时间：%d年%d月%d日", s_year, s_month, s_day);
							sprintf(text[1], "退房时间：%d年%d月%d日", year, month, days);
							if (Popup_Window(250, 200, 300, 200, title, text, 2, 2))
							{
								Time start = { s_year, s_month, s_day, 0, 0 };
								Time end = { year, month, days, 0, 0 };
								int num[4] = { 0 };
								int* rooms_num = num;
								rooms_num = Display_rooms_number(num, start, end);
								FlushBatchDraw();
								cleardevice();
								Choose_room(client, rooms_num, start, end);
							}
							else
							{
								FlushBatchDraw();
								cleardevice();
								Commit_Order(client);
							}
						}
						else {
							char title[] = "提交错误";
							char text[1][50];
							sprintf(text[0], " 退房时间应在%d年%d月%d日之后", s_year, s_month, s_day);
							Popup_Window(250, 200, 300, 200, title, text, 1, 1);
							Commit_Order(client);
						}
					}
				}
			}
		}
	}
}

bool Button_Calendar(int a, int b, int day)			//日历模组
{
	char days[][5] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15",
					"16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31" };

	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a, b, a + 49, b + 49);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a && x < a + 49 && y > b && y < b + 49)	//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a, b, a + 49, b + 49);

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 20;
	strcpy(t.lfFaceName, "微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	if (day < 10) {
		outtextxy(a + 20, b + 14, days[day]);
	}
	else {
		outtextxy(a + 17, b + 14, days[day]);
	}

	return false;
}

bool Button_Star(int a, int b, int *num, int n, int star)
{
	static int x, y;

	x = M_msg.x;
	y = M_msg.y;
	if (star >= n)
	{
		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 45;
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(a, b, "★");

	}

	if (*num > n)
	{
		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 45;
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(a, b, "★");

	}
	else if (x > a - 15 && x < a + 30 && y > b && y < b + 30)		//判断高亮显示
	{
		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 45;
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(a, b, "★");

		*num = n;

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}
	else
	{
		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 45;
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(a, b, "☆");

		if (*num == n) {
			*num = 0;
		}
	}
	return false;
}

int Popup_Window(int x, int y, int wight, int hight, char title[], char text[][50], int g_num, int var)
{
	setbkmode(TRANSPARENT);

	char c;

	while (true)
	{
		if (_kbhit())									//键盘消息清空
			c = _getch();

		while (MouseHit())
			M_msg = GetMouseMsg();						//鼠标消息获取

		setfillcolor(RGB(25, 25, 25));
		solidrectangle(x, y, x + wight, y + hight);		//绘制边框

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 30;
		strcpy(f.lfFaceName, "黑体");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		outtextxy(x + 20, y + 10, title);

		for (int i = 0; i < g_num; i++)				//输出内容
		{
			f.lfHeight = 18;
			f.lfQuality = ANTIALIASED_QUALITY;
			settextstyle(&f);
			outtextxy(x + 20, y + 45 + i * 20, text[i]);
		}

		if (var == 1)							//按钮放置
		{
			if (Button(x + wight - 70, y + hight - 37, "确定"))
				return 1;
		}
		else if (var == 2)
		{
			if (Button(x + wight - 125, y + hight - 37, "是"))
				return 1;

			if (Button(x + wight - 50, y + hight - 37, "否"))
				return 0;
		}

		FlushBatchDraw();
	}
	return 0;
}

int Popup_Window_Room(int x, int y, int wight, int hight, char title[], char text[][50], int g_num, int var)
{
	setbkmode(TRANSPARENT);

	char c;

	while (true)
	{
		if (_kbhit())									//键盘消息清空
			c = _getch();

		while (MouseHit())
			M_msg = GetMouseMsg();						//鼠标消息获取

		setfillcolor(RGB(25, 25, 25));
		solidrectangle(x, y, x + wight, y + hight);		//绘制边框

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 30;
		strcpy(f.lfFaceName, "黑体");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		outtextxy(x + 20, y + 10, title);

		for (int i = 0; i < g_num; i++)				//输出内容
		{
			f.lfHeight = 18;
			f.lfQuality = ANTIALIASED_QUALITY;
			settextstyle(&f);
			outtextxy(x + 20, y + 45 + i * 20, text[i]);
		}

		if (var == 1)							//按钮放置
		{
			if (Button(x + wight - 70, y + hight - 37, "确定"))
				return 1;
		}
		else if (var == 2)
		{
			if (Button(x + wight - 200, y + hight - 37, "删除该房间"))
				return 1;

			if (Button(x + wight - 70, y + hight - 37, "返回"))
				return 0;
		}

		FlushBatchDraw();
	}
	return 0;
}