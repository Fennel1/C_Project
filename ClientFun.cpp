
#include "functions.h"

extern MOUSEMSG M_msg;				// �����Ϣ\

extern PClient P_Head_Client;		//�û�����

extern POrder P_Head_Order;		//��ʱ������Ķ���

extern PRoom P_Head_Room;


bool Checkid(char id[])			//���id
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

bool Checkphone(char phone[])		//���绰
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

bool Checkpassword(char password[])		//��������ʽ
{

	for (int i = 0; i < strlen(password); i++)
	{
		if (password[i] < 21 || password[i]> 126)
			return false;
	}
	return true;
}

bool Checkrepassword(char password[], char repassword[])		//ȷ������
{
	if (strcmp(password, repassword) == 0)
		return true;

	return false;
}

PClient Register(char id[], char password[], char name[], char phone[])		//�û�ע��
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

PClient Login(char id[], char password[])		//�û���¼
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

int* Display_rooms_number(int* rooms, Time start, Time end)//�������ֿշ���ĸ���
{
	//�������������
	PRoom p_now_room = P_Head_Room->next;
	//�����������ı�is_use��ֵ
	POrder p_now_order = P_Head_Order->next;

	while (p_now_room != NULL)		//����
	{
		p_now_room->Is_Use = false;
		p_now_room = p_now_room->next;
	}

	while (p_now_order != NULL)
	{
		//�жϣ�start��end�����ж�����ֹʱ��֮�ڣ�is_use��Ϊtrue
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

	//�������䣬���is_useΪfalse���շ�����+1
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
	//����ͷ�巨
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
		//id���֮ǰ�Ķ���+1
		int int_id = 0;
		sscanf(p_now_order->order_id, "%d", &int_id);
		int_id++;
		sprintf(p_this_order->order_id, "%d", int_id);
	}
	
	//�������䣬�ҵ����÷��䣬ƥ��room_id, price
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
	//order������ֵ
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
	if (p_now_room != NULL) {
		p_this_order->price = p_now_room->price * Get_Days(start, end) * (1 - client->VIP * 0.03);
	}
	//����ֵ
	return p_this_order;
}

void Add_In_Linklist(POrder p_this_order, PClient client)
{
	client->num_bill++;
	client->pay += p_this_order->price;
	if (client->pay <= 100)		client->VIP = 0;
	else  if (client->pay > 100 && client->pay <= 1000)	client->VIP = 1;
	else  if (client->pay > 1000 && client->pay <= 5000)	client->VIP = 2;
	else  if (client->pay > 5000 && client->pay <= 20000)	client->VIP = 3;
	else  if (client->pay > 20000 && client->pay <= 50000)	client->VIP = 4;
	else  if (client->pay > 50000 && client->pay <= 100000)	client->VIP = 5;
	else  if (client->pay > 100000 && client->pay <= 1000000)	client->VIP = 6;
	else  client->pay = 7;


	POrder p_temp_order = (Order*)malloc(sizeof(Order));
	POrder p_now_order = P_Head_Order;
	//���ڵ�����ܶ����У�β�壩
	
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
	
	//�ڵ���뵽�û�����������
	
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

void Delete_Node(POrder this_order, PClient client)//ɾ���ڵ�
{
	//ȡ�ö�����idֵ
	char ID[10];
	strcpy(ID, this_order->order_id);

	//1.���û�������ɾ���˽ڵ�

	
	POrder p_now = client->head_order->next;
	POrder p2 = NULL;
	if (p_now == NULL)//����Ϊ��
	{
		return;
	}
	//�ҵ���Ҫ��ɾ���Ľڵ㣨idֵΨһ��
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
	else//�Ҳ�������ڵ�
	{
		return;
	}
	

	//2.���ܶ���������ɾ���˽ڵ�
	
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

int Get_Days(Time start, Time end)
{
	int start_year = start.year;
	int start_month = start.month;
	int start_day = start.day;
	int end_year = end.year;
	int end_month = end.month;
	int end_day = end.day;
	//�����·ݰ���������һά����
	int day[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int i;                  //����ѭ������
	double sum_day = 0;     //�����ܵ�����������ʼ��Ϊ0
	int count_lyear = 0;    //�����ܵ�������������ʼ��Ϊ0
	int count_cyear = 0;    //�����ܵ�ƽ����������ʼ��Ϊ0
	int count_sday = 0;     //���忪ʼ�������������ʼ��Ϊ0
	int count_eday = 0;     //��������������������ʼ��Ϊ0

	for (i = start_year + 1; i < end_year; i++)  //��¼������������ƽ����
	{
		if (((i % 4) == 0 && (i % 100) != 0) || (i % 400) == 0)
		{
			count_lyear++;  //������������
		}
		else {
			count_cyear++;  //ƽ����������
		}
	}
	if (start_year == end_year)  //���������ͬʱ
	{
		//�ж��ǲ������꣬��������day[1]��ʼ��Ϊ29������Ϊ28
		day[1] = (((start_year % 4) == 0 && (start_year % 100) != 0) || (start_year % 400) == 0) ? 29 : 28;
		for (i = start_month; i < end_month; i++)    //ѭ����¼��ʼ�·ݵ������·ݵ�����
		{
			sum_day += day[start_month - 1];
		}
		sum_day = sum_day - start_day + end_day;    //��������������ȥ��ʼ�µ��������������һ���µ�����
	}
	else {
		while (start_month <= 12)    //ѭ����¼��ʼ�������
		{
			day[1] = (((start_year % 4) == 0 && (start_year % 100) != 0) || (start_year % 400) == 0) ? 29 : 28;
			count_sday += day[start_month - 1];
			start_month++;
		}
		count_sday -= start_day;    //��ȥ��ʼ�·ݰ���������

		int month = 1;              //������������ʼ���·ݣ���ʼ��Ϊ1

		while (month < end_month)    //ѭ����¼��������н����·�֮ǰ������
		{
			day[1] = (((end_year % 4) == 0 && (end_year % 100) != 0) || (end_year % 400) == 0) ? 29 : 28;
			count_eday += day[month - 1];
			month++;
		}
		count_eday += end_day;      //���Ͻ����·ݰ���������
		//����������
		sum_day += (count_lyear * 366) + (count_cyear * 365) + count_sday + count_eday;
	}

	return sum_day +  1;
}