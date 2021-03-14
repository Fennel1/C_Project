
#include "functions.h"

extern MOUSEMSG M_msg;				// �����Ϣ\

extern PClient P_Head_Client;		//�û�����

extern POrder P_Head_Order;		//��ʱ������Ķ���

extern PRoom P_Head_Room;

bool Button(int a, int b, const char str[])			//������ťģ��
{
	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//���Ʊ߿�
	solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 15 && (size_t)x < a + 9 * strlen(str) + 20 && y > b && y < b + 30)		//�жϸ�����ʾ
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

		if (M_msg.uMsg == WM_LBUTTONUP)		//��������
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//��������
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "΢���ź� Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return false;
}

bool Button_Input(int a, int b, const char str[])			//���밴ťģ��
{
	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//���Ʊ߿�
	solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 15 && (size_t)x < a + 9 * strlen(str) + 170 && y > b && y < b + 30)		//�жϸ�����ʾ
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

		if (M_msg.uMsg == WM_LBUTTONUP && x > a - 15 && (size_t)x < a + 9 * strlen(str) + 170 && y > b && y < b + 30)		//��������
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//��������
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "΢���ź� Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return false;
}

void Draw_Calendar(int year, int month, PClient client)
{	
	int LeapYear[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int NoLeapYear[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int days = 0;

	if (month == 1 || month == 2) 
	{
		month += 12;
		year--;
	}

	bool flag = false;
	int weekday = (1 + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	int x = 205, y = 200;
	int cnt = 0;

	if (month == 13 || month == 14)
	{
		month -= 12;
		year++;
	}

	for (int week = 0; week <= 5; week++) {
		for (int day = 0; day <= 6; day++) {
			if (day == weekday) {
				flag = true;
			}
			if (flag)
			{
				cnt++;
				days++;
				if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
				{
					if (cnt == LeapYear[month]+1) {
						return;
					}
					if (Button_Calendar(x + day * 60, y + week * 60, days % (LeapYear[month] + 1)))
					{
						FlushBatchDraw();
						cleardevice();
						ReCommit_Order(client, year, month, days);
						return;
					}
				}
				else
				{
					if (cnt == NoLeapYear[month]+1) {
						return;
					}
					if (Button_Calendar(x + day * 60, y + week * 60, days % (NoLeapYear[month] + 1)))
					{
						FlushBatchDraw();
						cleardevice();
						ReCommit_Order(client, year, month, days);
						return;
					}
				}
			}
		}
	}
}

void reDraw_Calendar(int year, int month, int s_year, int s_month, int s_day, PClient client)
{
	int LeapYear[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int NoLeapYear[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int days = 0;

	if (month == 1 || month == 2)
	{
		month += 12;
		year--;
	}

	bool flag = false;
	int weekday = (1 + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	int x = 205, y = 200;
	int cnt = 0;

	if (month == 13 || month == 14)
	{
		month -= 12;
		year++;
	}

	for (int week = 0; week <= 5; week++) {
		for (int day = 0; day <= 6; day++) {
			if (day == weekday) {
				flag = true;
			}
			if (flag)
			{
				cnt++;
				days++;
				if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
				{
					if (cnt == LeapYear[month] + 1) {
						return;
					}
					if (year == s_year && month == s_month && days == s_day) 
					{
						setlinecolor(RGB(0, 255, 0));
						rectangle(x + day * 60 - 5, y + week * 60 - 5, x + day * 60 + 55, y + week * 60 + 55);
					}
					if (Button_Calendar(x + day * 60, y + week * 60, days % (LeapYear[month] + 1)))
					{
						char title[] = "ȷ�ϵ�ǰ������";
						char text[2][50];
						sprintf(text[0], "��סʱ�䣺%d��%d��%d��", s_year, s_month, s_day);
						sprintf(text[1], "�˷�ʱ�䣺%d��%d��%d��", year, month, days);
						if (Popup_Window(250, 200, 300, 200, title, text, 2, 2))
						{
							Time start = { s_year, s_month, s_day, 0, 0 };
							Time end = { year, month, day, 0, 0 };
							int num[4] = { 0 };
							int* rooms_num = num;
							rooms_num = Display_rooms_number(num, start, end);
							FlushBatchDraw();
							cleardevice();
							Choose_room(client, rooms_num, start, end);
						}
						else
						{
							FlushBatchDraw();
							cleardevice();
							Commit_Order(client);
						}
					}
				}
				else
				{
					if (cnt == NoLeapYear[month] + 1) {
						return;
					}
					if (year == s_year && month == s_month && days == s_day)
					{
						setlinecolor(RGB(0, 255, 0));
						rectangle(x + day * 60 - 5, y + week * 60 - 5, x + day * 60 + 55, y + week * 60 + 55);
					}
					if (Button_Calendar(x + day * 60, y + week * 60, days % (NoLeapYear[month] + 1)))
					{
						char title[] = "ȷ�ϵ�ǰ������";
						char text[2][50];
						sprintf(text[0], "��סʱ�䣺%d��%d��%d��", s_year, s_month, s_day);
						sprintf(text[1], "�˷�ʱ�䣺%d��%d��%d��", year, month, days);
						if (Popup_Window(250, 200, 300, 200, title, text, 2, 2))
						{
							Time start = { s_year, s_month, s_day, 0, 0 };
							Time end = { year, month, day, 0, 0 };
							int num[4] = {0};
							int* rooms_num = num;
							rooms_num = Display_rooms_number(num, start, end);
							FlushBatchDraw();
							cleardevice();
							Choose_room(client, rooms_num, start, end);
						}
						else
						{
							FlushBatchDraw();
							cleardevice();
							Commit_Order(client);
						}
					}
				}
			}
		}
	}
}

bool Button_Calendar(int a, int b, int day)			//����ģ��
{
	char days[][5] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15",
					"16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31" };

	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//���Ʊ߿�
	solidrectangle(a, b, a + 49, b + 49);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a && x < a + 49 && y > b && y < b + 49)	//�жϸ�����ʾ
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a, b, a + 49, b + 49);

		if (M_msg.uMsg == WM_LBUTTONUP)		//��������
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//��������
	gettextstyle(&t);
	t.lfHeight = 20;
	strcpy(t.lfFaceName, "΢���ź� Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	if (day < 10) {
		outtextxy(a + 20, b + 14, days[day]);
	}
	else {
		outtextxy(a + 17, b + 14, days[day]);
	}

	return false;
}

bool Button_Star(int a, int b, int *num, int n, int star)
{
	static int x, y;

	x = M_msg.x;
	y = M_msg.y;
	if (star >= n)
	{
		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 45;
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(a, b, "��");

	}

	if (*num > n)
	{
		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 45;
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(a, b, "��");

	}
	else if (x > a - 15 && x < a + 30 && y > b && y < b + 30)		//�жϸ�����ʾ
	{
		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 45;
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(a, b, "��");

		*num = n;

		if (M_msg.uMsg == WM_LBUTTONUP)		//��������
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}
	else
	{
		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 45;
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(a, b, "��");

		if (*num == n) {
			*num = 0;
		}
	}
	return false;
}

int Popup_Window(int x, int y, int wight, int hight, char title[], char text[][50], int g_num, int var)
{
	setbkmode(TRANSPARENT);

	char c;

	while (true)
	{
		if (_kbhit())									//������Ϣ���
			c = _getch();

		while (MouseHit())
			M_msg = GetMouseMsg();						//�����Ϣ��ȡ

		setfillcolor(RGB(25, 25, 25));
		solidrectangle(x, y, x + wight, y + hight);		//���Ʊ߿�

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 30;
		strcpy(f.lfFaceName, "����");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		outtextxy(x + 20, y + 10, title);

		for (int i = 0; i < g_num; i++)				//�������
		{
			f.lfHeight = 18;
			f.lfQuality = ANTIALIASED_QUALITY;
			settextstyle(&f);
			outtextxy(x + 20, y + 45 + i * 20, text[i]);
		}

		if (var == 1)							//��ť����
		{
			if (Button(x + wight - 70, y + hight - 37, "ȷ��"))
				return 1;
		}
		else if (var == 2)
		{
			if (Button(x + wight - 125, y + hight - 37, "��"))
				return 1;

			if (Button(x + wight - 50, y + hight - 37, "��"))
				return 0;
		}

		FlushBatchDraw();
	}
	return 0;
}