
#include "functions.h"

PClient P_Head_Client;		//用户链表
PClient P_Now_Client;

POrder P_Head_Order;		//以时间排序的订单
POrder P_Now_Order;

PRoom P_Head_Room;		//房间链表
PRoom P_Now_Room;

MOUSEMSG M_msg;

void Init()			//程序初始化
{
	initgraph(SCREEN_W, SCREEN_H);	//窗口大小

	setbkcolor(RGB(50, 50, 50));	//背景颜色
	cleardevice();

	setbkmode(TRANSPARENT);			//设置背景为透明

	P_Head_Client = NULL;		//用户链表
	P_Now_Client = NULL;

	P_Head_Order = NULL;		//以时间排序的订单
	P_Now_Order = NULL;

	P_Head_Room = NULL;
	P_Now_Room = NULL;
}

void Run_MainMenu()		//主界面
{
	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 75;
		wcscpy_s(t.lfFaceName, L"微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(310, 70, L"主菜单");

		if (Button(350, 200, L"我是管理员"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminLoginMenu();
			return;
		}

		if (Button(360, 300, L"我是用户"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientLoginMenu();
			return;
		}

		if (Button(360, 400, L"点击退出"))
		{
			break;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Exit()			//退出程序
{
	EndBatchDraw();
	closegraph();
}

bool Button(int a, int b, const wchar_t str[])			//按钮模组
{
	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30)		//判断高亮显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);

		if (M_msg.uMsg == WM_LBUTTONUP)		//检测鼠标点击
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//绘制文字
	gettextstyle(&t);
	t.lfHeight = 25;
	wcscpy_s(t.lfFaceName, L"微软雅黑 Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return false;
}

void test()
{
	PText s = (PText)malloc(sizeof(Text));
	bool Is_Input = false;
	wchar_t key = 0;

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		if (Is_Input)
		{
			key = Input_Text();
			if (key != 0)
			{
				if (key != 13)
				{
					Append_Text(s, key);
				}
				else
				{
					Empty_Text(s);
					Is_Input = false;
					key = 0;
				}
			}
		}

		cleardevice();
		Draw_Text(s);

		if (Is_Input == false && Button(200, 200, L"点击输入"))
		{
			Init_text(s, 200, 300, 200, 230, 200);

			Is_Input = true;
		}

		if (Button(400, 200, L"点击退出"))
		{
			break;
		}

		FlushBatchDraw();
		Sleep(10);
	}
}