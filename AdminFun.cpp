
#include "functions.h"

extern MOUSEMSG M_msg;				// �����Ϣ\

extern PClient P_Head_Client;		//�û�����

extern POrder P_Head_Order;			//��ʱ������Ķ���

extern PRoom P_Head_Room;

POrder Sort_Order_Time_Ascending(POrder p_head_order)		//ʱ������
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
		//�ҵ������λ��
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
	p_head_order = p_start_order->next;
	p_start_order = NULL;
	return p_head_order;
}

POrder Sort_Order_Time_Descending(POrder p_head_order)		//ʱ�併��
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
		//�ҵ������λ��
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
	p_head_order = p_start_order->next;
	p_start_order = NULL;
	return p_head_order;
}
