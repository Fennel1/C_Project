
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息

int main() 
{

	Init();
	PText s = (PText)malloc(sizeof(Text));
	bool Is_Input = false;
	wchar_t key = 0;

	while (true)
	{
		while (MouseHit())		// 鼠标消息获取
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

		if (Is_Input == false && Button(200, 200, L"点击输入"))
		{
			Init_text(s, 200, 300, 200, 230, 200);

			Is_Input = true;
		}

		if (Button(400, 200, L"点击退出"))
		{
			break;
		}

		FlushBatchDraw();
		Sleep(10);
	}

	EndBatchDraw();
	closegraph();

	return 0;
}

