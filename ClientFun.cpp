
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//以时间排序的订单
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;

PClient Register(char id[], char password[], char name[], char phone[])
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