#pragma once

#include "settings.h"

//InterfaceComponents.cpp			//窗口显示组件
bool Button(int a, int b, const char str[]);						//绘制基本按钮
bool Button(int a, int b, const char str[], bool choose);			//绘制点击高亮按钮
bool Button_Order(int a, int b, POrder order);						//绘制显示订单按钮
bool Button_Remark(int a, int b, POrder order);
bool Button_Client(int a, int b, PClient client);
bool Button_Room(int a, int b, PRoom room);							//绘制房间按钮
bool Button_Delete_Order(int a, int b, POrder order);				//绘制删除订单按钮
bool Button_Input(int a, int b, const char str[]);					//绘制文字输入按钮
bool Button_Calendar(int a, int b, int day);						//绘制日历按钮
bool Button_Star(int a, int b, int* num, int n, int star);			//绘制评价星级按钮
void Draw_Calendar(int year, int month, PClient client);														//绘制输入入住日期时的日历
void reDraw_Calendar(int year, int month, int s_year, int s_month, int s_day, PClient client);					//绘制输入退房日期时的日历
bool Check_Time(int s_year, int s_month, int s_day, int e_year, int e_month, int e_day);						//检查时间是否合法
int Popup_Window(int x, int y, int wight, int hight, char title[], char text[][50], int g_num, int var);		//绘制弹窗
int Popup_Window_Room(int x, int y, int wight, int hight, char title[], char text[][50], int g_num, int var);	//绘制房间弹窗


//String.cpp						//文字输入组件
void Init_text(PText t, int x1, int x2, int y1, int y2, int fps);	//初始化文本
wchar_t Input_Text();												//从键盘读入
void Append_Text(PText t, char c);									//修改文本
void Draw_Text(PText t);											//绘制文本
void Empty_Text(PText t);											//清空文本
void Draw_Fps(PText t);												//打印光标


//ClientMenu.cpp					//用户交互窗口
void Run_ClientLoginMenu();														//用户登录界面
void Run_ClientRegisterMenu();													//用户注册界面
void Run_ClientMainMenu(PClient client);										//用户主菜单
void Commit_Order(PClient client);												//用户选择入住时间界面
void ReCommit_Order(PClient client, int s_year, int s_month, int s_day);		//用户选择退房时间界面
void Choose_room(PClient client, int* room_num, Time start, Time end);			//用户选择房间类型界面
void Complete_Order(POrder order, PClient client, Time start, Time end);		//用户支付界面
void Message_Board(POrder order, PClient client);								//用户评价评论界面
void Delete_Order(PClient client);												//用户删除订单界面
void Show_Order(PClient client);												//显示用户全部订单界面									


//ClientFun.cpp						//用户函数
PClient Login(char id[], char password[]);										//用户登录
PClient Register(char id[], char password[], char name[], char phone[]);		//用户注册
PClient MissPassword(char id[], char password[], char name[], char phone[]);	//用户找回密码
void SetNewPassword(PClient client, char password[]);							//用户设置新密码
bool Checkid(char id[]);														//判断身份证号是否合法
bool Checkphone(char phone[]);													//判断电话号码是否合法
bool Checkpassword(char password[]);											//判断密码是否合法
bool Checkrepassword(char password[], char repassword[]);						//判断两次密码输入是否一致
int* Display_rooms_number(int* rooms, Time start, Time end);					//查找剩余房间数
bool Judge_time(Time a, Time b);												//检查时间是否合法
POrder Add_Order(PClient client, Room_Type type, Time start, Time end);			//新建订单
void Add_In_Linklist(POrder p_this_order, PClient client);						//将订单加入链表
void Add_Remark_In_Order(POrder order, Remark remark);							//将评论加入订单中
void Delete_Node(POrder this_order, PClient client);							//从链表中删除订单


//MainMenu.cpp						//主菜单界面
void Run_MainMenu();				


//AdminMenu.cpp						//管理员界面
void Run_AdminLoginMenu();		//管理员登录界面
void Run_AdminMainMenu();		//管理员主菜单
void Run_Hotel();				//酒店概况
void Run_Show_Room();			//显示房间界面
void Run_Show_Order();			//显示订单界面
void Run_Search_Order();		//查找订单界面
void Run_Search_Client();		//查找用户界面


//AdminFun.cpp						//管理员函数
POrder Sort_Order_Time_Ascending(POrder p_head_order);					//订单时间升序排序
POrder Sort_Order_Time_Descending(POrder p_head_order);					//订单时间降序排序
POrder Sort_Order_ID_Descending(POrder p_head_order);					//订单ID降序排序
POrder Sort_Order_ID_Ascending(POrder p_head_order);					//订单ID升序排序
POrder Search_Order_By_Orderid(char id[]);								//订单ID查找
POrder Search_Order_By_Clientid(char id[]);								//用户ID查找
POrder Search_Order_By_Roomid(char id[]);								//房间ID查找
POrder Search_Order_By_Starttime(Time start);							//开始时间查找
POrder Search_Order_By_Endtime(Time end);								//结束时间查找
POrder Search_Order_By_Time(Time start, Time end);						//开始结束时间查找
POrder Search_Order_By_OrderidT(char id[], Time start, Time end);		//时间和订单ID查找
POrder Search_Order_By_ClientidT(char id[], Time start, Time end);		//时间和用户ID查找
POrder Search_Order_By_RoomidT(char id[], Time start, Time end);		//时间和房间ID查找
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


//Init.cpp							//初始化
void Init();								//程序初始化
PRoom Room_Init();							//房间链表初始化
PClient Client_Init();						//用户链表初始化
POrder Order_Init();						//订单链表初始化
POrder Client_Order_Init(PClient client);	//用户的个人订单链表初始化
void Change_File();							//修改文件
void Change_Room();							//修改房间文件
void Change_Client();						//修改用户文件
void Change_Order();						//修改订单文件
void Destroy_Linklist(POrder head);			//释放订单链表空间
void Destroy_Linklist(PClient head);		//释放用户链表空间
void Destroy_Linklist(PRoom head);			//释放房间链表空间
void Exit();								//退出程序