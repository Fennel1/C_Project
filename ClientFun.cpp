
#include "functions.h"

extern MOUSEMSG M_msg;				// �����Ϣ

extern PClient P_Head_Client;		//�û�����
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//��ʱ������Ķ���
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;

PClient Register(char id[], char password[], char name[], char phone[])		//�û�ע��
{
	PClient temp = P_Head_Client->next;
	while (temp != NULL)
	{
		if (strcmp(temp->id, id) == 0)
			return NULL;
		temp = temp->next;
	}
	PClient newtemp = (PClient)malloc(sizeof(Client));
	strcpy(newtemp->id, id);
	strcpy(newtemp->password, password);
	strcpy(newtemp->name, name);
	strcpy(newtemp->phone, phone);
	int sex = id[16] - '0';
	if ((sex % 2) == 0)
		newtemp->gender = false;
	else newtemp->gender = true;
	newtemp->VIP = 0;
	newtemp->head_order = NULL;
	newtemp->next = NULL;
	newtemp->num_bill = 0;
	newtemp->pay = 0;
	P_Now_Client->next = newtemp;
	P_Now_Client = newtemp;

	return P_Now_Client;
}

PClient Login(char id[], char password[])		//�û���¼
{
	PClient temp = P_Head_Client->next;
	while (temp != NULL)
	{
		if ((strcmp(temp->id, id) == 0) && (strcmp(temp->password, password) == 0))
			return temp;
		temp = temp->next;
	}
	return NULL;
}

PClient MissPassword(char id[], char password[], char name[], char phone[])		//�һ�����
{
	PClient temp = P_Head_Client->next;
	while (temp != NULL)
	{
		if ((strcmp(temp->id, id) == 0) && (strcmp(temp->password, password) == 0) &&
			(strcmp(temp->name, name) == 0) && (strcmp(temp->phone, phone) == 0))
			return temp;

		temp = temp->next;
	}
	return NULL;
}

void SetNewPassword(PClient client, char password[])			//����������
{
	PClient temp = client;
	strcpy(temp->password, " ");
	strcpy(temp->password, password);

}