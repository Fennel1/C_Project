
#include "functions.h"

PClient P_Head_Client;		//�û�����
PClient P_Now_Client;

POrder P_Head_Order;		//��ʱ������Ķ���
POrder P_Now_Order;

PRoom P_Head_Room;		//��������
PRoom P_Now_Room;

MOUSEMSG M_msg;

void Init()			//�����ʼ��
{
	initgraph(SCREEN_W, SCREEN_H);	//���ڴ�С

	setbkcolor(RGB(50, 50, 50));	//������ɫ
	cleardevice();

	setbkmode(TRANSPARENT);			//���ñ���Ϊ͸��

	P_Head_Client = NULL;		//�û�����
	P_Now_Client = NULL;

	P_Head_Order = NULL;		//��ʱ������Ķ���
	P_Now_Order = NULL;

	P_Head_Room = NULL;
	P_Now_Room = NULL;
}

void Run_MainMenu()		//������
{
	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		LOGFONT t;			//��������
		gettextstyle(&t);
		t.lfHeight = 75;
		wcscpy_s(t.lfFaceName, L"΢���ź� Light");
		t.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&t);
		settextcolor(WHITE);
		outtextxy(310, 70, L"���˵�");

		if (Button(350, 200, L"���ǹ���Ա"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminLoginMenu();
			return;
		}

		if (Button(360, 300, L"�����û�"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientLoginMenu();
			return;
		}

		if (Button(360, 400, L"����˳�"))
		{
			break;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}

void Exit()			//�˳�����
{
	EndBatchDraw();
	closegraph();
}

bool Button(int a, int b, const wchar_t str[])			//��ťģ��
{
	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//���Ʊ߿�
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30)		//�жϸ�����ʾ
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);

		if (M_msg.uMsg == WM_LBUTTONUP)		//��������
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//��������
	gettextstyle(&t);
	t.lfHeight = 25;
	wcscpy_s(t.lfFaceName, L"΢���ź� Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return false;
}

void test()
{
	PText s = (PText)malloc(sizeof(Text));
	bool Is_Input = false;
	wchar_t key = 0;

	while (true)
	{
		while (MouseHit())		// �����Ϣ��ȡ
			M_msg = GetMouseMsg();

		if (Is_Input)
		{
			key = Input_Text();
			if (key != 0)
			{
				if (key != 13)
				{
					Append_Text(s, key);
				}
				else
				{
					Empty_Text(s);
					Is_Input = false;
					key = 0;
				}
			}
		}

		cleardevice();
		Draw_Text(s);

		if (Is_Input == false && Button(200, 200, L"�������"))
		{
			Init_text(s, 200, 300, 200, 230, 200);

			Is_Input = true;
		}

		if (Button(400, 200, L"����˳�"))
		{
			break;
		}

		FlushBatchDraw();
		Sleep(10);
	}
}