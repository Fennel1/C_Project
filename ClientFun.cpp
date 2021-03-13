
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表
extern PClient P_Now_Client;

extern POrder P_Head_Order;		//以时间排序的订单
extern POrder P_Now_Order;

extern PRoom P_Head_Room;
extern PRoom P_Now_Room;


bool Checkid(char id[])			//检查id
{
	if (id[18] != '\0')
		return false;
	if (id[17] != 'X' || id[17] < '0' || id[17]>'9')
		return false;
	for (int i = 0; i < 17; i++)
	{
		if (id[i] < '0' || id[i]>'9')
			return false;

	}
	PClient temp = P_Head_Client->next;
	while (temp != NULL)
	{
		if (strcmp(temp->id, id) == 0)
			return false;
		temp = temp->next;
	}
	
	return true;
}

bool Checkphone(char phone[])		//检查电话
{
	if (phone[11] != '\0')
		return false;
	for (int i = 0; i < 11; i++)
	{
		if (phone[i] < '0' || phone[i]>'9')
			return false;

	}
	PClient temp = P_Head_Client->next;
	while (temp != NULL)
	{
		if (strcmp(temp->phone, phone) == 0)
			return false;
		temp = temp->next;
	}
	return true;
}

PClient Register(char id[], char password[], char name[], char phone[])		//用户注册
{
	FILE* fp;
	fp = fopen("client.txt", "a");
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
	newtemp->num_bill = 0;
	newtemp->pay = 0;
	newtemp->head_order = NULL;
	newtemp->next = NULL;
	fprintf(fp, "%s %s %s %s %d %d %d %d\n", newtemp->id, newtemp->password, newtemp-> name, newtemp->phone,
		newtemp->gender, newtemp->VIP, newtemp->num_bill, newtemp->pay);
	fclose(fp);
	return P_Now_Client;
}

PClient Login(char id[], char password[])		//用户登录
{
	PClient temp = P_Head_Client->next;
	while (temp != NULL)
	{
		if ((strcmp(temp->id, id) == 0)&&(strcmp(temp->password , password)==0))
			return temp;
		temp = temp->next;
	}
	return NULL;
}

PClient Misspw(char id[], char password[], char name[], char phone[])		//找回密码
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

void Setnpw(PClient client, char password[])			//设置新密码
{
	PClient temp = client;
	strcpy(temp->password, " ");
	strcpy(temp->password, password);

}