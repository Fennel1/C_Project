
#include "functions.h"

extern MOUSEMSG M_msg;				// �����Ϣ\

extern PClient P_Head_Client;		//�û�����

extern POrder P_Head_Order;		//��ʱ������Ķ���

extern PRoom P_Head_Room;

void Run_ClientLoginMenu()			//�û���¼����
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
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();

		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "΢���ź� Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(280, 70, "�û�����");

		if (Is_Input)			//��������
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
						PClient client = Login(id->text, password->text);
						if (client != NULL) {
							FlushBatchDraw();
							cleardevice();
							Client_Order_Init(client);
							Run_ClientMainMenu(client);
						}
						else
						{
							char title[] = "��½ʧ��";
							char text[1][50];
							sprintf(text[0], "�˻����������");
							if (Popup_Window(250, 200, 300, 200, title, text, 1, 1))
							{
								FlushBatchDraw();
								cleardevice();
								Run_ClientLoginMenu();
							}
						}
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

		settextstyle(20, 0, "Verdana");		//��ӡ�ı�
		setlinecolor(WHITE);
		outtextxy(id->x1, id->y1 + (id->y2 - id->y1 - 19) / 2, id->text);
		outtextxy(password->x1, password->y1 + (password->y2 - password->y1 - 19) / 2, password->text);

		if (Is_Input && choose == 1) {			//��ӡ���
			Draw_Fps(id);
		}
		else if (Is_Input && choose == 2) {
			Draw_Fps(password);
		}	
		
		line(330, 225, 500, 225);				//��ӡ����
		line(330, 325, 500, 325);

		if (Button_Input(215, 200, "���֤�ţ�"))
		{
			choose = 1;
			Is_Input = true;
		}

		if (Button_Input(250, 300, "���룺"))
		{
			choose = 2;
			Is_Input = true;
		}

		if (Button(250, 400, "��¼"))
		{
			PClient client = Login(id->text, password->text);
			if (client != NULL) {
				FlushBatchDraw();
				cleardevice();
				Client_Order_Init(client);
				Run_ClientMainMenu(client);
			}
			else
			{
				char title[] = "��½ʧ��";
				char text[1][50];
				sprintf(text[0], "�˻����������");
				if (Popup_Window(250, 200, 300, 200, title, text, 1, 1))
				{
					FlushBatchDraw();
					cleardevice();
					Run_ClientLoginMenu();
				}
			}
			return;
		}

		if (Button(400, 400, "ע��"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientRegisterMenu();
			return;
		}

		if (Button(600, 500, "����"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_MainMenu();
			break;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Run_ClientRegisterMenu()			//�û�ע�����
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
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();

		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "΢���ź� Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(280, 70, "ע�����");

		if (Is_Input)			//��������
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
					if (choose == 5)
					{
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
							Client_Order_Init(client);
							Run_ClientMainMenu(client);
						}
						else
						{
							char title[] = "ע��ʧ��";
							char text[4][50];
							int num = 0;
							if (judge[0])	sprintf(text[num++], "���֤�Ÿ�ʽ����");
							if (judge[1])	sprintf(text[num++], "�����ʽ����");
							if (judge[2])	sprintf(text[num++], "�����������벻һ��");
							if (judge[3])	sprintf(text[num++], "�绰�����ʽ����");
							if (Popup_Window(250, 200, 300, 200, title, text, num, 1)) {
								FlushBatchDraw();
								cleardevice();
								Run_ClientRegisterMenu();
							}
						}
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

		settextstyle(20, 0, "Verdana");		//��ӡ�ı�
		setlinecolor(WHITE);
		outtextxy(id->x1, id->y1 + (id->y2 - id->y1 - 19) / 2, id->text);
		outtextxy(password->x1, password->y1 + (password->y2 - password->y1 - 19) / 2, password->text);
		outtextxy(repassword->x1, repassword->y1 + (repassword->y2 - repassword->y1 - 19) / 2, repassword->text);
		outtextxy(name->x1, name->y1 + (name->y2 - name->y1 - 19) / 2, name->text);
		outtextxy(phone->x1, phone->y1 + (phone->y2 - phone->y1 - 19) / 2, phone->text);

		if (Is_Input && choose == 1) {			//��ӡ���
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

		line(330, 225, 500, 225);				//��ӡ����
		line(330, 300, 500, 300);
		line(330, 375, 500, 375);
		line(330, 450, 500, 450);
		line(330, 525, 500, 525);

		if (Button_Input(215, 200, "���֤�ţ�"))
		{
			choose = 1;
			Is_Input = true;
		}

		if (Button_Input(250, 275, "���룺"))
		{
			choose = 2;
			Is_Input = true;
		}

		if (Button_Input(215, 350, "ȷ�����룺"))
		{
			choose = 3;
			Is_Input = true;
		}

		if (Button_Input(250, 425, "������"))
		{
			choose = 4;
			Is_Input = true;
		}

		if (Button_Input(250, 500, "�绰��"))
		{
			choose = 5;
			Is_Input = true;
		}

		if (Button(400, 550, "ע��"))
		{
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
				Client_Order_Init(client);
				Run_ClientMainMenu(client);
			}
			else
			{
				char title[] = "ע��ʧ��";
				char text[4][50];
				int num = 0;
				if (judge[0])	sprintf(text[num++], "���֤�Ÿ�ʽ����");
				if (judge[1])	sprintf(text[num++], "�����ʽ����");
				if (judge[2])	sprintf(text[num++], "�����������벻һ��");
				if (judge[3])	sprintf(text[num++], "�绰�����ʽ����");
				if (Popup_Window(250, 200, 300, 200, title, text, num, 1)) {
					FlushBatchDraw();
					cleardevice();
					Run_ClientRegisterMenu();
				}

			}
			return;
		}

		if (Button(600, 500, "����"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientLoginMenu();
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Run_ClientMainMenu(PClient client)			//�û����˽���
{
	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "΢���ź� Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(310, 70, "�û����˽��� ");

		if (Button(350, 200, "��Ҫס��"))
		{
			FlushBatchDraw();
			cleardevice();
			Commit_Order(client);
			return;
		}

		if (Button(350, 300, "��Ҫ�˷�"))
		{
			FlushBatchDraw();
			cleardevice();
			Delete_Order(client);
			return;
		}

		if (Button(330, 400, "��Ҫ�鿴����"))
		{
			FlushBatchDraw();
			cleardevice();
			Show_Order(client);
			return;
		}

		if (Button(350, 500, "ע���˻�"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientLoginMenu();
			break;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Commit_Order(PClient client)		//�û�����ס������
{
	time_t timep;			//��ȡϵͳʱ��
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);

	int year = 1900 + p->tm_year, month = 1 + p->tm_mon, day = p->tm_mday;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();

		Draw_Calendar(year, month, client);

		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "΢���ź� Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(200, 70, "��ѡ����סʱ��");

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
		strcpy(t.lfFaceName, "΢���ź� Light");
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

		if (Button(600, 500, "����"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void ReCommit_Order(PClient client, int s_year, int s_month, int s_day)
{

	int year = s_year, month = s_month, day = s_day;

	int choose = 0;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();

		reDraw_Calendar(year, month, s_year, s_month, s_day, client);

		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "΢���ź� Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(200, 70, "��ѡ���˷�ʱ��");

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
		strcpy(t.lfFaceName, "΢���ź� Light");
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

		if (Button(600, 500, "����"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}


void Choose_room(PClient client, int *room_num, Time start, Time end)
{
	char text[20];
	POrder order = NULL;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();


		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 75;
		strcpy(t.lfFaceName, "΢���ź� Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(265, 70, "��ѡ����");

		if (Button_Input(265, 200, "�����ӵ㷿"))
		{
			FlushBatchDraw();
			order = Add_Order(client, A1, start, end);
			Complete_Order(order, client, start, end);
		}

		gettextstyle(&t);
		t.lfHeight = 35;
		sprintf(text, "ʣ�ࣺ%d��", room_num[0]);
		outtextxy(265, 250, text);

		if (Button_Input(465, 200, "˫���ӵ㷿"))
		{
			FlushBatchDraw();
			order = Add_Order(client, A2, start, end);
			Complete_Order(order, client, start, end);
		}

		gettextstyle(&t);
		t.lfHeight = 35;
		sprintf(text, "ʣ�ࣺ%d��", room_num[1]);
		outtextxy(465, 250, text);

		if (Button(265, 350, "���˶��ⷿ"))
		{
			FlushBatchDraw();
			order = Add_Order(client, B1, start, end);
			Complete_Order(order, client, start, end);

		}

		gettextstyle(&t);
		t.lfHeight = 35;
		sprintf(text, "ʣ�ࣺ%d��", room_num[2]);
		outtextxy(265, 400, text);

		if (Button(465, 350, "˫�˶��ⷿ"))
		{
			FlushBatchDraw();
			order = Add_Order(client, B2, start, end);
			Complete_Order(order, client, start, end);
		}

		gettextstyle(&t);
		t.lfHeight = 35;
		sprintf(text, "ʣ�ࣺ%d��", room_num[3]);
		outtextxy(465, 400, text);

		if (Button(600, 500, "����"))
		{
			FlushBatchDraw();
			cleardevice();
			Commit_Order(client);
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Complete_Order(POrder order, PClient client, Time start, Time end)
{
	char title[] = "ȷ�϶�����Ϣ";
	char text[7][50];
	sprintf(text[0], "������ţ�%s", order->order_id);
	sprintf(text[1], "�����ţ�%s", order->room_id);
	sprintf(text[2], "��סʱ�䣺%d��%d��%d��", start.year, start.month, start.day);
	sprintf(text[3], "�˷�ʱ�䣺%d��%d��%d��", end.year, end.month, end.day);
	sprintf(text[4], "�۸�%.2lf", order->price);
	sprintf(text[5], "�ۿۣ�%.0lf��", (1-client->VIP * 0.03)*100 );
	sprintf(text[6], "��֧����%.2lf��", (1 - client->VIP * 0.03) * order->price);
	Popup_Window(250, 200, 300, 200, title, text, 7, 1);

	cleardevice();

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();

		IMAGE img;
		loadimage(&img, _T("pay.jpg"), 400, 400, true);
		putimage(200, 70, &img);
			

		if (Button(475, 500, "���֧��"))
		{
			FlushBatchDraw();
			cleardevice();
			Message_Board(order, client);
			return;
		}

		if (Button(600, 500, "�˳�֧��"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Message_Board(POrder order, PClient client)
{
	Remark remark;
	PText message = (PText)malloc(sizeof(Text));
	PText line1 = (PText)malloc(sizeof(Text));
	PText line2 = (PText)malloc(sizeof(Text));
	PText line3 = (PText)malloc(sizeof(Text));
	PText line4 = (PText)malloc(sizeof(Text));
	PText line5 = (PText)malloc(sizeof(Text));
	PText line6 = (PText)malloc(sizeof(Text));
	PText line7 = (PText)malloc(sizeof(Text));
	Init_text(message, 0, 0, 0, 0, 150);
	Init_text(line1, 200, 650, 160, 190, 150);
	Init_text(line2, 200, 650, 200, 230, 150);
	Init_text(line3, 200, 650, 240, 270, 150);
	Init_text(line4, 200, 650, 280, 320, 150);
	Init_text(line5, 200, 650, 320, 360, 150);
	Init_text(line6, 200, 650, 360, 400, 150);
	Init_text(line7, 200, 650, 400, 440, 150);
	int choose = 1;
	wchar_t key = 0;
	int star = 0, num_star=0;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		key = Input_Text();

		if (key != 0)
		{
			if (key == 13)
			{
				if (choose < 7) {
					choose++;
				}
			}
			else
			{
				if (choose == 1) {
					Append_Text(line1, key);
					Append_Text(message, key);
				}
				else if (choose == 2) {
					Append_Text(line2, key);
					Append_Text(message, key);
				}
				else if (choose == 3) {
					Append_Text(line3, key);
					Append_Text(message, key);
				}
				else if (choose == 4) {
					Append_Text(line4, key);
					Append_Text(message, key);
				}
				else if (choose == 5) {
					Append_Text(line5, key);
					Append_Text(message, key);
				}
				else if (choose == 6) {
					Append_Text(line6, key);
					Append_Text(message, key);
				}
				else if (choose == 7) {
					Append_Text(line7, key);
					Append_Text(message, key);
				}
			}
		}

		outtextxy(0, 0, message->text);
		
		cleardevice();

		if (Button_Star(255, 75, &num_star, 1, star)){
			star = 1;
		}
		if (Button_Star(335, 75, &num_star, 2, star)){
			star = 2;
		}
		if (Button_Star(415, 75, &num_star, 3, star)){
			star = 3;
		}
		if (Button_Star(495, 75, &num_star, 4, star)){
			star = 4;
		}
		if (Button_Star(575, 75, &num_star, 5, star)){
			star = 5;
		}

		

		setfillcolor(RGB(100, 100, 100));
		solidrectangle(175, 150, 675, 450);

		settextstyle(20, 0, "Verdana");		//��ӡ�ı�
		setlinecolor(WHITE);
		outtextxy(line1->x1, line1->y1 + (line1->y2 - line1->y1 - 19) / 2, line1->text);
		outtextxy(line2->x1, line2->y1 + (line2->y2 - line2->y1 - 19) / 2, line2->text);
		outtextxy(line3->x1, line3->y1 + (line3->y2 - line3->y1 - 19) / 2, line3->text);
		outtextxy(line4->x1, line4->y1 + (line4->y2 - line4->y1 - 19) / 2, line4->text);
		outtextxy(line5->x1, line5->y1 + (line5->y2 - line5->y1 - 19) / 2, line5->text);
		outtextxy(line6->x1, line6->y1 + (line6->y2 - line6->y1 - 19) / 2, line6->text);
		outtextxy(line7->x1, line7->y1 + (line7->y2 - line7->y1 - 19) / 2, line7->text);

		if (choose == 1)		Draw_Fps(line1);
		else if (choose == 2)	Draw_Fps(line2);
		else if (choose == 3)	Draw_Fps(line3);
		else if (choose == 4)	Draw_Fps(line4);
		else if (choose == 5)	Draw_Fps(line5);
		else if (choose == 6)	Draw_Fps(line6);
		else if (choose == 7)	Draw_Fps(line7);

		if (Button(450, 500, "���"))
		{
			FlushBatchDraw();
			cleardevice();
			remark.star = star;
			strcpy(remark.message, message->text);
			Add_Remark_In_Order(order, remark);
			Add_In_Linklist(order, client);
			Change_File();
			Run_ClientMainMenu(client);
			return;
		}

		if (Button(600, 500, "�ݲ�����"))
		{
			FlushBatchDraw();
			cleardevice();
			remark.star = 0;
			strcpy(remark.message, "havenomessage");
			Add_Remark_In_Order(order, remark);
			Add_In_Linklist(order, client);
			Change_File();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}


void Delete_Order(PClient client)		//�û������˷�����
{
	time_t timep;			//��ȡϵͳʱ��
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);

	int year = 1900 + p->tm_year, month = 1 + p->tm_mon, day = p->tm_mday;

	POrder order = client->head_order;
	int page = 1;
	int num_page;
	if (client->num_bill % 5 == 0)	num_page = client->num_bill / 5;
	else	num_page = client->num_bill / 5 + 1;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();

		if (client->head_order == NULL)
		{
			outtextxy(300, 70, "����ʷ����");
		}
		else
		{
			POrder p_now_client_order = client->head_order->next;
			for (int i = 1; i < page; i++) {
				for (int j = 1; j <= 5; j++) {
					if (p_now_client_order == NULL)	break;
					p_now_client_order = p_now_client_order->next;
				}
			}

			for (int i = 1; i <= 5; i++)
			{
				if (p_now_client_order == NULL)	break;
				if (Button_Delete_Order(100, 75 + (i - 1) * 80, p_now_client_order))
				{
					char title[] = "�Ƿ�ȷ��ɾ������";
					char text[5][50];
					sprintf(text[0], "������ţ�%s", p_now_client_order->order_id);
					sprintf(text[1], "�����ţ�%s", p_now_client_order->room_id);
					sprintf(text[2], "��סʱ�䣺%d��%d��%d��", p_now_client_order->start.year, p_now_client_order->start.month, p_now_client_order->start.day);
					sprintf(text[3], "�˷�ʱ�䣺%d��%d��%d��", p_now_client_order->end.year, p_now_client_order->end.month, p_now_client_order->end.day);
					sprintf(text[4], "ʵ��֧����%.2lf��", (1 - client->VIP * 0.03) * p_now_client_order->price);
					POrder temp = p_now_client_order->next;
					if (Popup_Window(250, 200, 300, 200, title, text, 5, 2))
					{
						if (Check_Time(p_now_client_order->start.year, p_now_client_order->start.month, p_now_client_order->start.day, p_now_client_order->end.year, p_now_client_order->end.month, p_now_client_order->end.day))
						{
							Delete_Node(p_now_client_order, client);
							char title[] = "�ɹ�ɾ������";
							char text[1][50];
							Popup_Window(250, 200, 300, 200, title, text, 0, 1);
							p_now_client_order = temp;
							client->num_bill--;
							Change_File();
						}
						else
						{
							char title[] = "����ɾ��ʧ��";
							char text[3][50];
							sprintf(text[0], "������סʱ�䣺��%d��%d��%d��", p_now_client_order->start.year, p_now_client_order->start.month, p_now_client_order->start.day);
							sprintf(text[1], "�˷�ʱ�䣺%d��%d��%d��", year, month, day);
							sprintf(text[2], "����ɾ������ס�Ķ���");
							Popup_Window(250, 200, 300, 200, title, text, 3, 1);
						}
					}
				}
				if (p_now_client_order == NULL)	break;
				p_now_client_order = p_now_client_order->next;
			}
		}

		if (Button(200, 500, "��һҳ"))
		{
			if (page > 1) {
				page--;
			}
		}

		char text[10];
		sprintf(text, "��%dҳ", page);
		outtextxy(300, 500, text);

		if (Button(400, 500, "��һҳ"))
		{
			if (page < num_page) {
				page++;
			}
		}

		if (Button(600, 500, "����"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Show_Order(PClient client)			//�û��鿴����
{
	POrder order = client->head_order;
	int page = 1;
	int num_page;
	if (client->num_bill % 5 == 0)	num_page = client->num_bill / 5;
	else	num_page = client->num_bill / 5 + 1;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();

		if (client->head_order == NULL)
		{
			outtextxy(300, 70, "����ʷ����");
		}
		else
		{
			POrder p_now_client_order = client->head_order->next;
			for (int i = 1; i < page; i++) {
				for (int j = 1; j <= 5; j++) {
					if (p_now_client_order == NULL)	break;
					p_now_client_order = p_now_client_order->next;
				}
			}

			for (int i = 1; i <= 5; i++) 
			{
				if (p_now_client_order == NULL)	break;
				if (Button_Order(125, 75 + (i - 1) * 80, p_now_client_order))
				{
					char title[] = "������Ϣ";
					char text[7][50];
					sprintf(text[0], "������ţ�%s", p_now_client_order->order_id);
					sprintf(text[1], "�����ţ�%s", p_now_client_order->room_id);
					sprintf(text[2], "��סʱ�䣺%d��%d��%d��", p_now_client_order->start.year, p_now_client_order->start.month, p_now_client_order->start.day);
					sprintf(text[3], "�˷�ʱ�䣺%d��%d��%d��", p_now_client_order->end.year, p_now_client_order->end.month, p_now_client_order->end.day);
					sprintf(text[4], "�۸�%.2lf", p_now_client_order->price);
					sprintf(text[5], "�ۿۣ�%.0lf��", (1 - client->VIP * 0.03) * 100);
					sprintf(text[6], "ʵ��֧����%.2lf��", (1 - client->VIP * 0.03) * p_now_client_order->price);
					Popup_Window(250, 200, 300, 200, title, text, 7, 1);
				}
				
				p_now_client_order = p_now_client_order->next;
			}
		}

		if (Button(200, 500, "��һҳ"))
		{
			if (page > 1) {
				page--;
			}
		}

		char text[10];
		sprintf(text, "��%dҳ", page);
		outtextxy(300, 500, text);

		if (Button(400, 500, "��һҳ"))
		{
			if (page < num_page) {
				page++;
			}
		}

		if (Button(600, 500, "����"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}