
#include "functions.h"

MOUSEMSG M_msg;				// �����Ϣ

void Init()
{
	initgraph(SCREEN_W, SCREEN_H);	

	setbkcolor(RGB(50, 50, 50));
	cleardevice();

	setbkmode(TRANSPARENT);
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