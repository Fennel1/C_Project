
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
			FlushBatchDraw();
			cleardevice();
			PClient client = Login(id->text, password->text);
			if (client != NULL) {
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
				char title[] = "ע��ʧ��";
				char text[4][50];
				int num = 0;
				if (judge[0])	sprintf(text[num++], "���֤�Ÿ�ʽ����");
				if (judge[1])	sprintf(text[num++], "�����ʽ����");
				if (judge[2])	sprintf(text[num++], "�����������벻һ��");
				if (judge[3])	sprintf(text[num++], "�绰�����ʽ����");
				Popup_Window(250, 200, 300, 200, title, text, num, 1);
				Run_ClientRegisterMenu();
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
	time_t timep;			//��ȡϵͳʱ��
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);

	int year = 1900 + p->tm_year, month = 1 + p->tm_mon, day = p->tm_mday;

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
			cleardevice();
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
			cleardevice();
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
			cleardevice();
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
			cleardevice();
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
	sprintf(text[2], "��סʱ�䣺%d��%d��%d��", start.hour, start.month, start.day);
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
	PText message = (PText)malloc(sizeof(Text));
	Init_text(message, 330, 500, 200, 230, 150);

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();



		if (Button(450, 500, "���"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientMainMenu(client);
			return;
		}

		if (Button(600, 500, "�ݲ�����"))
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


void Delete_Order(PClient client)		//�û������˷�����
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
		outtextxy(310, 70, "�û������˷�����");

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Show_Order(PClient client)			//�û��鿴����
{
	POrder order = client->head_order;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 45;
		strcpy(t.lfFaceName, "΢���ź� Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);

		if (client->head_order == NULL)
		{
			outtextxy(310, 70, "����ʷ����");
		}
		else
		{
			
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