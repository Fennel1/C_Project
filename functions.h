#pragma once

#include "settings.h"

//InterfaceComponents.cpp			//������ʾ���
bool Button(int a, int b, const char str[]);						//���ƻ�����ť
bool Button(int a, int b, const char str[], bool choose);			//���Ƶ��������ť
bool Button_Order(int a, int b, POrder order);						//������ʾ������ť
bool Button_Remark(int a, int b, POrder order);
bool Button_Client(int a, int b, PClient client);
bool Button_Room(int a, int b, PRoom room);							//���Ʒ��䰴ť
bool Button_Delete_Order(int a, int b, POrder order);				//����ɾ��������ť
bool Button_Input(int a, int b, const char str[]);					//�����������밴ť
bool Button_Calendar(int a, int b, int day);						//����������ť
bool Button_Star(int a, int b, int* num, int n, int star);			//���������Ǽ���ť
void Draw_Calendar(int year, int month, PClient client);														//����������ס����ʱ������
void reDraw_Calendar(int year, int month, int s_year, int s_month, int s_day, PClient client);					//���������˷�����ʱ������
bool Check_Time(int s_year, int s_month, int s_day, int e_year, int e_month, int e_day);						//���ʱ���Ƿ�Ϸ�
int Popup_Window(int x, int y, int wight, int hight, char title[], char text[][50], int g_num, int var);		//���Ƶ���
int Popup_Window_Room(int x, int y, int wight, int hight, char title[], char text[][50], int g_num, int var);	//���Ʒ��䵯��


//String.cpp						//�����������
void Init_text(PText t, int x1, int x2, int y1, int y2, int fps);	//��ʼ���ı�
wchar_t Input_Text();												//�Ӽ��̶���
void Append_Text(PText t, char c);									//�޸��ı�
void Draw_Text(PText t);											//�����ı�
void Empty_Text(PText t);											//����ı�
void Draw_Fps(PText t);												//��ӡ���


//ClientMenu.cpp					//�û���������
void Run_ClientLoginMenu();														//�û���¼����
void Run_ClientRegisterMenu();													//�û�ע�����
void Run_ClientMainMenu(PClient client);										//�û����˵�
void Commit_Order(PClient client);												//�û�ѡ����סʱ�����
void ReCommit_Order(PClient client, int s_year, int s_month, int s_day);		//�û�ѡ���˷�ʱ�����
void Choose_room(PClient client, int* room_num, Time start, Time end);			//�û�ѡ�񷿼����ͽ���
void Complete_Order(POrder order, PClient client, Time start, Time end);		//�û�֧������
void Message_Board(POrder order, PClient client);								//�û��������۽���
void Delete_Order(PClient client);												//�û�ɾ����������
void Show_Order(PClient client);												//��ʾ�û�ȫ����������									


//ClientFun.cpp						//�û�����
PClient Login(char id[], char password[]);										//�û���¼
PClient Register(char id[], char password[], char name[], char phone[]);		//�û�ע��
PClient MissPassword(char id[], char password[], char name[], char phone[]);	//�û��һ�����
void SetNewPassword(PClient client, char password[]);							//�û�����������
bool Checkid(char id[]);														//�ж����֤���Ƿ�Ϸ�
bool Checkphone(char phone[]);													//�жϵ绰�����Ƿ�Ϸ�
bool Checkpassword(char password[]);											//�ж������Ƿ�Ϸ�
bool Checkrepassword(char password[], char repassword[]);						//�ж��������������Ƿ�һ��
int* Display_rooms_number(int* rooms, Time start, Time end);					//����ʣ�෿����
bool Judge_time(Time a, Time b);												//���ʱ���Ƿ�Ϸ�
POrder Add_Order(PClient client, Room_Type type, Time start, Time end);			//�½�����
void Add_In_Linklist(POrder p_this_order, PClient client);						//��������������
void Add_Remark_In_Order(POrder order, Remark remark);							//�����ۼ��붩����
void Delete_Node(POrder this_order, PClient client);							//��������ɾ������


//MainMenu.cpp						//���˵�����
void Run_MainMenu();				


//AdminMenu.cpp						//����Ա����
void Run_AdminLoginMenu();		//����Ա��¼����
void Run_AdminMainMenu();		//����Ա���˵�
void Run_Hotel();				//�Ƶ�ſ�
void Run_Show_Room();			//��ʾ�������
void Run_Show_Order();			//��ʾ��������
void Run_Search_Order();		//���Ҷ�������
void Run_Search_Client();		//�����û�����


//AdminFun.cpp						//����Ա����
POrder Sort_Order_Time_Ascending(POrder p_head_order);					//����ʱ����������
POrder Sort_Order_Time_Descending(POrder p_head_order);					//����ʱ�併������
POrder Sort_Order_ID_Descending(POrder p_head_order);					//����ID��������
POrder Sort_Order_ID_Ascending(POrder p_head_order);					//����ID��������
POrder Search_Order_By_Orderid(char id[]);								//����ID����
POrder Search_Order_By_Clientid(char id[]);								//�û�ID����
POrder Search_Order_By_Roomid(char id[]);								//����ID����
POrder Search_Order_By_Starttime(Time start);							//��ʼʱ�����
POrder Search_Order_By_Endtime(Time end);								//����ʱ�����
POrder Search_Order_By_Time(Time start, Time end);						//��ʼ����ʱ�����
POrder Search_Order_By_OrderidT(char id[], Time start, Time end);		//ʱ��Ͷ���ID����
POrder Search_Order_By_ClientidT(char id[], Time start, Time end);		//ʱ����û�ID����
POrder Search_Order_By_RoomidT(char id[], Time start, Time end);		//ʱ��ͷ���ID����
bool Search_Check_Orderid(char id[]);
bool Search_Check_Clientid(char id[]);
bool Search_Check_Roomid(char id[]);
bool Search_Check_Time(char time[]);
PClient Blur_Search_By_Name(char name[]);
POrder Blur_Search_By_Time(Time start, Time end);
PClient Search_Client_By_Clientid(char id[]);
void Delete_Room(PRoom room);
bool Judge_Search_Time(int year, int month, int day, Time s, Time e);
void Add_Room(Room_Type type);


//Init.cpp							//��ʼ��
void Init();								//�����ʼ��
PRoom Room_Init();							//���������ʼ��
PClient Client_Init();						//�û������ʼ��
POrder Order_Init();						//���������ʼ��
POrder Client_Order_Init(PClient client);	//�û��ĸ��˶��������ʼ��
void Change_File();							//�޸��ļ�
void Change_Room();							//�޸ķ����ļ�
void Change_Client();						//�޸��û��ļ�
void Change_Order();						//�޸Ķ����ļ�
void Destroy_Linklist(POrder head);			//�ͷŶ�������ռ�
void Destroy_Linklist(PClient head);		//�ͷ��û�����ռ�
void Destroy_Linklist(PRoom head);			//�ͷŷ�������ռ�
void Exit();								//�˳�����