
#include "functions.h"

extern MOUSEMSG M_msg;				// �����Ϣ\

extern PClient P_Head_Client;		//�û�����
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//��ʱ������Ķ���
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;

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
		outtextxy(310, 70, "����Ա����");

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