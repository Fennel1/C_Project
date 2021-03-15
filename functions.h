#pragma once

#include "settings.h"

void Init();	//��ʼ������
bool Button(int a, int b, const char str[]);		//���ƻ�����ť
bool Button_Order(int a, int b, POrder order);
bool Button_Delete_Order(int a, int b, POrder order);
bool Button_Input(int a, int b, const char str[]);	//�������밴ť
bool Button_Calendar(int a, int b, int day);
bool Check_Time(int s_year, int s_month, int s_day, int e_year, int e_month, int e_day);
void Draw_Calendar(int year, int month, PClient client);
void reDraw_Calendar(int year, int month, int s_year, int s_month, int s_day, PClient client);
int Popup_Window(int x, int y, int wight, int hight, char title[], char text[][50], int g_num, int var);
bool Button_Star(int a, int b, int* num, int n, int star);


void Init_text(PText t, int x1, int x2, int y1, int y2, int fps);	//��ʼ���ı�
wchar_t Input_Text();
void Append_Text(PText t, char c);			//�޸��ı�
void Draw_Text(PText t);		//�����ı�
void Empty_Text(PText t);

void Run_MainMenu();
void Run_AdminLoginMenu();
void Run_AdminMainMenu();
void Run_ClientLoginMenu();
void Run_ClientRegisterMenu();
void Run_ClientMainMenu(PClient client);
void Commit_Order(PClient client);
void ReCommit_Order(PClient client, int s_year, int s_month, int s_day);
void Choose_room(PClient client, int* room_num, Time start, Time end);
void Complete_Order(POrder order, PClient client, Time start, Time end);
void Message_Board(POrder order, PClient client);
void Delete_Order(PClient client);
void Show_Order(PClient client);
void Draw_Fps(PText t);
void Exit();

PRoom Room_Init();		//Ŀǰֻ�ܶ�ȡ����id
PClient Client_Init();
POrder Order_Init();
POrder Client_Order_Init(PClient client);
void Change_File();//���������ڵ�ֵ�����ļ�
void Change_Room();
void Change_Client();
void Change_Order();

PClient Login(char id[], char password[]);
PClient Register(char id[], char password[], char name[], char phone[]);
PClient MissPassword(char id[], char password[], char name[], char phone[]);
void SetNewPassword(PClient client, char password[]);
bool Checkid(char id[]);
bool Checkphone(char phone[]);
bool Checkpassword(char password[]);
bool Checkrepassword(char password[], char repassword[]);
int* Display_rooms_number(int* rooms, Time start, Time end);
bool Judge_time(Time a, Time b);	//a��b֮ǰ����true��a��b֮���ab��ȶ�����false
POrder Add_Order(PClient client, Room_Type type, Time start, Time end);
void Add_In_Linklist(POrder p_this_order, PClient client);
void Add_Remark_In_Order(POrder order, Remark remark);