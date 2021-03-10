#pragma once

#include "settings.h"

void Init();	//初始化程序
bool Button(int a, int b, const char str[]);		//绘制基本按钮
bool Button_Input(int a, int b, const char str[]);	//绘制输入按钮
bool Button_Calendar(int a, int b, int day);
void Draw_Calendar(int year, int month, int choose);


void Init_text(PText t, int x1, int x2, int y1, int y2, int fps);	//初始化文本
wchar_t Input_Text();
void Append_Text(PText t, char c);			//修改文本
void Draw_Text(PText t);		//绘制文本
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

PRoom Room_Init();		//目前只能读取房间id
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