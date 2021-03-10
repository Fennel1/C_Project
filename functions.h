#pragma once

#include "settings.h"

void Init();	//��ʼ������
bool Button(int a, int b, const char str[]);		//���ƻ�����ť
bool Button_Input(int a, int b, const char str[]);	//�������밴ť
bool Button_Calendar(int a, int b, int day);
void Draw_Calendar(int year, int month, int choose);


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
void Delete_Order(PClient client);
void Show_Order(PClient client);
void Draw_Fps(PText t);
void Exit();

PRoom Room_Init();		//Ŀǰֻ�ܶ�ȡ����id
//PClient Client_Init();
//POrder Order_Init();
void out_Room(Room* head);

PClient Login(char id[], char password[]);
PClient Register(char id[], char password[], char name[], char phone[]);
PClient Misspw(char id[], char password[], char name[], char phone[]);
void Setnpw(PClient client, char password[]);
bool Search_Room(Time start_t, Time end_t, PClient client, Room_Type type);
bool Delete_Order(PClient client, char room_id);

bool Change_File();