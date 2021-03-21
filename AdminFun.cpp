
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表

extern POrder P_Head_Order;			//以时间排序的订单

extern PRoom P_Head_Room;

bool Admin_Login(char id[], char password[])		//管理员登录
{
	if (strcmp(MANAGER_NAME, id) == 0 && strcmp(MANAGER_PASSWORD, password) == 0) {
		return true;
	}
	return false;
}

POrder Sort_Order_Time_Ascending(POrder p_head_order)		//时间升序
{
	POrder p_now_order = p_head_order->next;
	POrder p_start_order = (Order*)malloc(sizeof(Order));
	p_start_order->next = NULL;
	POrder p_new_now_order = p_start_order;
	bool flag;
	while (p_now_order != NULL)
	{
		flag = false;
		POrder p_temp_order = (Order*)malloc(sizeof(Order));
		*p_temp_order = *p_now_order;
		p_temp_order->next = NULL;
		p_new_now_order = p_start_order;
		while (p_new_now_order->next != NULL)
		{
			if (Judge_time(p_now_order->start, p_new_now_order->next->start) == true)
			{
				flag = true;
				p_temp_order->next = p_new_now_order->next;
				p_new_now_order->next = p_temp_order;
				break;
			}
			p_new_now_order = p_new_now_order->next;
		}
		if (flag == false) 
		{
			p_new_now_order->next = p_temp_order;
		}
		p_now_order = p_now_order->next;
	}
	return p_start_order;
}

POrder Sort_Order_Time_Descending(POrder p_head_order)		//时间降序
{
	POrder p_now_order = p_head_order->next;
	POrder p_start_order = (Order*)malloc(sizeof(Order));
	p_start_order->next = NULL;
	POrder p_new_now_order = p_start_order;
	bool flag;
	while (p_now_order != NULL)
	{
		flag = false;
		POrder p_temp_order = (Order*)malloc(sizeof(Order));
		*p_temp_order = *p_now_order;
		p_temp_order->next = NULL;
		p_new_now_order = p_start_order;
		while (p_new_now_order->next != NULL)
		{
			if (Judge_time(p_now_order->start, p_new_now_order->next->start) == false)
			{
				flag = true;
				p_temp_order->next = p_new_now_order->next;
				p_new_now_order->next = p_temp_order;
				break;
			}
			p_new_now_order = p_new_now_order->next;
		}
		if (flag == false)
		{
			p_new_now_order->next = p_temp_order;
		}
		p_now_order = p_now_order->next;
	}
	return p_start_order;
}

POrder Sort_Order_ID_Ascending(POrder p_head_order)		//ID升序
{
	POrder p_now_order = p_head_order->next;
	POrder p_start_order = (Order*)malloc(sizeof(Order));
	p_start_order->next = NULL;
	POrder p_new_now_order = p_start_order;
	bool flag;
	while (p_now_order != NULL)
	{
		flag = false;
		POrder p_temp_order = (Order*)malloc(sizeof(Order));
		*p_temp_order = *p_now_order;
		p_temp_order->next = NULL;
		p_new_now_order = p_start_order;
		while (p_new_now_order->next != NULL)
		{
			if (strcmp(p_now_order->client_id, p_temp_order->client_id) <= 0)
			{
				flag = true;
				p_temp_order->next = p_new_now_order->next;
				p_new_now_order->next = p_temp_order;
				break;
			}
			p_new_now_order = p_new_now_order->next;
		}
		if (flag == false)
		{
			p_new_now_order->next = p_temp_order;
		}
		p_now_order = p_now_order->next;
	}
	return p_start_order;
}

POrder Sort_Order_ID_Descending(POrder p_head_order)		//ID降序
{
	POrder p_now_order = p_head_order->next;
	POrder p_start_order = (Order*)malloc(sizeof(Order));
	p_start_order->next = NULL;
	POrder p_new_now_order = p_start_order;
	bool flag;
	while (p_now_order != NULL)
	{
		flag = false;
		POrder p_temp_order = (Order*)malloc(sizeof(Order));
		*p_temp_order = *p_now_order;
		p_temp_order->next = NULL;
		p_new_now_order = p_start_order;
		while (p_new_now_order->next != NULL)
		{
			if (strcmp(p_now_order->client_id, p_temp_order->client_id) >= 0)
			{
				flag = true;
				p_temp_order->next = p_new_now_order->next;
				p_new_now_order->next = p_temp_order;
				break;
			}
			p_new_now_order = p_new_now_order->next;
		}
		if (flag == false)
		{
			p_new_now_order->next = p_temp_order;
		}
		p_now_order = p_now_order->next;
	}
	return p_start_order;
}

POrder Search_Order_By_Orderid(char id[])
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->order_id, id) == 0) {
			results_temp = (POrder)malloc(sizeof(order));
			strcpy(results_temp->client_id, temp->client_id);
			strcpy(results_temp->order_id, temp->order_id);
			strcpy(results_temp->room_id, temp->room_id);
			results_temp->type = temp->type;
			results_temp->price = temp->price;
			results_temp->start.year = temp->start.year;
			results_temp->start.month = temp->start.month;
			results_temp->start.day = temp->start.day;
			results_temp->start.weekday = temp->start.weekday;
			results_temp->start.hour = temp->start.hour;
			results_temp->end.year = temp->end.year;
			results_temp->end.month = temp->end.month;
			results_temp->end.day = temp->end.day;
			results_temp->end.weekday = temp->end.weekday;
			results_temp->end.hour = temp->end.hour;
			strcpy(results_temp->remark.message, temp->remark.message);
			results_temp->remark.star = temp->remark.star;
			results_temp->next = NULL;
			results_now->next = results_temp;
			results_now = results_temp;
		}
		temp = temp->next;
	}
	return results_head;
}

POrder Search_Order_By_Clientid(char id[])
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->client_id, id) == 0) {
			results_temp = (POrder)malloc(sizeof(order));
			strcpy(results_temp->client_id, temp->client_id);
			strcpy(results_temp->order_id, temp->order_id);
			strcpy(results_temp->room_id, temp->room_id);
			results_temp->type = temp->type;
			results_temp->price = temp->price;
			results_temp->start.year = temp->start.year;
			results_temp->start.month = temp->start.month;
			results_temp->start.day = temp->start.day;
			results_temp->start.weekday = temp->start.weekday;
			results_temp->start.hour = temp->start.hour;
			results_temp->end.year = temp->end.year;
			results_temp->end.month = temp->end.month;
			results_temp->end.day = temp->end.day;
			results_temp->end.weekday = temp->end.weekday;
			results_temp->end.hour = temp->end.hour;
			strcpy(results_temp->remark.message, temp->remark.message);
			results_temp->remark.star = temp->remark.star;
			results_temp->next = NULL;
			results_now->next = results_temp;
			results_now = results_temp;
		}
		temp = temp->next;
	}
	return results_head;
}

POrder Search_Order_By_Roomid(char id[])
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->room_id, id) == 0) {
			results_temp = (POrder)malloc(sizeof(order));
			strcpy(results_temp->client_id, temp->client_id);
			strcpy(results_temp->order_id, temp->order_id);
			strcpy(results_temp->room_id, temp->room_id);
			results_temp->type = temp->type;
			results_temp->price = temp->price;
			results_temp->start.year = temp->start.year;
			results_temp->start.month = temp->start.month;
			results_temp->start.day = temp->start.day;
			results_temp->start.weekday = temp->start.weekday;
			results_temp->start.hour = temp->start.hour;
			results_temp->end.year = temp->end.year;
			results_temp->end.month = temp->end.month;
			results_temp->end.day = temp->end.day;
			results_temp->end.weekday = temp->end.weekday;
			results_temp->end.hour = temp->end.hour;
			strcpy(results_temp->remark.message, temp->remark.message);
			results_temp->remark.star = temp->remark.star;
			results_temp->next = NULL;
			results_now->next = results_temp;
			results_now = results_temp;
		}
		temp = temp->next;
	}
	return results_head;
}

POrder Search_Order_By_Starttime(Time start)
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day) {
			results_temp = (POrder)malloc(sizeof(order));
			strcpy(results_temp->client_id, temp->client_id);
			strcpy(results_temp->order_id, temp->order_id);
			strcpy(results_temp->room_id, temp->room_id);
			results_temp->type = temp->type;
			results_temp->price = temp->price;
			results_temp->start.year = temp->start.year;
			results_temp->start.month = temp->start.month;
			results_temp->start.day = temp->start.day;
			results_temp->start.weekday = temp->start.weekday;
			results_temp->start.hour = temp->start.hour;
			results_temp->end.year = temp->end.year;
			results_temp->end.month = temp->end.month;
			results_temp->end.day = temp->end.day;
			results_temp->end.weekday = temp->end.weekday;
			results_temp->end.hour = temp->end.hour;
			strcpy(results_temp->remark.message, temp->remark.message);
			results_temp->remark.star = temp->remark.star;
			results_temp->next = NULL;
			results_now->next = results_temp;
			results_now = results_temp;
		}
		temp = temp->next;
	}
	return results_head;
}

POrder Search_Order_By_Endtime(Time end)
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day) {
			results_temp = (POrder)malloc(sizeof(order));
			strcpy(results_temp->client_id, temp->client_id);
			strcpy(results_temp->order_id, temp->order_id);
			strcpy(results_temp->room_id, temp->room_id);
			results_temp->type = temp->type;
			results_temp->price = temp->price;
			results_temp->start.year = temp->start.year;
			results_temp->start.month = temp->start.month;
			results_temp->start.day = temp->start.day;
			results_temp->start.weekday = temp->start.weekday;
			results_temp->start.hour = temp->start.hour;
			results_temp->end.year = temp->end.year;
			results_temp->end.month = temp->end.month;
			results_temp->end.day = temp->end.day;
			results_temp->end.weekday = temp->end.weekday;
			results_temp->end.hour = temp->end.hour;
			strcpy(results_temp->remark.message, temp->remark.message);
			results_temp->remark.star = temp->remark.star;
			results_temp->next = NULL;
			results_now->next = results_temp;
			results_now = results_temp;
		}
		temp = temp->next;
	}
	return results_head;
}

POrder Search_Order_By_Time(Time start, Time end)
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day) {
			if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day) {
				results_temp = (POrder)malloc(sizeof(order));
				strcpy(results_temp->client_id, temp->client_id);
				strcpy(results_temp->order_id, temp->order_id);
				strcpy(results_temp->room_id, temp->room_id);
				results_temp->type = temp->type;
				results_temp->price = temp->price;
				results_temp->start.year = temp->start.year;
				results_temp->start.month = temp->start.month;
				results_temp->start.day = temp->start.day;
				results_temp->start.weekday = temp->start.weekday;
				results_temp->start.hour = temp->start.hour;
				results_temp->end.year = temp->end.year;
				results_temp->end.month = temp->end.month;
				results_temp->end.day = temp->end.day;
				results_temp->end.weekday = temp->end.weekday;
				results_temp->end.hour = temp->end.hour;
				strcpy(results_temp->remark.message, temp->remark.message);
				results_temp->remark.star = temp->remark.star;
				results_temp->next = NULL;
				results_now->next = results_temp;
				results_now = results_temp;
			}
		}
		temp = temp->next;
	}
	return results_head;
}

POrder Search_Order_By_OrderidT(char id[], Time start, Time end)
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->order_id, id) == 0) {
			if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day) {
				if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day) {
					results_temp = (POrder)malloc(sizeof(order));
					strcpy(results_temp->client_id, temp->client_id);
					strcpy(results_temp->order_id, temp->order_id);
					strcpy(results_temp->room_id, temp->room_id);
					results_temp->type = temp->type;
					results_temp->price = temp->price;
					results_temp->start.year = temp->start.year;
					results_temp->start.month = temp->start.month;
					results_temp->start.day = temp->start.day;
					results_temp->start.weekday = temp->start.weekday;
					results_temp->start.hour = temp->start.hour;
					results_temp->end.year = temp->end.year;
					results_temp->end.month = temp->end.month;
					results_temp->end.day = temp->end.day;
					results_temp->end.weekday = temp->end.weekday;
					results_temp->end.hour = temp->end.hour;
					strcpy(results_temp->remark.message, temp->remark.message);
					results_temp->remark.star = temp->remark.star;
					results_temp->next = NULL;
					results_now->next = results_temp;
					results_now = results_temp;
				}
			}
		}
		temp = temp->next;
	}
	return results_head;
}

POrder Search_Order_By_ClientidT(char id[], Time start, Time end)
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->client_id, id) == 0) {
			if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day) {
				if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day) {
					results_temp = (POrder)malloc(sizeof(order));
					strcpy(results_temp->client_id, temp->client_id);
					strcpy(results_temp->order_id, temp->order_id);
					strcpy(results_temp->room_id, temp->room_id);
					results_temp->type = temp->type;
					results_temp->price = temp->price;
					results_temp->start.year = temp->start.year;
					results_temp->start.month = temp->start.month;
					results_temp->start.day = temp->start.day;
					results_temp->start.weekday = temp->start.weekday;
					results_temp->start.hour = temp->start.hour;
					results_temp->end.year = temp->end.year;
					results_temp->end.month = temp->end.month;
					results_temp->end.day = temp->end.day;
					results_temp->end.weekday = temp->end.weekday;
					results_temp->end.hour = temp->end.hour;
					strcpy(results_temp->remark.message, temp->remark.message);
					results_temp->remark.star = temp->remark.star;
					results_temp->next = NULL;
					results_now->next = results_temp;
					results_now = results_temp;
				}
			}
		}
		temp = temp->next;
	}
	return results_head;
}

POrder Search_Order_By_RoomidT(char id[], Time start, Time end)
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->room_id, id) == 0) {
			if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day) {
				if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day) {
					results_temp = (POrder)malloc(sizeof(order));
					strcpy(results_temp->client_id, temp->client_id);
					strcpy(results_temp->order_id, temp->order_id);
					strcpy(results_temp->room_id, temp->room_id);
					results_temp->type = temp->type;
					results_temp->price = temp->price;
					results_temp->start.year = temp->start.year;
					results_temp->start.month = temp->start.month;
					results_temp->start.day = temp->start.day;
					results_temp->start.weekday = temp->start.weekday;
					results_temp->start.hour = temp->start.hour;
					results_temp->end.year = temp->end.year;
					results_temp->end.month = temp->end.month;
					results_temp->end.day = temp->end.day;
					results_temp->end.weekday = temp->end.weekday;
					results_temp->end.hour = temp->end.hour;
					strcpy(results_temp->remark.message, temp->remark.message);
					results_temp->remark.star = temp->remark.star;
					results_temp->next = NULL;
					results_now->next = results_temp;
					results_now = results_temp;
				}
			}
		}
		temp = temp->next;
	}
	return results_head;
}

bool Search_Check_Orderid(char id[])
{
	if (id[0] == '\0')	return true;
	int idlen = strlen(id);
	if (id[0] < '1' || id[0]>'9') {
		return false;
	}
	for (int n = 1; n < idlen; n++) {
		if (id[n] < '0' || id[n]>'9') {
			return false;
		}
	}
	return true;
}

bool Search_Check_Clientid(char id[])
{
	if (strcmp(id, "11") == 0)	return true;
	if (id[0] == '\0')	return true;
	int idlen = strlen(id);
	if (idlen != 18) {
		return false;
	}
	if ((id[17] != 'X' && id[17] != 'x') && (id[17] < '0' || id[17]>'9'))
		return false;
	for (int i = 0; i < 17; i++)
	{
		if (id[i] < '0' || id[i]>'9')
			return false;

	}
	return true;
}

bool Search_Check_Roomid(char id[])
{
	if (id[0] == '\0')	return true;
	int idlen = strlen(id);
	if (idlen != 6) {
		return false;
	}
	if (id[0] < 'A' || id[0]>'Z') {
		return false;
	}
	if (id[1] < '0' || id[1]>'9') {
		return false;
	}
	if (id[2] != '_') {
		return false;
	}
	if (id[3] < '0' || id[3]>'9') {
		return false;
	}
	if (id[4] < '0' || id[4]>'9') {
		return false;
	}
	if (id[5] < '0' || id[5]>'9') {
		return false;
	}
	return true;
}

bool Search_Check_Time(char time[])
{
	if (time[0] == '\0')	return true;
	int len = strlen(time);
	if (len != 8) {
		return false;
	}
	for (int i = 0; i < 8; i++)
	{
		if (time[i] < '0' || time[i]>'9')
			return false;

	}
	return true;
}

PClient Search_Client_By_Clientid(char id[])
{

	PClient results_head = (PClient)malloc(sizeof(client));
	PClient results_temp;
	PClient results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	PClient temp = P_Head_Client->next;
	while (temp != NULL) {
		if (strcmp(temp->id, id) == 0) {
			results_temp = (PClient)malloc(sizeof(client));
			strcpy(results_temp->id, temp->id);
			strcpy(results_temp->password, temp->password);
			strcpy(results_temp->name, temp->name);
			strcpy(results_temp->phone, temp->phone);
			results_temp->gender = temp->gender;
			results_temp->VIP = temp->VIP;
			results_temp->num_bill = temp->num_bill;
			results_temp->pay = temp->pay;
			results_temp->head_order = NULL;
			results_temp->next = NULL;
			results_now->next = results_temp;
			results_now = results_temp;
		}
		temp = temp->next;
	}
	return results_head;
}

PClient Blur_Search_By_Name(char name[])
{
	PClient results_head = (PClient)malloc(sizeof(client));
	PClient results_temp;
	PClient results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	PClient temp = P_Head_Client->next;
	int len = strlen(temp->name);
	int checklen = strlen(name);
	char  key[100];

	while (temp != NULL) {

		int i = 0;
		for (; i < len; i++) {
			if (name[0] == temp->name[i]) {
				strncpy(key, temp->name + i, checklen);
				key[checklen] = '\0';
				if (strcmp(key, name) == 0) {
					results_temp = (PClient)malloc(sizeof(client));
					strcpy(results_temp->id, temp->id);
					strcpy(results_temp->password, temp->password);
					strcpy(results_temp->name, temp->name);
					strcpy(results_temp->phone, temp->phone);
					results_temp->gender = temp->gender;
					results_temp->VIP = temp->VIP;
					results_temp->num_bill = temp->num_bill;
					results_temp->pay = temp->pay;
					results_temp->head_order = NULL;
					results_temp->next = NULL;
					results_now->next = results_temp;
					results_now = results_temp;
					break;
				}
			}
		}

		temp = temp->next;
	}
	return results_head;
}

void Delete_Room(PRoom room)
{
	//获得房间id值
	char id[10];
	strcpy(id, room->id);
	PRoom now = P_Head_Room->next;
	PRoom last = NULL;
	if (now == NULL)//链表为空
	{
		return;
	}
	while (now->next != NULL && strcmp(now->id, id) != 0)
	{
		last = now;
		now = now->next;
	}
	if (strcmp(now->id, id) == 0)
	{
		if (P_Head_Room->next == now)
		{
			P_Head_Room->next = now->next;
		}
		else
		{
			last->next = now->next;
			free(now);
		}
	}
	else//找不到这个节点
	{
		return;
	}
}

POrder Blur_Search_By_Time(Time start, Time end)
{
	POrder results_head = (POrder)malloc(sizeof(order));
	POrder results_temp;
	POrder results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (Judge_Search_Time(temp->start.year, temp->start.month, temp->start.day, start, end)) {
			results_temp = (POrder)malloc(sizeof(order));
			strcpy(results_temp->client_id, temp->client_id);
			strcpy(results_temp->order_id, temp->order_id);
			strcpy(results_temp->room_id, temp->room_id);
			results_temp->type = temp->type;
			results_temp->price = temp->price;
			results_temp->start.year = temp->start.year;
			results_temp->start.month = temp->start.month;
			results_temp->start.day = temp->start.day;
			results_temp->start.weekday = temp->start.weekday;
			results_temp->start.hour = temp->start.hour;
			results_temp->end.year = temp->end.year;
			results_temp->end.month = temp->end.month;
			results_temp->end.day = temp->end.day;
			results_temp->end.weekday = temp->end.weekday;
			results_temp->end.hour = temp->end.hour;
			strcpy(results_temp->remark.message, temp->remark.message);
			results_temp->remark.star = temp->remark.star;
			results_temp->next = NULL;
			results_now->next = results_temp;
			results_now = results_temp;
		}


		temp = temp->next;
	}
	return results_head;
}

PClient Search_Client_By_ClientidN(char id[], char name[])
{

	PClient results_head = (PClient)malloc(sizeof(client));
	PClient results_temp;
	PClient results_now;
	results_head->next = NULL;
	results_now = results_temp = results_head;

	PClient temp = P_Head_Client->next;
	while (temp != NULL) {
		if (strcmp(temp->id, id) == 0 && strcmp(temp->name, name) == 0) {
			results_temp = (PClient)malloc(sizeof(client));
			strcpy(results_temp->id, temp->id);
			strcpy(results_temp->password, temp->password);
			strcpy(results_temp->name, temp->name);
			strcpy(results_temp->phone, temp->phone);
			results_temp->gender = temp->gender;
			results_temp->VIP = temp->VIP;
			results_temp->num_bill = temp->num_bill;
			results_temp->pay = temp->pay;
			results_temp->head_order = NULL;
			results_temp->next = NULL;
			results_now->next = results_temp;
			results_now = results_temp;
		}
		temp = temp->next;
	}
	return results_head;
}

bool Judge_Search_Time(int year, int month, int day, Time s, Time e)
{
	if (s.year == e.year && s.month == e.month) {
		if (year == s.year && year == s.month && day >= s.day && day <= e.day) {
			return true;
		}
		else return false;
	}

	if (s.year == e.year) {
		if (year == s.year) {
			if (month == s.month) {
				if (day >= s.day) {
					return true;
				}
				return false;
			}
			if (month > s.month) {
				if (month < e.month) {
					return true;
				}
				if (month == e.month) {
					if (day <= e.day) {
						return true;
					}
					return false;
				}
			}
		}

		return false;
	}

	if (s.year < e.year) {
		if (year == s.year) {
			if (month >= s.month) {
				if (day >= s.day) {
					return true;
				}
			}
			return false;
		}
		if (year > s.year) {
			if (year < e.year) {
				return true;
			}
			if (year == e.year) {
				if (month < e.month) {
					return true;
				}
				if (month == e.month) {
					if (day <= e.day) {
						return true;
					}
					return false;
				}
			}
		}
	}

	return false;
}

void Add_Room(Room_Type type)//建立房间时需定义价格，暂全定为100
{
	PRoom p_now_room = P_Head_Room;
	P_Head_Room->type = A1;

	//建立一个节点
	PRoom p = (PRoom)malloc(sizeof(Room));

	PRoom p2 = p_now_room;

	//与类型有关的元素
	if (type == A1)
	{
		p->type = A1;
		p->id[0] = 'A';
		p->id[1] = '1';
		p->price = 60;//需要改
		p->id[3] = '1';
	}
	else if (type == A2)
	{
		p->type = A2;
		p->id[0] = 'A';
		p->id[1] = '2';
		p->price = 90;//需要改
		p->id[3] = '2';
	}
	else if (type == B1)
	{
		p->type = B1;
		p->id[0] = 'B';
		p->id[1] = '1';
		p->price = 500;//需要改
		p->id[3] = '3';
	}
	else if (type == B2)
	{
		p->type = B2;
		p->id[0] = 'B';
		p->id[1] = '2';
		p->price = 220;//需要改
		p->id[3] = '4';
	}
	//全部一致的元素
	p->id[2] = '_';
	p->id[6] = '\0';
	p->Is_Use = 0;
	p->discount = 1;
	p->client = NULL;
	p->start.year = 0;
	p->start.month = 0;
	p->start.day = 0;
	p->start.weekday = 0;
	p->start.hour = 0;
	p->end.year = 0;
	p->end.month = 0;
	p->end.day = 0;
	p->end.weekday = 0;
	p->end.hour = 0;
	p->next = NULL;
	//(暂不确定此房间的id值)

	//找到插入的位置(上面将head节点类型设置为A1，可以进行没有A1时的判断)
	while (p2 != NULL)
	{
		if ((p_now_room != NULL && p2->type <= type && p_now_room->type > type) || (p2->type == B2 && p2->next == NULL) || (p2->type == A2 && p2->next == NULL) || (p2->type == B1 && p2->next == NULL))
		{
			//链表的插入操作
			PRoom temp = (PRoom)malloc(sizeof(Room));
			if ((p2->next == NULL && p2->type == B2) || (p2->type == A2 && p2->next == NULL) || (p2->type == B1 && p2->next == NULL))
			{
				p2->next = p;
			}
			else
			{
				p->next = p2->next;
				p2->next = p;

			}

			p->id[4] = p2->id[4];
			p->id[5] = p2->id[5];

			//确定id值
			if (p2->type != p->type)
			{
				p->id[4] = '0';
				p->id[5] = '1';
			}
			else
			{
				if (p->id[5] != '9')
				{
					p->id[5] += 1;
				}
				else
				{
					p->id[5] = '0';
					p->id[4] += 1;
				}
			}
			break;
		}
		//进入下一个节点
		if (p_now_room != NULL)
		{
			p2 = p_now_room;
			p_now_room = p_now_room->next;
		}
		else
		{
			break;
		}
	}


	//如果没有房间
	if (P_Head_Room->next == NULL)
	{
		P_Head_Room->next = p;
		//确定id值
		p->id[4] = '0';
		p->id[5] = '1';
	}
}