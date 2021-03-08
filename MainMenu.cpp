
#include "functions.h"

MOUSEMSG M_msg;				// 鼠标消息\

PClient P_Head_Client;		//用户链表
PClient P_Now_Client;

POrder P_Head_Order;		//以时间排序的订单
POrder P_Now_Order;

PRoom P_Head_Room;
PRoom P_Now_Room;

void Init()
{
	initgraph(SCREEN_W, SCREEN_H);	

	setbkcolor(RGB(50, 50, 50));
	cleardevice();

	setbkmode(TRANSPARENT);

	P_Head_Client = NULL;		//用户链表
	P_Now_Client = NULL;

	P_Head_Order = NULL;		//以时间排序的订单
	P_Now_Order = NULL;

	P_Head_Room = NULL;
	P_Now_Room = NULL;

}

bool Button(int a, int b, const wchar_t str[])
{
	static int x, y;
	
	setfillcolor(RGB(100, 100, 100));				//绘制边框
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 25 && (size_t)x < a + 19  *wcslen(str) + 25 && y > b && y < b + 30)		//判断高亮显示
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
	outtextxy(a, b+3, str);

	return false;
}