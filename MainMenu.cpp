
#include "functions.h"

extern PClient P_Head_Client;		//�û�����
<<<<<<< HEAD
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//��ʱ������Ķ���
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;
=======

extern POrder P_Head_Order;		//��ʱ������Ķ���

extern PRoom P_Head_Room;
>>>>>>> 7d9156758fbc4c2a843b36efb07bb633e32abab8

MOUSEMSG M_msg;

void Run_MainMenu()		//������
{
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
		outtextxy(310, 70, "���˵�");
		if (Button(350, 200, "���ǹ���Ա"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_AdminLoginMenu();
			return;
		}

		if (Button(360, 300, "�����û�"))
		{
			FlushBatchDraw();
			cleardevice();
			Run_ClientLoginMenu();
			return;
		}

		if (Button(360, 400, "����˳�"))
		{
			break;
		}

		FlushBatchDraw();			// ִ��δ��ɵĻ�������
		Sleep(10);
	}
}