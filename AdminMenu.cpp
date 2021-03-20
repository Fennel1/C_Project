
#include "functions.h"

extern MOUSEMSG M_msg;				// �����Ϣ\

extern PClient P_Head_Client;		//�û�����

extern POrder P_Head_Order;		//��ʱ������Ķ���

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
		outtextxy(200, 70, "����Ա��¼����");

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

		if (Button_Input(250, 200, "�˺ţ�"))
		{
			choose = 1;
			Is_Input = true;
		}

		if (Button_Input(250, 300, "���룺"))
		{
			choose = 2;
			Is_Input = true;
		}

		if (Button(350, 400, "��¼"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminMainMenu();
			return;
		}

		if (Button(600, 500, "����"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_MainMenu();
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Run_AdminMainMenu()
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
		outtextxy(250, 50, "����Ա����");

		if (Button(350, 150, "�鿴�Ƶ�ſ�"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Hotel();
			return;
		}

		if (Button(350, 225, "��ʾ������Ϣ"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Show_Room();
			return;
		}

		if (Button(350, 300, "��ʾ������Ϣ"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Show_Order();
			return;
		}

		if (Button(370, 375, "���Ҷ���"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Search_Order();
			return;
		}

		if (Button(370, 450, "�����û�"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_Search_Client();
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

void Run_Hotel()					//�鿴�Ƶ�ſ�
{
	time_t timep;			//��ȡϵͳʱ��
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);

	int year = 1900 + p->tm_year, month = 1 + p->tm_mon, day = p->tm_mday;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();

		

		if (Button(600, 500, "����"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminMainMenu();
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Run_Show_Room()				//��ʾ������Ϣ
{
	time_t timep;			//��ȡϵͳʱ��
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);

	int year = 1900 + p->tm_year, month = 1 + p->tm_mon, day = p->tm_mday;
	Time s, e;
	s = { year, month, day, 0, 0 };
	e = { year, month, day, 0, 0 };

	int num[4] = { 0 };
	int* rooms_num = num;

	rooms_num = Display_rooms_number(num, s, e);

	PRoom p_now_room = P_Head_Room->next;
	int page = 1;
	int num_page = 0;

	while (p_now_room != NULL) {			//����ҳ��
		num_page++;
		p_now_room = p_now_room->next;
	}
	if (num_page % 20 == 0)	num_page = num_page / 20;
	else	num_page = num_page / 20 + 1;

	PRoom p_head_order = P_Head_Room->next;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
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
				if (Button_Room(125 + (i - 1) * 130, 60 + (j - 1) * 90, p_now_room))
				{
					char title[] = "������Ϣ";
					char text[2][50];
					if (p_now_room->Is_Use == true) {
						sprintf(text[0], "����ʹ����");
					}
					else {
						sprintf(text[0], "����Ϊ��");
					}
					sprintf(text[1], "����۸�%.2lf", p_now_room->price);
					if (p_now_room->Is_Use == true) {
						Popup_Window(250, 200, 300, 200, title, text, 2, 1);
					}
					else {
						if (Popup_Window_Room(250, 200, 300, 200, title, text, 2, 2))
						{
							char title[] = "ȷ��ɾ���÷��䣿";
							char text[1][50];
							if (Popup_Window(250, 200, 300, 200, title, text, 0, 2))
							{
								//ɾ��
							}
						}
					}
					

				}
				p_now_room = p_now_room->next;
			}	
		}

		if (Button(150, 435, "���A1"))
		{

		}
		if (Button(300, 435, "���A2"))
		{

		}
		if (Button(450, 435, "���B1"))
		{

		}
		if (Button(600, 435, "���B2"))
		{

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
			Run_AdminMainMenu();
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Run_Show_Order()				//��ʾ������Ϣ
{
	POrder p_now_order = P_Head_Order->next;
	int page = 1;
	int num_page=0;
	bool flag1 = false, flag2 = false;
	bool choose1 = false, choose2 = false, choose3 = false, choose4 = false;


	while (p_now_order != NULL) {			//����ҳ��
		num_page++;
		p_now_order = p_now_order->next;
	}
	if (num_page % 5 == 0)	num_page = num_page / 5;
	else	num_page = num_page / 5 + 1;

	POrder p_head_order = NULL;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		cleardevice();

		if (p_head_order == NULL)
		{
			outtextxy(340, 70, "����ʷ����");
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
					char title[] = "������Ϣ";
					char text[7][50];
					sprintf(text[0], "������ţ�%s", p_now_order->order_id);
					sprintf(text[1], "�����ţ�%s", p_now_order->room_id);
					sprintf(text[2], "�û����֤�ţ�%s", p_now_order->client_id);
					sprintf(text[3], "��סʱ�䣺%d��%d��%d��", p_now_order->start.year, p_now_order->start.month, p_now_order->start.day);
					sprintf(text[4], "�˷�ʱ�䣺%d��%d��%d��", p_now_order->end.year, p_now_order->end.month, p_now_order->end.day);
					sprintf(text[5], "�����۸�%.2lf", p_now_order->price);
					sprintf(text[6], "�û����ۣ�%d��", p_now_order->remark.star);
					Popup_Window(250, 200, 300, 200, title, text, 7, 1);
				}

				p_now_order = p_now_order->next;
			}
		}

		if (Button(150, 30, "����", choose1))
		{
			flag1 = false;
			choose1 = true;
			choose2 = false;
		}

		if (Button(275, 30, "����", choose2))
		{
			flag1 = true;
			choose2 = true;
			choose1 = false;
		}

		if (Button(400, 30, "��ʱ������", choose3))
		{
			flag2 = false;
			choose3 = true;
			choose4 = false;
		}

		if (Button(570, 30, "��ID����", choose4))
		{
			flag2 = true;
			choose4 = true;
			choose3 = false;
		}

		if (Button(700, 30, "��ʾ"))
		{
			p_head_order = NULL;
			Order_Init();
			if (flag1 == false && flag2 == false) {
				p_head_order = Sort_Order_Time_Ascending(P_Head_Order);
				Change_File();
			}
			else if (flag1 == true && flag2 == false) {
				p_head_order = Sort_Order_Time_Descending(P_Head_Order);
				Change_File();
			}
			else if (flag1 == false && flag2 == true) {
				p_head_order = Sort_Order_ID_Ascending(P_Head_Order);
				Change_File();
			}
			else if (flag1 == true && flag2 == true) {
				p_head_order = Sort_Order_ID_Descending(P_Head_Order);
				Change_File();
			}
			p_head_order = p_head_order->next;
			page = 1;
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
			Run_AdminMainMenu();
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Run_Search_Order()				//���Ҷ���
{
	POrder p_now_order = P_Head_Order->next;
	int page = 1;
	int num_page = 0;

	POrder p_head_order = NULL;


	PText s_time = (PText)malloc(sizeof(Text));
	PText e_time = (PText)malloc(sizeof(Text));
	PText client_id = (PText)malloc(sizeof(Text));
	PText order_id = (PText)malloc(sizeof(Text));
	Init_text(s_time, 166, 320, 35, 65, 150);
	Init_text(e_time, 166, 320, 105, 135, 150);
	Init_text(client_id, 450, 610, 35, 65, 150);
	Init_text(order_id, 450, 610, 105, 135, 150);
	bool Is_Input = false;
	int choose = 0;
	bool judge[4] = { true, true, true, true };
	wchar_t key = 0;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		if (Is_Input)			//��������
		{
			key = Input_Text();

			if (key != 0)
			{
				if (key == 9)
				{
					choose++;
					if (choose == 5) {
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
						Append_Text(s_time, key);
					}
					else if (choose == 2) {
						Append_Text(e_time, key);
					}
					else if (choose == 3) {
						Append_Text(client_id, key);
					}
					else if (choose == 4) {
						Append_Text(order_id, key);
					}
				}
			}
		}

		cleardevice();

		settextstyle(20, 0, "Verdana");		//��ӡ�ı�
		setlinecolor(WHITE);
		outtextxy(s_time->x1, s_time->y1 + (s_time->y2 - s_time->y1 - 19) / 2, s_time->text);
		outtextxy(e_time->x1, e_time->y1 + (e_time->y2 - e_time->y1 - 19) / 2, e_time->text);
		outtextxy(client_id->x1, client_id->y1 + (client_id->y2 - client_id->y1 - 19) / 2, client_id->text);
		outtextxy(order_id->x1, order_id->y1 + (order_id->y2 - order_id->y1 - 19) / 2, order_id->text);

		if (Is_Input && choose == 1) {			//��ӡ���
			Draw_Fps(s_time);
		}
		else if (Is_Input && choose == 2) {
			Draw_Fps(e_time);
		}
		else if (Is_Input && choose == 3) {
			Draw_Fps(client_id);
		}
		else if (Is_Input && choose == 4) {
			Draw_Fps(order_id);
		}

		line(166, 60, 320, 60);				//��ӡ����
		line(166, 130, 320, 130);
		line(450, 60, 610, 60);
		line(450, 130, 610, 130);

		if (Button(680, 80, "����"))
		{
			if (p_head_order != NULL)
			{
				Destroy_Linklist(p_head_order);
				p_head_order = NULL;
			}

			if (!Search_Check_Time(s_time->text)) {
				judge[0] = false;
			}
			if (!Search_Check_Time(e_time->text)) {
				judge[1] = false;
			}
			if (!Search_Check_Clientid(client_id->text)) {
				judge[2] = false;
			}
			if (!Search_Check_Orderid(order_id->text)) {
				judge[3] = false;
			}
			if (judge[0] == true && judge[1] == true && judge[2] == true && judge[3] == true)		//��ʽ�޴���
			{
				if (s_time->text[0] != '\0' && e_time->text[0] == '\0' && client_id->text[0] == '\0' && order_id->text[0] == '\0') {		//���ݿ�ʼʱ�����
					Time s;
					sscanf(s_time->text, "%4d%2d%2d", &s.year, &s.month, &s.day);
					s.weekday = s.hour = 0;
					p_head_order = Search_Order_By_Starttime(s);
				}
				else if (s_time->text[0] == '\0' && e_time->text[0] != '\0' && client_id->text[0] == '\0' && order_id->text[0] == '\0') {		//���ݽ���ʱ�����
					Time e;
					sscanf(e_time->text, "%4d%2d%2d", &e.year, &e.month, &e.day);
					e.weekday = e.hour = 0;
					p_head_order = Search_Order_By_Endtime(e);
				}
				else if (s_time->text[0] == '\0' && e_time->text[0] == '\0' && client_id->text[0]!= '\0' && order_id->text[0] == '\0') {			//�����û�ID����
					p_head_order = Search_Order_By_Clientid(client_id->text);
				}
				else if (s_time->text[0] == '\0' && e_time->text[0] == '\0' && client_id->text[0] == '\0' && order_id->text[0]!= '\0') {		//���ݶ���ID����
					p_head_order = Search_Order_By_Orderid(order_id->text);
				}
				else if (s_time->text[0] != '\0' && e_time->text[0] != '\0' && client_id->text[0] == '\0' && order_id->text[0] == '\0') {		//���ݿ�ʼ����ʱ�����
					Time s, e;
					sscanf(s_time->text, "%4d%2d%2d", &s.year, &s.month, &s.day);
					sscanf(e_time->text, "%4d%2d%2d", &e.year, &e.month, &e.day);
					s.weekday = s.hour = e.weekday = e.hour = 0;
					p_head_order = Search_Order_By_Time(s, e);
				}
				else if (s_time->text[0] != '\0' && e_time->text[0] != '\0' && client_id->text[0] == '\0' && order_id->text[0]!= '\0') {		//���ݶ���ID & ʱ�����
					Time s, e;
					sscanf(s_time->text, "%4d%2d%2d", &s.year, &s.month, &s.day);
					sscanf(e_time->text, "%4d%2d%2d", &e.year, &e.month, &e.day);
					s.weekday = s.hour = e.weekday = e.hour = 0;
					p_head_order = Search_Order_By_OrderidT(order_id->text, s, e);
				}
				else if (s_time->text[0] != '\0' && e_time->text[0] != '\0' && client_id->text[0] != '\0' && order_id->text[0] == '\0') {		//�����û�ID & ʱ�����
					Time s, e;
					sscanf(s_time->text, "%4d%2d%2d", &s.year, &s.month, &s.day);
					sscanf(e_time->text, "%4d%2d%2d", &e.year, &e.month, &e.day);
					s.weekday = s.hour = e.weekday = e.hour = 0;
					p_head_order = Search_Order_By_ClientidT(client_id->text, s, e);
				}

				if (p_head_order != NULL)
				{
					p_now_order = p_head_order->next;
					num_page = 0;

					while (p_now_order != NULL) {			//����ҳ��
						num_page++;
						p_now_order = p_now_order->next;
					}
					if (num_page % 3 == 0)	num_page = num_page / 3;
					else	num_page = num_page / 3 + 1;
				}
			}
			else
			{
				char title[] = "��ʽ����";
				char text[4][50];
				int num = 0;
				if (!judge[0])	sprintf(text[num++], "��ʼʱ���ʽ����");
				if (!judge[1])	sprintf(text[num++], "����ʱ���ʽ����");
				if (!judge[2])	sprintf(text[num++], "�û�ID��ʽ����");
				if (!judge[3])	sprintf(text[num++], "����ID��ʽ����");
				Popup_Window(250, 200, 300, 200, title, text, num, 1);
			}

			for (int i = 0; i <= 3; i++) {
				judge[i] = true;
			}
		}

		if (Button_Input(50, 30, "��ʼʱ�䣺"))
		{
			choose = 1;
			Is_Input = true;
		}
		if (Button_Input(50, 100, "����ʱ�䣺"))
		{
			choose = 2;
			Is_Input = true;
		}
		if(Button_Input(350, 30, "�û�ID��"))
		{
			choose = 3;
			Is_Input = true;
		}
		if (Button_Input(350, 100, "����ID��"))
		{
			choose = 4;
			Is_Input = true;
		}

		if (p_head_order == NULL)
		{
			outtextxy(300, 200, "���޶���");
		}
		else
		{
			p_now_order = p_head_order->next;
			for (int i = 1; i < page; i++) {
				for (int j = 1; j <= 3; j++) {
					if (p_now_order == NULL)	break;
					p_now_order = p_now_order->next;
				}
			}

			for (int i = 1; i <= 3; i++)
			{
				if (p_now_order == NULL)	break;
				if (Button_Order(125, 200 + (i - 1) * 80, p_now_order))
				{
					char title[] = "������Ϣ";
					char text[7][50];
					sprintf(text[0], "������ţ�%s", p_now_order->order_id);
					sprintf(text[1], "�����ţ�%s", p_now_order->room_id);
					sprintf(text[2], "�û����֤�ţ�%s", p_now_order->client_id);
					sprintf(text[3], "��סʱ�䣺%d��%d��%d��", p_now_order->start.year, p_now_order->start.month, p_now_order->start.day);
					sprintf(text[4], "�˷�ʱ�䣺%d��%d��%d��", p_now_order->end.year, p_now_order->end.month, p_now_order->end.day);
					sprintf(text[5], "�����۸�%.2lf", p_now_order->price);
					sprintf(text[6], "�û����ۣ�%d��", p_now_order->remark.star);
					Popup_Window(250, 200, 300, 200, title, text, 7, 1);
				}

				p_now_order = p_now_order->next;
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
			Run_AdminMainMenu();
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(1);
	}
}

void Run_Search_Client()			//�����û�
{
	PClient p_now_client = P_Head_Client->next;
	int page = 1;
	int num_page = 0;

	PClient p_head_client = NULL;

	PText client_id = (PText)malloc(sizeof(Text));
	PText client_name = (PText)malloc(sizeof(Text));
	Init_text(client_id, 166, 320, 35, 65, 650);
	Init_text(client_name, 465, 610, 35, 65, 650);
	bool Is_Input = false;
	int choose = 0;
	wchar_t key = 0;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

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
						Append_Text(client_id, key);
					}
					else if (choose == 2) {
						Append_Text(client_name, key);
					}
				}
			}
		}

		cleardevice();

		settextstyle(20, 0, "Verdana");		//��ӡ�ı�
		setlinecolor(WHITE);
		outtextxy(client_id->x1, client_id->y1 + (client_id->y2 - client_id->y1 - 19) / 2, client_id->text);
		outtextxy(client_name->x1, client_name->y1 + (client_name->y2 - client_name->y1 - 19) / 2, client_name->text);

		if (Is_Input && choose == 1) {			//��ӡ���
			Draw_Fps(client_id);
		}
		else if (Is_Input && choose == 2) {
			Draw_Fps(client_name);
		}

		line(166, 60, 320, 60);				//��ӡ����
		line(465, 60, 610, 60);

		if (Button(680, 30, "����"))
		{
			if (p_head_client != NULL)
			{
				Destroy_Linklist(p_head_client);
				p_head_client = NULL;
			}	

			if (client_id->text[0] != '\0' && client_name->text[0] == '\0') {		//�����û����֤�Ų���
				p_head_client = Search_Client_By_Clientid(client_id->text);
			}
			else if (client_id->text[0] == '\0' && client_name->text[0] != '\0') {		//�����û���������
				p_head_client = Blur_Search_By_Name(client_name->text);
			}
			else if (client_id->text[0] != '\0' && client_name->text[0] != '\0') {			//�����û����֤�� & ��������
				//p_head_client = Search_Order_By_Clientid(client_id->text);
			}

			if (p_head_client != NULL)
			{
				p_now_client = p_head_client->next;
				num_page = 0;

				while (p_now_client != NULL) {			//����ҳ��
					num_page++;
					p_now_client = p_now_client->next;
				}
				if (num_page % 3 == 0)	num_page = num_page / 3;
				else	num_page = num_page / 3 + 1;
			}
		}

		if (Button_Input(50, 30, "���֤�ţ�"))
		{
			choose = 1;
			Is_Input = true;
		}
		if (Button_Input(350, 30, "�û�������"))
		{
			choose = 2;
			Is_Input = true;
		}

		if (p_head_client == NULL || p_head_client->next == NULL)
		{
			outtextxy(300, 125, "�����û�");
		}
		else
		{
			p_now_client = p_head_client->next;
			for (int i = 1; i < page; i++) {
				for (int j = 1; j <= 3; j++) {
					if (p_now_client == NULL)	break;
					p_now_client = p_now_client->next;
				}
			}

			for (int i = 1; i <= 3; i++)
			{
				if (p_now_client == NULL)	break;
				if (Button_Client(125, 125 + (i - 1) * 80, p_now_client))
				{
					char title[] = "�û���Ϣ";
					char text[7][50];
					if (p_now_client->gender == true) {
						sprintf(text[0], "%s����", p_now_client->name);
					}
					else {
						sprintf(text[0], "%sŮʿ", p_now_client->name);
					}
					sprintf(text[1], "���֤�ţ�%s", p_now_client->id);
					sprintf(text[2], "�绰���룺%s", p_now_client->phone);
					sprintf(text[3], "VIP�ȼ���%d", p_now_client->VIP);
					sprintf(text[4], "����������%d", p_now_client->num_bill);
					sprintf(text[5], "���ѽ�%.2lf", p_now_client->pay);
					Popup_Window(250, 200, 300, 200, title, text, 6, 1);
				}
				p_now_client = p_now_client->next;
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
			Run_AdminMainMenu();
			return;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(1);
		
	}
}