
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表

extern POrder P_Head_Order;		//以时间排序的订单

extern PRoom P_Head_Room;


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
	PRoom p_now_room = P_Head_Room->next;
	//遍历订单，改变is_use的值
	POrder p_now_order = P_Head_Order->next;

	while (p_now_room != NULL)		//重置
	{
		p_now_room->Is_Use = false;
		p_now_room = p_now_room->next;
	}

	while (p_now_order != NULL)
	{
		//判断：start或end在已有订单起止时间之内，is_use改为true
		if ((Judge_time(p_now_order->start, start) == 1 && Judge_time(start, p_now_order->end) == 1) || (Judge_time(p_now_order->start, end) == 1 && Judge_time(end, p_now_order->end) == 1))
		{
			p_now_room = P_Head_Room->next;
			while (p_now_room != NULL)
			{
				if (strcmp(p_now_room->id, p_now_order->room_id) == 0)
				{
					p_now_room->Is_Use = true;
					break;
				}
				p_now_room = p_now_room->next;
			}
		}
		p_now_order = p_now_order->next;
	}

	//遍历房间，如果is_use为false，空房间数+1
	p_now_room = P_Head_Room->next;
	while (p_now_room != NULL)
	{
		if (p_now_room->type == A1 && p_now_room->Is_Use == false)	rooms[0]++;
		else if (p_now_room->type == A2 && p_now_room->Is_Use == false)	rooms[1]++;
		else if (p_now_room->type == B1 && p_now_room->Is_Use == false)	rooms[2]++;
		else if (p_now_room->type == B2 && p_now_room->Is_Use == false)	rooms[3]++;
		p_now_room = p_now_room->next;
	}
	return rooms;
}

bool Judge_time(Time a, Time b)
{
	if (a.year > b.year)	return false;
	else if (a.year == b.year && a.month > b.month)	return false;
	else if (a.year == b.year && a.month == b.month && a.day > b.day)	return false;
	else	return true;
}


POrder Add_Order(PClient client, Room_Type type, Time start, Time end)
{
	//链表头插法
	POrder p_this_order = (Order*)malloc(sizeof(Order));

	if (P_Head_Order->next == NULL) {
		sprintf(p_this_order->order_id, "%d", 1);
		strcpy(p_this_order->client_id, client->id);
	}
	else {
		POrder p_now_order = P_Head_Order->next;
		while (p_now_order->next != NULL) {
			p_now_order = p_now_order->next;
		}
		strcpy(p_this_order->client_id, client->id);
		//id相比之前的订单+1
		int int_id = 0;
		sscanf(p_now_order->order_id, "%d", &int_id);
		int_id++;
		sprintf(p_this_order->order_id, "%d", int_id);
	}
	
	//遍历房间，找到可用房间，匹配room_id, price
	PRoom p_now_room = P_Head_Room->next;
	while (p_now_room != NULL)
	{
		if (p_now_room->Is_Use == false && p_now_room->type == type)
		{
			strcpy(p_this_order->room_id, p_now_room->id);
			p_this_order->price = p_now_room->price;
			break;
		}
		p_now_room = p_now_room->next;
	}
	//order其他的值
	p_this_order->type = type;
	p_this_order->start.year = start.year;
	p_this_order->start.month = start.month;
	p_this_order->start.day = start.day;
	p_this_order->start.weekday = start.weekday;
	p_this_order->start.hour = start.hour;
	p_this_order->end.year = end.year;
	p_this_order->end.month = end.month;
	p_this_order->end.day = end.day;
	p_this_order->end.weekday = end.weekday;
	p_this_order->end.hour = end.hour;
	strcpy(p_this_order->remark.message, "");
	p_this_order->remark.star = 0;
	//返回值
	return p_this_order;
}

void Add_In_Linklist(POrder p_this_order, PClient client)
{
	client->num_bill++;
	client->pay += p_this_order->price;

	POrder p_temp_order = (Order*)malloc(sizeof(Order));
	POrder p_now_order = P_Head_Order;
	//将节点加入总订单中（尾插）
	
	if (p_now_order->next == NULL)
	{
		strcpy(p_temp_order->client_id, p_this_order->client_id);
		strcpy(p_temp_order->order_id, p_this_order->order_id);
		strcpy(p_temp_order->room_id, p_this_order->room_id);
		p_temp_order->type = p_this_order->type;
		p_temp_order->price = p_this_order->price;
		p_temp_order->start.year = p_this_order->start.year;
		p_temp_order->start.month = p_this_order->start.month;
		p_temp_order->start.day = p_this_order->start.day;
		p_temp_order->start.weekday = p_this_order->start.weekday;
		p_temp_order->start.hour = p_this_order->start.hour;
		p_temp_order->end.year = p_this_order->end.year;
		p_temp_order->end.month = p_this_order->end.month;
		p_temp_order->end.day = p_this_order->end.day;
		p_temp_order->end.weekday = p_this_order->end.weekday;
		p_temp_order->end.hour = p_this_order->end.hour;
		strcpy(p_temp_order->remark.message, p_this_order->remark.message);
		p_temp_order->remark.star = p_this_order->remark.star;
		p_temp_order->next = NULL;
		p_now_order->next = p_temp_order;
	}
	else
	{
		while (p_now_order->next != NULL)
		{
			p_now_order = p_now_order->next;
		}
		strcpy(p_temp_order->client_id, p_this_order->client_id);
		strcpy(p_temp_order->order_id, p_this_order->order_id);
		strcpy(p_temp_order->room_id, p_this_order->room_id);
		p_temp_order->type = p_this_order->type;
		p_temp_order->price = p_this_order->price;
		p_temp_order->start.year = p_this_order->start.year;
		p_temp_order->start.month = p_this_order->start.month;
		p_temp_order->start.day = p_this_order->start.day;
		p_temp_order->start.weekday = p_this_order->start.weekday;
		p_temp_order->start.hour = p_this_order->start.hour;
		p_temp_order->end.year = p_this_order->end.year;
		p_temp_order->end.month = p_this_order->end.month;
		p_temp_order->end.day = p_this_order->end.day;
		p_temp_order->end.weekday = p_this_order->end.weekday;
		p_temp_order->end.hour = p_this_order->end.hour;
		strcpy(p_temp_order->remark.message, p_this_order->remark.message);
		p_temp_order->remark.star = p_this_order->remark.star;
		p_temp_order->next = NULL;
		p_now_order->next = p_temp_order;
	}
	
	//节点加入到用户订单链表中
	
	p_temp_order = (Order*)malloc(sizeof(Order));
	p_now_order = client->head_order;
	if (p_now_order->next == NULL)
	{
		strcpy(p_temp_order->client_id, p_this_order->client_id);
		strcpy(p_temp_order->order_id, p_this_order->order_id);
		strcpy(p_temp_order->room_id, p_this_order->room_id);
		p_temp_order->type = p_this_order->type;
		p_temp_order->price = p_this_order->price;
		p_temp_order->start.year = p_this_order->start.year;
		p_temp_order->start.month = p_this_order->start.month;
		p_temp_order->start.day = p_this_order->start.day;
		p_temp_order->start.weekday = p_this_order->start.weekday;
		p_temp_order->start.hour = p_this_order->start.hour;
		p_temp_order->end.year = p_this_order->end.year;
		p_temp_order->end.month = p_this_order->end.month;
		p_temp_order->end.day = p_this_order->end.day;
		p_temp_order->end.weekday = p_this_order->end.weekday;
		p_temp_order->end.hour = p_this_order->end.hour;
		strcpy(p_temp_order->remark.message, p_this_order->remark.message);
		p_temp_order->remark.star = p_this_order->remark.star;
		p_temp_order->next = NULL;
		p_now_order->next = p_temp_order;
	}
	else
	{
		while (p_now_order->next != NULL)
		{
			p_now_order = p_now_order->next;
		}
		strcpy(p_temp_order->client_id, p_this_order->client_id);
		strcpy(p_temp_order->order_id, p_this_order->order_id);
		strcpy(p_temp_order->room_id, p_this_order->room_id);
		p_temp_order->type = p_this_order->type;
		p_temp_order->price = p_this_order->price;
		p_temp_order->start.year = p_this_order->start.year;
		p_temp_order->start.month = p_this_order->start.month;
		p_temp_order->start.day = p_this_order->start.day;
		p_temp_order->start.weekday = p_this_order->start.weekday;
		p_temp_order->start.hour = p_this_order->start.hour;
		p_temp_order->end.year = p_this_order->end.year;
		p_temp_order->end.month = p_this_order->end.month;
		p_temp_order->end.day = p_this_order->end.day;
		p_temp_order->end.weekday = p_this_order->end.weekday;
		p_temp_order->end.hour = p_this_order->end.hour;
		strcpy(p_temp_order->remark.message, p_this_order->remark.message);
		p_temp_order->remark.star = p_this_order->remark.star;
		p_temp_order->next = NULL;
		p_now_order->next = p_temp_order;
	}
	
}

void Add_Remark_In_Order(POrder order, Remark remark)
{
	strcpy(order->remark.message, remark.message);
	order->remark.star = remark.star;
}

void Delete_Node(POrder this_order, PClient client)//删除节点
{
	//取得订单的id值
	char ID[10];
	strcpy(ID, this_order->order_id);

	//1.在用户订单中删除此节点

	
	POrder p_now = client->head_order->next;
	POrder p2 = NULL;
	if (p_now == NULL)//链表为空
	{
		return;
	}
	//找到需要被删除的节点（id值唯一）
	while (p_now->next != NULL && strcmp(p_now->order_id, ID) != 0)
	{
		p2 = p_now;
		p_now = p_now->next;
	}
	if (strcmp(p_now->order_id, ID) == 0)
	{
		if (client->head_order->next == p_now)
		{
			client->head_order->next = p_now->next;
		}
		else
		{
			p2->next = p_now->next;
			free(p_now);
		}
	}
	else//找不到这个节点
	{
		return;
	}
	

	//2.在总订单链表中删除此节点
	
	p_now = P_Head_Order->next;
	p2 = NULL;
	if (p_now == NULL)
	{
		return;
	}
	while (p_now->next != NULL && strcmp(p_now->order_id, ID) != 0)
	{
		p2 = p_now;
		p_now = p_now->next;
	}
	if (strcmp(p_now->order_id, ID) == 0)
	{
		if (P_Head_Order->next == p_now)
		{
			P_Head_Order->next = p_now->next;
		}
		else
		{
			p2->next = p_now->next;
			free(p_now);
		}
	}
	else
	{
		return;
	}
	
}