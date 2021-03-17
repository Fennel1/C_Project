
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表

extern POrder P_Head_Order;		//以时间排序的订单

extern PRoom P_Head_Room;

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
					if (choose == 2)
					{
						FlushBatchDraw();
						cleardevice();
						Run_AdminMainMenu();
					}
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
		outtextxy(250, 50, "管理员界面");

		if (Button(350, 150, "查看酒店概况"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Hotel();
			return;
		}

		if (Button(350, 225, "显示房间信息"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Show_Room();
			return;
		}

		if (Button(350, 300, "显示订单信息"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Show_Order();
			return;
		}

		if (Button(370, 375, "查找订单"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Search_Order();
			return;
		}

		if (Button(370, 450, "查找用户"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Search_Client();
			return;
		}

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

void Run_Hotel()					//查看酒店概况
{
	
}

void Run_Show_Room()				//显示房间信息
{
	PRoom p_now_room = P_Head_Room->next;
	int page = 1;
	int num_page = 0;

	while (p_now_room != NULL) {			//计算页数
		num_page++;
		p_now_room = p_now_room->next;
	}
	if (num_page % 20 == 0)	num_page = num_page / 20;
	else	num_page = num_page / 20 + 1;

	PRoom p_head_order = P_Head_Room->next;

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		cleardevice();

		p_now_room = p_head_order;
		for (int i = 1; i < page; i++) {
			for (int j = 1; j <= 20; j++) {
				if (p_now_room == NULL)	break;
				p_now_room = p_now_room->next;
			}
		}

		for (int i = 1; i <= 5; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				if (p_now_room == NULL)	break;
				Button_Room(125 + (i - 1) * 130, 60 + (j - 1) * 90, p_now_room);
				p_now_room = p_now_room->next;
			}	
		}

		if (Button(200, 500, "上一页"))
		{
			if (page > 1) {
				page--;
			}
		}

		char text[10];
		sprintf(text, "第%d页", page);
		outtextxy(300, 500, text);

		if (Button(400, 500, "下一页"))
		{
			if (page < num_page) {
				page++;
			}
		}

		if (Button(600, 500, "返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminMainMenu();
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Run_Show_Order()				//显示订单信息
{
	POrder p_now_order = P_Head_Order->next;
	int page = 1;
	int num_page=0;
	bool flag1 = false, flag2 = false;
	bool choose1 = false, choose2 = false, choose3 = false, choose4 = false;


	while (p_now_order != NULL) {			//计算页数
		num_page++;
		p_now_order = p_now_order->next;
	}
	if (num_page % 5 == 0)	num_page = num_page / 5;
	else	num_page = num_page / 5 + 1;

	POrder p_head_order = NULL;

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		cleardevice();

		if (p_head_order == NULL)
		{
			outtextxy(340, 70, "无历史订单");
		}
		else
		{
			p_now_order = p_head_order;
			for (int i = 1; i < page; i++) {
				for (int j = 1; j <= 5; j++) {
					if (p_now_order == NULL)	break;
					p_now_order = p_now_order->next;
				}
			}

			for (int i = 1; i <= 5; i++)
			{
				if (p_now_order == NULL)	break;
				if (Button_Order(125, 75 + (i - 1) * 80, p_now_order))
				{
					char title[] = "订单信息";
					char text[7][50];
					sprintf(text[0], "订单编号：%s", p_now_order->order_id);
					sprintf(text[1], "房间编号：%s", p_now_order->room_id);
					sprintf(text[2], "用户身份证号：%s", p_now_order->client_id);
					sprintf(text[3], "入住时间：%d年%d月%d日", p_now_order->start.year, p_now_order->start.month, p_now_order->start.day);
					sprintf(text[4], "退房时间：%d年%d月%d日", p_now_order->end.year, p_now_order->end.month, p_now_order->end.day);
					sprintf(text[5], "订单价格：%.2lf", p_now_order->price);
					sprintf(text[6], "用户评价：%d★", p_now_order->remark.star);
					Popup_Window(250, 200, 300, 200, title, text, 7, 1);
				}

				p_now_order = p_now_order->next;
			}
		}

		if (Button(150, 30, "升序", choose1))
		{
			flag1 = false;
			choose1 = true;
			choose2 = false;
		}

		if (Button(275, 30, "降序", choose2))
		{
			flag1 = true;
			choose2 = true;
			choose1 = false;
		}

		if (Button(400, 30, "按时间排列", choose3))
		{
			flag2 = false;
			choose3 = true;
			choose4 = false;
		}

		if (Button(570, 30, "按ID排列", choose4))
		{
			flag2 = true;
			choose4 = true;
			choose3 = false;
		}

		if (Button(700, 30, "显示"))
		{
			p_head_order = NULL;
			if (flag1 == false && flag2 == false) {
				p_head_order = Sort_Order_Time_Ascending(P_Head_Order);
			}
			else if (flag1 == true && flag2 == false) {
				p_head_order = Sort_Order_Time_Descending(P_Head_Order);
			}
			else if (flag1 == false && flag2 == true) {
				p_head_order = Sort_Order_ID_Ascending(P_Head_Order);
			}
			else if (flag1 == true && flag2 == true) {
				p_head_order = Sort_Order_ID_Descending(P_Head_Order);
			}
		}

		if (Button(200, 500, "上一页"))
		{
			if (page > 1) {
				page--;
			}
		}

		char text[10];
		sprintf(text, "第%d页", page);
		outtextxy(300, 500, text);

		if (Button(400, 500, "下一页"))
		{
			if (page < num_page) {
				page++;
			}
		}

		if (Button(600, 500, "返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminMainMenu();
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Run_Search_Order()				//查找订单
{
	POrder p_now_order = P_Head_Order->next;
	int page = 1;
	int num_page = 0;

	while (p_now_order != NULL) {			//计算页数
		num_page++;
		p_now_order = p_now_order->next;
	}
	if (num_page % 5 == 0)	num_page = num_page / 5;
	else	num_page = num_page / 5 + 1;

	POrder p_head_order = NULL;

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		cleardevice();

		if (p_head_order == NULL)
		{
			outtextxy(300, 70, "查无订单");
		}
		else
		{
			p_now_order = p_head_order;
			for (int i = 1; i < page; i++) {
				for (int j = 1; j <= 5; j++) {
					if (p_now_order == NULL)	break;
					p_now_order = p_now_order->next;
				}
			}

			for (int i = 1; i <= 5; i++)
			{
				if (p_now_order == NULL)	break;
				if (Button_Order(125, 75 + (i - 1) * 80, p_now_order))
				{
					char title[] = "订单信息";
					char text[7][50];
					sprintf(text[0], "订单编号：%s", p_now_order->order_id);
					sprintf(text[1], "房间编号：%s", p_now_order->room_id);
					sprintf(text[2], "用户身份证号：%s", p_now_order->client_id);
					sprintf(text[3], "入住时间：%d年%d月%d日", p_now_order->start.year, p_now_order->start.month, p_now_order->start.day);
					sprintf(text[4], "退房时间：%d年%d月%d日", p_now_order->end.year, p_now_order->end.month, p_now_order->end.day);
					sprintf(text[1], "订单价格：%.2lf", p_now_order->price);
					sprintf(text[5], "用户评价：%d★", p_now_order->remark.star);
					Popup_Window(250, 200, 300, 200, title, text, 7, 1);
				}

				p_now_order = p_now_order->next;
			}
		}

		if (Button(650, 30, "查找"))
		{
		}

		if (Button(200, 500, "上一页"))
		{
			if (page > 1) {
				page--;
			}
		}

		char text[10];
		sprintf(text, "第%d页", page);
		outtextxy(300, 500, text);

		if (Button(400, 500, "下一页"))
		{
			if (page < num_page) {
				page++;
			}
		}

		if (Button(600, 500, "返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminMainMenu();
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Run_Search_Client()			//查找用户
{

}