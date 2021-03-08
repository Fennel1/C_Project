
#include "functions.h"

MOUSEMSG M_msg;				// �����Ϣ\

PClient P_Head_Client;		//�û�����
PClient P_Now_Client;

POrder P_Head_Order;		//��ʱ������Ķ���
POrder P_Now_Order;

PRoom P_Head_Room;
PRoom P_Now_Room;

void Init()
{
	initgraph(SCREEN_W, SCREEN_H);	

	setbkcolor(RGB(50, 50, 50));
	cleardevice();

	setbkmode(TRANSPARENT);

	P_Head_Client = NULL;		//�û�����
	P_Now_Client = NULL;

	P_Head_Order = NULL;		//��ʱ������Ķ���
	P_Now_Order = NULL;

	P_Head_Room = NULL;
	P_Now_Room = NULL;

}

bool Button(int a, int b, const wchar_t str[])
{
	static int x, y;
	
	setfillcolor(RGB(100, 100, 100));				//���Ʊ߿�
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 25 && (size_t)x < a + 19  *wcslen(str) + 25 && y > b && y < b + 30)		//�жϸ�����ʾ
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
	outtextxy(a, b+3, str);

	return false;
}