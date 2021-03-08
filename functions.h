#pragma once

#include "settings.h"

void Init();	//��ʼ������
bool Button(int a, int b, const wchar_t str[]);		//���ư�ť


void Init_text(PText t, int x1, int x2, int y1, int y2, int fps);	//��ʼ���ı�
wchar_t Input_Text();
void Append_Text(PText t, wchar_t c);			//�޸��ı�
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

bool Login(wchar_t id[], wchar_t password[]);
bool Register();
bool Search_Room(Time start_t, Time end_t, PClient client, Room_Type type);
bool Delete_Order(PClient client, wchar_t room_id);

bool Change_File();