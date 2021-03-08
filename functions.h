#pragma once

#include "settings.h"


void Init();	//初始化程序
bool Button(int a, int b, const wchar_t str[]);		//绘制按钮


void Init_text(PText t, int x1, int x2, int y1, int y2, int fps);	//初始化文本
wchar_t Input_Text();
void Append_Text(PText t, wchar_t c);			//修改文本
void Draw_Text(PText t);		//绘制文本
void Empty_Text(PText t);