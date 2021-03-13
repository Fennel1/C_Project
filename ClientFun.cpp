
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
	if ((id[17] != 'X'||id[17]!='x' )&&( id[17] < '0' || id[17]>'9'))
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

bool Checkpassword(char password[])		//检查密码格式
{

	for (int i = 0; i < strlen(password); i++)
	{
		if (password[i] < 21 || password[i]> 126)
			return false;

	}

	return true;
}

bool Checkrepassword(char password[], char repassword[])		//确认密码
{
	if (strcmp(password, repassword) == 0)
		return false;

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
	return newtemp;
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

PClient MissPassword(char id[], char password[], char name[], char phone[])		//找回密码
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

void SetNewPassword(PClient client, char password[])			//设置新密码
{
	PClient temp = client;
	strcpy(temp->password, " ");
	strcpy(temp->password, password);

}

int* Display_rooms_number(int* rooms, Time start, Time end)//返回四种空房间的个数
{
	//建立房间的链表
	PRoom p_head_room = Room_Init();
	PRoom p_now_room = p_head_room->next;
	//遍历订单，改变is_use的值
	POrder p_head_order = Order_Init();
	POrder p_now_order = p_head_order->next;
	while (p_now_order != NULL)
	{
		//判断：start或end在已有订单起止时间之内，is_use改为true
		if ((Judge_time(p_now_order->start, start) == 1 && Judge_time(start, p_now_order->end) == 1) || (Judge_time(p_now_order->start, end) == 1 && Judge_time(end, p_now_order->end) == 1))
		{
			while (p_now_room != NULL)
			{
				if (p_now_room->id == p_now_order->room_id)
				{
					p_now_room->Is_Use = 1;
					break;
				}
			}
		}
	}
	//遍历房间，如果is_use为false，空房间数+1
	while (p_now_room != NULL)
	{
		if (p_now_room->type == 0 && p_now_room->Is_Use == 0)rooms[0]++;
		else if (p_now_room->type == 1 && p_now_room->Is_Use == 0)rooms[1]++;
		else if (p_now_room->type == 2 && p_now_room->Is_Use == 0)rooms[2]++;
		else if (p_now_room->type == 3 && p_now_room->Is_Use == 0)rooms[3]++;
		p_now_room = p_now_room->next;
	}
	return rooms;
}

bool Judge_time(Time a, Time b)
{
	if (a.year < b.year)return true;
	else if (a.month < b.month)return true;
	else if (a.day < b.day)return true;
	return false;
}
