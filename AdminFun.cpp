
#include "functions.h"

extern MOUSEMSG M_msg;				// 鼠标消息\

extern PClient P_Head_Client;		//用户链表

extern POrder P_Head_Order;			//以时间排序的订单

extern PRoom P_Head_Room;

POrder Sort_Order_Time_Ascending(POrder p_head_order)		//时间升序
{
	if (p_head_order == NULL || p_head_order->next == NULL)
	{
		return p_head_order;
	}

	POrder p_now_order = p_head_order->next;
	POrder p_start_order = (Order*)malloc(sizeof(Order));
	p_start_order->next = p_head_order;
	POrder p_end_order = p_head_order;

	while (p_now_order != NULL)
	{
		POrder p_temp_order = p_start_order->next;
		POrder pre = p_start_order;
		//找到插入的位置
		while (p_temp_order != p_now_order && Judge_time(p_now_order->start, p_temp_order->start) == false)
		{
			p_temp_order = p_temp_order->next;
			pre = pre->next;
		}
		if (p_temp_order == p_now_order)
		{
			p_end_order = p_now_order;
		}
		else
		{
			p_end_order->next = p_now_order->next;
			p_now_order->next = p_temp_order;
			pre->next = p_now_order;
		}
		p_now_order = p_end_order->next;
	}

	return p_start_order->next->next;
}

POrder Sort_Order_Time_Descending(POrder p_head_order)		//时间降序
{
	if (p_head_order == NULL || p_head_order->next == NULL)
	{
		return p_head_order;
	}

	POrder p_now_order = p_head_order->next;
	POrder p_start_order = (Order*)malloc(sizeof(Order));
	p_start_order->next = p_head_order;
	POrder p_end_order = p_head_order;

	while (p_now_order != NULL)
	{
		POrder p_temp_order = p_start_order->next;
		POrder pre = p_start_order;
		//找到插入的位置
		while (p_temp_order != p_now_order && Judge_time(p_now_order->start, p_temp_order->start) == true)
		{
			p_temp_order = p_temp_order->next;
			pre = pre->next;
		}
		if (p_temp_order == p_now_order)
		{
			p_end_order = p_now_order;
		}
		else
		{
			p_end_order->next = p_now_order->next;
			p_now_order->next = p_temp_order;
			pre->next = p_now_order;
		}
		p_now_order = p_end_order->next;
	}
	return p_start_order->next->next;
}

POrder Sort_Order_ID_Ascending(POrder p_head_order)		//ID升序
{
	if (p_head_order == NULL || p_head_order->next == NULL)
	{
		return p_head_order;
	}

	POrder p_now_order = p_head_order->next;
	POrder p_start_order = (Order*)malloc(sizeof(Order));
	p_start_order->next = p_head_order;
	POrder p_end_order = p_head_order;

	while (p_now_order != NULL)
	{
		POrder p_temp_order = p_start_order->next;
		POrder pre = p_start_order;
		//找到插入的位置
		while (p_temp_order != p_now_order && strcmp(p_now_order->client_id, p_temp_order->client_id) > 0)
		{
			p_temp_order = p_temp_order->next;
			pre = pre->next;
		}
		if (p_temp_order == p_now_order)
		{
			p_end_order = p_now_order;
		}
		else
		{
			p_end_order->next = p_now_order->next;
			p_now_order->next = p_temp_order;
			pre->next = p_now_order;
		}
		p_now_order = p_end_order->next;
	}
	return p_start_order->next->next;
}

POrder Sort_Order_ID_Descending(POrder p_head_order)		//ID降序
{
	if (p_head_order == NULL || p_head_order->next == NULL)
	{
		return p_head_order;
	}

	POrder p_now_order = p_head_order->next;
	POrder p_start_order = (Order*)malloc(sizeof(Order));
	p_start_order->next = p_head_order;
	POrder p_end_order = p_head_order;

	while (p_now_order != NULL)
	{
		POrder p_temp_order = p_start_order->next;
		POrder pre = p_start_order;
		//找到插入的位置
		while (p_temp_order != p_now_order && strcmp(p_now_order->client_id, p_temp_order->client_id) < 0)
		{
			p_temp_order = p_temp_order->next;
			pre = pre->next;
		}
		if (p_temp_order == p_now_order)
		{
			p_end_order = p_now_order;
		}
		else
		{
			p_end_order->next = p_now_order->next;
			p_now_order->next = p_temp_order;
			pre->next = p_now_order;
		}
		p_now_order = p_end_order->next;
	}
	return p_start_order->next->next;
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
	if (strcmp(id, "1") == 0)	return true;
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