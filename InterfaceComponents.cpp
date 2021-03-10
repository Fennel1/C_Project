
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

void Draw_Calendar(int *year, int *month)
{	
	int LeapYear[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int NoLeapYear[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int days = 0;

	for (int i = YEAR; i < *year; i++) {
		for (int j = MONTH; j < *month; j++) {
			if ((i % 400 == 0) || (i % 4 == 0 && i % 100 != 0)) {
				days += LeapYear[j];
			}
			else{
				days += NoLeapYear[j];
			}
		}
	}

	if (Button(170, 150, "<<")) {
		(*year)--;
	}

	if (Button(230, 150, "<")) {
		if (*month > 1) {
			(*month)--;
		}
		else {
			(*year)--;
			*month = 12;
		}
	}

	if (Button(450, 150, ">")) {
		if (*month < 11) {
			(*month)++;
		}
		else {
			(*year)++;
			*month = 1;
		}
	}

	if (Button(500, 150, ">>")) {
		(*year)++;
	}

	int x = 200, y = 150;
	for (int week = 0; week <= 5; week++) {
		for (int day = 0; day <= 6; day++) {
			days++;
			if ((*year % 400 == 0) || (*year % 4 == 0 && *year % 100 != 0))
			{
				if (Button_Calendar(y + day * 60, x + week * 60, days % LeapYear[*month]))
				{

				}
			}
			else
			{
				if (Button_Calendar(y + day * 60, x + week * 60, days % NoLeapYear[*month]))
				{

				}
			}
		}
	}
}