
#include "functions.h"

PClient P_Head_Client;		//�û�����
PClient P_Now_Client;

POrder P_Head_Order;		//��ʱ������Ķ���
POrder P_Now_Order;

PRoom P_Head_Room;		//��������
PRoom P_Now_Room;

MOUSEMSG M_msg;

void Run_MainMenu()		//������
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





