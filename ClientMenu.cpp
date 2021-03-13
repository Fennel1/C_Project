
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表

extern POrder P_Head_Order;		//以时间排序的订单

extern PRoom P_Head_Room;


void Run_ClientLoginMenu()			//用户登录界面
{
	PClient client = (PClient)malloc(sizeof(Client));

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
		outtextxy(280, 70, "用户界面");

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

		if (Button_Input(215, 200, "身份证号："))
		{
			choose = 1;
			Is_Input = true;
		}

		if (Button_Input(250, 300, "密码："))
		{
			choose = 2;
			Is_Input = true;
		}

		if (Button(250, 400, "登录"))
		{
			FlushBatchDraw();
			cleardevice();
			PClient client = Login(id->text, password->text);
			if (client != NULL) {
				Run_ClientMainMenu(client);
			}
			else
			{
				char title[] = "登陆失败";
				char text[1][50];
				sprintf(text[0], "账户或密码错误");
				if (Popup_Window(250, 200, 300, 200, title, text, 1, 1))
				{
					FlushBatchDraw();
					cleardevice();
					Run_ClientLoginMenu();
				}
			}
			return;
		}

		if (Button(400, 400, "注册"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientRegisterMenu();
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

void Run_ClientRegisterMenu()			//用户注册界面
{
	PClient client = (PClient)malloc(sizeof(Client));
	client->head_order = NULL;
	client->VIP = 0;
	client->num_bill = 0;
	client->pay = 0;

	PText id = (PText)malloc(sizeof(Text));
	PText password = (PText)malloc(sizeof(Text));
	PText repassword = (PText)malloc(sizeof(Text));
	PText name = (PText)malloc(sizeof(Text));
	PText phone = (PText)malloc(sizeof(Text));
	Init_text(id, 330, 500, 200, 230, 150);
	Init_text(password, 330, 500, 275, 305, 150);
	Init_text(repassword, 330, 500, 350, 380, 150);
	Init_text(name, 330, 500, 425, 455, 150);
	Init_text(phone, 330, 500, 500, 530, 150);
	bool Is_Input = false;
	int choose = 0;
	bool judge[5] = { false, false, false, false, false };
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
		outtextxy(280, 70, "注册界面");

		if (Is_Input)			//键盘输入
		{
			key = Input_Text();

			if (key != 0)
			{
				if (key == 9) 
				{
					choose++;
					if (choose == 6) {
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
					else if (choose == 3) {
						Append_Text(repassword, key);
					}
					else if (choose == 4) {
						Append_Text(name, key);
					}
					else if (choose == 5) {
						Append_Text(phone, key);
					}
				}
			}
		}

		settextstyle(20, 0, "Verdana");		//打印文本
		setlinecolor(WHITE);
		outtextxy(id->x1, id->y1 + (id->y2 - id->y1 - 19) / 2, id->text);
		outtextxy(password->x1, password->y1 + (password->y2 - password->y1 - 19) / 2, password->text);
		outtextxy(repassword->x1, repassword->y1 + (repassword->y2 - repassword->y1 - 19) / 2, repassword->text);
		outtextxy(name->x1, name->y1 + (name->y2 - name->y1 - 19) / 2, name->text);
		outtextxy(phone->x1, phone->y1 + (phone->y2 - phone->y1 - 19) / 2, phone->text);

		if (Is_Input && choose == 1) {			//打印光标
			Draw_Fps(id);
		}
		else if (Is_Input && choose == 2) {
			Draw_Fps(password);
		}
		else if (Is_Input && choose == 3) {
			Draw_Fps(repassword);
		}
		else if (Is_Input && choose == 4) {
			Draw_Fps(name);
		}
		else if (Is_Input && choose == 5) {
			Draw_Fps(phone);
		}

		line(330, 225, 500, 225);				//打印横线
		line(330, 300, 500, 300);
		line(330, 375, 500, 375);
		line(330, 450, 500, 450);
		line(330, 525, 500, 525);

		if (Button_Input(215, 200, "身份证号："))
		{
			choose = 1;
			Is_Input = true;
		}

		if (Button_Input(250, 275, "密码："))
		{
			choose = 2;
			Is_Input = true;
		}

		if (Button_Input(215, 350, "确认密码："))
		{
			choose = 3;
			Is_Input = true;
		}

		if (Button_Input(250, 425, "姓名："))
		{
			choose = 4;
			Is_Input = true;
		}

		if (Button_Input(250, 500, "电话："))
		{
			choose = 5;
			Is_Input = true;
		}

		if (Button(400, 550, "注册"))
		{
			FlushBatchDraw();
			cleardevice();
			if (Checkid(id->text)) {
				judge[0] = true;
			}
			if (Checkpassword(password->text)) {
				judge[1] = true;
			}
			if (Checkrepassword(password->text, repassword->text)) {
				judge[2] = true;
			}
			if (Checkphone(phone->text)) {
				judge[3] = true;
			}
			if (judge[0] == true && judge[1] == true && judge[2] == true && judge[3] == true)
			{
				PClient client = Register(id->text, password->text, name->text, phone->text);
				FlushBatchDraw();
				cleardevice();
				Run_ClientMainMenu(client);
			}
			else
			{
				char title[] = "注册失败";
				char text[4][50];
				int num = 0;
				if (judge[0])	sprintf(text[num++], "身份证号格式错误");
				if (judge[1])	sprintf(text[num++], "密码格式错误");
				if (judge[2])	sprintf(text[num++], "两次密码输入不一致");
				if (judge[3])	sprintf(text[num++], "电话号码格式错误");
				Popup_Window(250, 200, 300, 200, title, text, num, 1);
				Run_ClientRegisterMenu();
			}
			return;
		}

		if (Button(600, 500, "返回"))
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

void Run_ClientMainMenu(PClient client)			//用户个人界面
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
		outtextxy(310, 70, "用户个人界面 ");

		if (Button(350, 200, "我要住房"))
		{
			FlushBatchDraw();
			cleardevice();
			Commit_Order(client);
			return;
		}

		if (Button(350, 300, "我要退房"))
		{
			FlushBatchDraw();
			cleardevice();
			Delete_Order(client);
			return;
		}

		if (Button(330, 400, "我要查看订单"))
		{
			FlushBatchDraw();
			cleardevice();
			Show_Order(client);
			return;
		}

		if (Button(350, 500, "注销账户"))
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

void Commit_Order(PClient client)		//用户申请住房界面
{
	time_t timep;			//获取系统时间
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);

	int year = 1900 + p->tm_year, month = 1 + p->tm_mon, day = p->tm_mday;

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		cleardevice();

		Draw_Calendar(year, month, client);

		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(200, 70, "请选择入住时间");

		if (Button(240, 150, "<<")) {
			(year)--;
		}

		if (Button(300, 150, "<")) {
			if (month > 1) {
				(month)--;
			}
			else {
				(year)--;
				month = 12;
			}
		}

		char str[10];
		sprintf(str, "%4d.%2d", year, month);
		gettextstyle(&t);
		t.lfHeight = 22;
		strcpy(t.lfFaceName, "微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(395, 155, str);

		if (Button(520, 150, ">")) {
			if (month < 12) {
				(month)++;
			}
			else {
				(year)++;
				month = 1;
			}
		}

		if (Button(570, 150, ">>")) {
			(year)++;
		}		

		if (Button(600, 500, "返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void ReCommit_Order(PClient client, int s_year, int s_month, int s_day)
{
	time_t timep;			//获取系统时间
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);

	int year = 1900 + p->tm_year, month = 1 + p->tm_mon, day = p->tm_mday;

	int choose = 0;

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		cleardevice();

		reDraw_Calendar(year, month, s_year, s_month, s_day, client);

		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(200, 70, "请选择退房时间");

		if (Button(240, 150, "<<")) {
			(year)--;
		}

		if (Button(300, 150, "<")) {
			if (month > 1) {
				(month)--;
			}
			else {
				(year)--;
				month = 12;
			}
		}

		char str[10];
		sprintf(str, "%4d.%2d", year, month);
		gettextstyle(&t);
		t.lfHeight = 22;
		strcpy(t.lfFaceName, "微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(395, 155, str);

		if (Button(520, 150, ">")) {
			if (month < 12) {
				(month)++;
			}
			else {
				(year)++;
				month = 1;
			}
		}

		if (Button(570, 150, ">>")) {
			(year)++;
		}

		if (Button(600, 500, "返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}


void Choose_room(PClient client, int *room_num, Time start, Time end)
{
	char text[20];
	POrder order = NULL;

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
		outtextxy(265, 70, "请选择房型");

		if (Button_Input(265, 200, "单人钟点房"))
		{
			FlushBatchDraw();
			cleardevice();
			order = Add_Order(client, A1, start, end);
			Complete_Order(order, client, start, end);
		}

		gettextstyle(&t);
		t.lfHeight = 35;
		sprintf(text, "剩余：%d间", room_num[0]);
		outtextxy(265, 250, text);

		if (Button_Input(465, 200, "双人钟点房"))
		{
			FlushBatchDraw();
			cleardevice();
			order = Add_Order(client, A2, start, end);
			Complete_Order(order, client, start, end);
		}

		gettextstyle(&t);
		t.lfHeight = 35;
		sprintf(text, "剩余：%d间", room_num[1]);
		outtextxy(465, 250, text);

		if (Button(265, 350, "单人短租房"))
		{
			FlushBatchDraw();
			cleardevice();
			order = Add_Order(client, B1, start, end);
			Complete_Order(order, client, start, end);

		}

		gettextstyle(&t);
		t.lfHeight = 35;
		sprintf(text, "剩余：%d间", room_num[2]);
		outtextxy(265, 400, text);

		if (Button(465, 350, "双人短租房"))
		{
			FlushBatchDraw();
			cleardevice();
			order = Add_Order(client, B2, start, end);
			Complete_Order(order, client, start, end);
		}

		gettextstyle(&t);
		t.lfHeight = 35;
		sprintf(text, "剩余：%d间", room_num[3]);
		outtextxy(465, 400, text);

		if (Button(600, 500, "返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Commit_Order(client);
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Complete_Order(POrder order, PClient client, Time start, Time end)
{
	char title[] = "确认订单信息";
	char text[7][50];
	sprintf(text[0], "订单编号：%s", order->order_id);
	sprintf(text[1], "房间编号：%s", order->room_id);
	sprintf(text[2], "入住时间：%d年%d月%d日", start.hour, start.month, start.day);
	sprintf(text[3], "退房时间：%d年%d月%d日", end.year, end.month, end.day);
	sprintf(text[4], "价格：%.2lf", order->price);
	sprintf(text[5], "折扣：%.0lf折", (1-client->VIP * 0.03)*100 );
	sprintf(text[6], "需支付：%.2lf折", (1 - client->VIP * 0.03) * order->price);
	Popup_Window(250, 200, 300, 200, title, text, 7, 1);
	cleardevice();

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		cleardevice();

		IMAGE img;
		loadimage(&img, _T("pay.jpg"), 400, 400, true);
		putimage(200, 70, &img);
			

		if (Button(475, 500, "完成支付"))
		{
			FlushBatchDraw();
			cleardevice();
			Message_Board(order, client);
			return;
		}

		if (Button(600, 500, "退出支付"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Message_Board(POrder order, PClient client)
{
	PText message = (PText)malloc(sizeof(Text));
	Init_text(message, 330, 500, 200, 230, 150);

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		cleardevice();



		if (Button(450, 500, "完成"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		if (Button(600, 500, "暂不评论"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}


void Delete_Order(PClient client)		//用户申请退房界面
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
		outtextxy(310, 70, "用户申请退房界面");

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}

void Show_Order(PClient client)			//用户查看订单
{
	POrder order = client->head_order;

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
			M_msg = GetMouseMsg();

		LOGFONT t;			//绘制文字
		gettextstyle(&t);
		t.lfHeight = 45;
		strcpy(t.lfFaceName, "微软雅黑 Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);

		if (client->head_order == NULL)
		{
			outtextxy(310, 70, "无历史订单");
		}
		else
		{
			
		}

		if (Button(600, 500, "返回"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// 执行未完成的绘制任务
		Sleep(10);
	}
}