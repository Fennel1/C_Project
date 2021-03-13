#pragma once

#include "settings.h"

void Init();	//初始化程序
bool Button(int a, int b, const char str[]);		//绘制基本按钮
bool Button_Input(int a, int b, const char str[]);	//绘制输入按钮
bool Button_Calendar(int a, int b, int day);
void Draw_Calendar(int year, int month, PClient client);
void reDraw_Calendar(int year, int month, int s_year, int s_month, int s_day, PClient client);
int Popup_Window(int x, int y, int wight, int hight, char title[], char text[][50], int g_num, int var);


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
void ReCommit_Order(PClient client, int s_year, int s_month, int s_day);
void Choose_room(PClient client, int* room_num);
void Complete_Order(POrder order, PClient client);
void Delete_Order(PClient client);
void Show_Order(PClient client);
void Draw_Fps(PText t);
void Exit();

PRoom Room_Init();		//目前只能读取房间id
PClient Client_Init();
POrder Order_Init();
<<<<<<< HEAD
=======
POrder Client_Order_Init(PClient client);

>>>>>>> 7d9156758fbc4c2a843b36efb07bb633e32abab8
void out_Room(Room* head);


bool Checkid(char id[]);
bool Checkphone(char phone[]);
PClient Login(char id[], char password[]);
PClient Register(char id[], char password[], char name[], char phone[]);
PClient MissPassword(char id[], char password[], char name[], char phone[]);
void SetNewPassword(PClient client, char password[]);
<<<<<<< HEAD

=======
bool Checkid(char id[]);
bool Checkphone(char phone[]);
int* Display_rooms_number(int* rooms, Time start, Time end);
bool Judge_time(Time a, Time b);	//a在b之前返回true，a在b之后或ab相等都返回false
>>>>>>> 7d9156758fbc4c2a843b36efb07bb633e32abab8

bool Change_File();