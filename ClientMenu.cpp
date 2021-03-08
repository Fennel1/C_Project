
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//以时间排序的订单
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;


void Run_ClientLoginMenu()			//用户登录界面
{
	PClient client = (PClient)malloc(sizeof(Client));

	PText id = (PText)malloc(sizeof(Text));
	PText password = (PText)malloc(sizeof(Text));
	Init_text(id, 400, 500, 200, 230, 200);
	Init_text(password, 400, 500, 300, 330, 200);
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
		wcscpy_s(t.lfFaceName, L"微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(280, 70, L"用户界面");

		if (Is_Input)			//键盘输入
		{
			key = Input_Text();
			if (key != 0)
			{
				if (key != 13)
				{
					if (choose == 1) {
						Append_Text(id, key);
					}
					else if (choose == 2) {
						Append_Text(password, key);
					}
				}
				else
				{
					Is_Input = false;
					key = 0;
				}
			}
		}

		settextstyle(20, 0, L"Verdana");		//打印文本
		setlinecolor(WHITE);
		outtextxy(id->x1, id->y1 + (id->y2 - id->y1 - 19) / 2, id->text);
		outtextxy(password->x1, password->y1 + (password->y2 - password->y1 - 19) / 2, password->text);

		if (Is_Input && choose == 1) {			//打印光标
			Draw_Fps(id);
		}
		else if (Is_Input && choose == 2) {
			Draw_Fps(password);
		}	
		
		line(350, 225, 500, 225);				//打印横线
		line(330, 325, 500, 325);

		if (Button(250, 200, L"身份证号："))
		{
			choose = 1;
			Is_Input = true;
		}

		if (Button(250, 300, L"密码："))
		{
			choose = 2;
			Is_Input = true;
		}

		if (Button(250, 400, L"登录"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		if (Button(400, 400, L"注册"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientRegisterMenu();
			return;
		}

		if (Button(600, 500, L"返回"))
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

void Run_ClientRegisterMenu()
{
	PClient client = (PClient)malloc(sizeof(Client));
	client->head_order = NULL;
	client->VIP = 0;
	client->num_bill = 0;
	client->pay = 0;

	PText id = (PText)malloc(sizeof(Text));
	PText password = (PText)malloc(sizeof(Text));
	PText name = (PText)malloc(sizeof(Text));
	PText phone = (PText)malloc(sizeof(Text));
	Init_text(id, 400, 500, 200, 230, 200);
	Init_text(password, 400, 500, 275, 305, 200);
	Init_text(name, 400, 500, 350, 380, 200);
	Init_text(phone, 400, 500, 425, 455, 200);
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
		wcscpy_s(t.lfFaceName, L"微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(280, 70, L"注册界面");

		if (Is_Input)			//键盘输入
		{
			key = Input_Text();
			if (key != 0)
			{
				if (key != 13)
				{
					if (choose == 1) {
						Append_Text(id, key);
					}
					else if (choose == 2) {
						Append_Text(password, key);
					}
					else if (choose == 3) {
						Append_Text(name, key);
					}
					else if (choose == 4) {
						Append_Text(phone, key);
					}
				}
				else
				{
					Is_Input = false;
					key = 0;
				}
			}
		}

		settextstyle(20, 0, L"Verdana");		//打印文本
		setlinecolor(WHITE);
		outtextxy(id->x1, id->y1 + (id->y2 - id->y1 - 19) / 2, id->text);
		outtextxy(password->x1, password->y1 + (password->y2 - password->y1 - 19) / 2, password->text);
		outtextxy(name->x1, name->y1 + (name->y2 - name->y1 - 19) / 2, name->text);
		outtextxy(phone->x1, phone->y1 + (phone->y2 - phone->y1 - 19) / 2, phone->text);

		if (Is_Input && choose == 1) {			//打印光标
			Draw_Fps(id);
		}
		else if (Is_Input && choose == 2) {
			Draw_Fps(password);
		}
		else if (Is_Input && choose == 3) {
			Draw_Fps(name);
		}
		else if (Is_Input && choose == 4) {
			Draw_Fps(phone);
		}

		line(330, 225, 500, 225);				//打印横线
		line(330, 300, 500, 300);
		line(330, 375, 500, 375);
		line(330, 450, 500, 450);

		if (Button(250, 200, L"身份证号："))
		{
			choose = 1;
			Is_Input = true;
		}

		if (Button(250, 275, L"密码："))
		{
			choose = 2;
			Is_Input = true;
		}

		if (Button(250, 350, L"姓名："))
		{
			choose = 3;
			Is_Input = true;
		}

		if (Button(250, 425, L"电话："))
		{
			choose = 4;
			Is_Input = true;
		}

		if (Button(400, 500, L"注册"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		if (Button(600, 500, L"返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientLoginMenu();
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Run_ClientMainMenu(PClient client)
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
		outtextxy(310, 70, L"用户主界面");

		if (Button(350, 200, L"我要住房"))
		{
			FlushBatchDraw();
			cleardevice();
			Commit_Order(client);
			return;
		}

		if (Button(350, 300, L"我要退房"))
		{
			FlushBatchDraw();
			cleardevice();
			Delete_Order(client);
			return;
		}

		if (Button(330, 400, L"我要查看订单"))
		{
			FlushBatchDraw();
			cleardevice();
			Show_Order(client);
			return;
		}

		if (Button(350, 500, L"注销账户"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientLoginMenu();
			break;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Commit_Order(PClient client)
{

}

void Delete_Order(PClient client)
{

}

void Show_Order(PClient client)
{

}