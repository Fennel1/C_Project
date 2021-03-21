
#include "functions.h"

void Init_text(PText t, int x1, int x2, int y1, int y2, int fps)
{
	t->x1 = x1;
	t->x2 = x2;
	t->y1 = y1;
	t->y2 = y2;
	t->text[0] = '\0';
	t->len = 0;
	t->fps = fps;
}

wchar_t Input_Text()		//ºÏ≤‚º¸≈Ã ‰»Î
{
	wchar_t c = 0;

	if (_kbhit())
	{
		c = _getch();
		if (c == ' ')	c = 0;		//œﬁ÷∆ø’∏Ò
	}
	return c;
}

void Append_Text(PText t, char c)		//–ﬁ∏ƒ◊÷∑˚¥Æ
{
	if (c != 8)
	{
		if (t->len < 99)
		{
			t->text[t->len] = c;
			t->text[t->len + 1] = '\0';
			t->len++;
		}
	}
	else
	{
		if (t->len > 0)
		{
			t->len--;
			t->text[t->len] = '\0';
		}
	}
}

void Draw_Text(PText t)					//ªÊ÷∆◊÷∑˚¥Æ
{
	settextstyle(20, 0, "Verdana");

	setlinecolor(WHITE);
	rectangle(t->x1, t->y1, t->x2, t->y2);

	outtextxy(t->x1 + 5, t->y1 + (t->y2 - t->y1 - 19) / 2, t->text);

	static int fps = 0;
	fps++;
	if (fps < (t->fps / 4))
	{
		setlinecolor(WHITE);
		int lx = t->x1 + 5 + textwidth(t->text);
		line(lx, t->y1 + (t->y2 - t->y1 - 19) / 2, lx, t->y1 + (t->y2 - t->y1 - 19) / 2 + 20);
	}
	else if (fps > (t->fps / 2))
	{
		fps = 0;
	}
}

void Draw_Fps(PText t)					//¥Ú”°π‚±Í
{
	static int fps = 0;
	fps++;
	if (fps < (t->fps / 4))
	{
		setlinecolor(WHITE);
		int lx = t->x1 + 5 + textwidth(t->text);
		line(lx, t->y1 + (t->y2 - t->y1 - 19) / 2, lx, t->y1 + (t->y2 - t->y1 - 19) / 2 + 20);
	}
	else if (fps > (t->fps / 2))
	{
		fps = 0;
	}
}

void Empty_Text(PText t)				//«Âø’◊÷∑˚¥Æ
{
	t->len = 0;
	t->text[0] = '\0';
}