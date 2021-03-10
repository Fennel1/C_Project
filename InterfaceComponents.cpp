
#include "functions.h"

bool Button(int a, int b, const char str[])			//»ù±¾°´Å¥Ä£×é
{
	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//»æÖÆ±ß¿ò
	solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 15 && (size_t)x < a + 9 * strlen(str) + 20 && y > b && y < b + 30)		//ÅÐ¶Ï¸ßÁÁÏÔÊ¾
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

		if (M_msg.uMsg == WM_LBUTTONUP)		//¼ì²âÊó±êµã»÷
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//»æÖÆÎÄ×Ö
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "Î¢ÈíÑÅºÚ Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return false;
}

bool Button_Calendar(int a, int b, int day)			//ÈÕÀúÄ£×é
{
	char days[][5] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15",
					"16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31" };

	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//»æÖÆ±ß¿ò
	solidrectangle(a, b, a + 49, b + 49);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a  && x < a + 49 && y > b && y < b + 49)	//ÅÐ¶Ï¸ßÁÁÏÔÊ¾
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a, b, a + 49, b + 49);

		if (M_msg.uMsg == WM_LBUTTONUP)		//¼ì²âÊó±êµã»÷
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//»æÖÆÎÄ×Ö
	gettextstyle(&t);
	t.lfHeight = 20;
	strcpy(t.lfFaceName, "Î¢ÈíÑÅºÚ Light");
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

bool Button_Input(int a, int b, const char str[])			//ÊäÈë°´Å¥Ä£×é
{
	static int x, y;

	setfillcolor(RGB(100, 100, 100));				//»æÖÆ±ß¿ò
	solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

	x = M_msg.x;
	y = M_msg.y;

	if (x > a - 15 && (size_t)x < a + 9 * strlen(str) + 170 && y > b && y < b + 30)		//ÅÐ¶Ï¸ßÁÁÏÔÊ¾
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 15, b, a + 9 * strlen(str) + 20, b + 30);

		if (M_msg.uMsg == WM_LBUTTONUP && x > a - 15 && (size_t)x < a + 9 * strlen(str) + 170 && y > b && y < b + 30)		//¼ì²âÊó±êµã»÷
		{
			M_msg.uMsg = WM_MOUSEMOVE;
			return true;
		}
	}

	LOGFONT t;			//»æÖÆÎÄ×Ö
	gettextstyle(&t);
	t.lfHeight = 25;
	strcpy(t.lfFaceName, "Î¢ÈíÑÅºÚ Light");
	t.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&t);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return false;
}

void Draw_Calendar(int year, int month, int choose)
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
						
					}
				}
				else
				{
					if (cnt == NoLeapYear[month]+1) {
						return;
					}
					if (Button_Calendar(x + day * 60, y + week * 60, days % (NoLeapYear[month] + 1)))
					{

					}
				}
			}
		}
	}
}