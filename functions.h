#pragma once

#include "settings.h"


void Init();	//��ʼ������
bool Button(int a, int b, const wchar_t str[]);		//���ư�ť


void Init_text(PText t, int x1, int x2, int y1, int y2, int fps);	//��ʼ���ı�
wchar_t Input_Text();
void Append_Text(PText t, wchar_t c);			//�޸��ı�
void Draw_Text(PText t);		//�����ı�
void Empty_Text(PText t);