
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
	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->order_id, id) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

POrder Search_Order_By_Clientid(char id[])
{
	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->client_id, id) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

POrder Search_Order_By_Roomid(char id[])
{
	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->room_id, id) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

POrder Search_Order_By_Starttime(Time start)
{
	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

POrder Search_Order_By_Endtime(Time end)
{
	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

POrder Search_Order_By_Time(Time start, Time end)
{
	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day) {
			if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day)
				return temp;
		}
		temp = temp->next;
	}
}

POrder Search_Order_By_OrderidT(char id[], Time start, Time end)
{
	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->order_id, id) == 0) {
			if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day) {
				if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day)
					return temp;
			}
		}
		temp = temp->next;
	}
	return NULL;
}

POrder Search_Order_By_ClientidT(char id[], Time start, Time end)
{
	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->client_id, id) == 0) {
			if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day) {
				if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day)
					return temp;
			}
		}
		temp = temp->next;
	}
	return NULL;
}

POrder Search_Order_By_RoomidT(char id[], Time start, Time end)
{
	POrder temp = P_Head_Order->next;
	while (temp != NULL) {
		if (strcmp(temp->room_id, id) == 0) {
			if (start.year == temp->start.year && start.month == temp->start.month && start.day == temp->start.day) {
				if (end.year == temp->end.year && end.month == temp->end.month && end.day == temp->end.day)
					return temp;
			}
		}
		temp = temp->next;
	}
	return NULL;
}