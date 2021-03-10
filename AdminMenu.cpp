
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//以时间排序的订单
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;

void Run_AdminLoginMenu()
{
	PText id = (PText)malloc(sizeof(Text));
	PText password = (PText)malloc(sizeof(Text));
	Init_text(id, 330, 500, 200, 230, 150);
	Init_text(password, 330, 500, 300, 330, 150);
	bool Is_Input = false;
	int choose = 0;
	wchar_t key = 0;

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
		outtextxy(200, 70, "管理员登录界面");

		if (Is_Input)			//键盘输入
		{
			key = Input_Text();

			if (key != 0)
			{
				if (key == 9)
				{
					choose++;
					if (choose == 3) {
						choose = 1;
					}
				}
				else if (key == 13)
				{
					Is_Input = false;
					key = 0;
				}
				else
				{
					if (choose == 1) {
						Append_Text(id, key);
					}
					else if (choose == 2) {
						Append_Text(password, key);
					}
				}
			}
		}

		settextstyle(20, 0, "Verdana");		//打印文本
		setlinecolor(WHITE);
		outtextxy(id->x1, id->y1 + (id->y2 - id->y1 - 19) / 2, id->text);
		outtextxy(password->x1, password->y1 + (password->y2 - password->y1 - 19) / 2, password->text);

		if (Is_Input && choose == 1) {			//打印光标
			Draw_Fps(id);
		}
		else if (Is_Input && choose == 2) {
			Draw_Fps(password);
		}

		line(330, 225, 500, 225);				//打印横线
		line(330, 325, 500, 325);

		if (Button_Input(250, 200, "账号："))
		{
			choose = 1;
			Is_Input = true;
		}

		if (Button_Input(250, 300, "密码："))
		{
			choose = 2;
			Is_Input = true;
		}

		if (Button(350, 400, "登录"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminMainMenu();
			return;
		}

		if (Button(600, 500, "返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_MainMenu();
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Run_AdminMainMenu()
{
	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(310, 70, "管理员界面");

		if (Button(600, 500, "返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_MainMenu();
			break;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}