
#include "functions.h"

extern PClient P_Head_Client;		//用户链表

extern POrder P_Head_Order;		//以时间排序的订单

extern PRoom P_Head_Room;

MOUSEMSG M_msg;

void Run_MainMenu()		//主界面
{
	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		cleardevice();

		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(310, 70, "主菜单");
		if (Button(350, 200, "我是管理员"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminLoginMenu();
			return;
		}

		if (Button(360, 300, "我是用户"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientLoginMenu();
			return;
		}

		if (Button(360, 400, "点击退出"))
		{
			break;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}