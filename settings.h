#pragma once

#include <time.h>		// ʱ����Ϊ�����������
#include <conio.h>		// ��ȡ������Ϣ��
#include <graphics.h>	// ����ͼ�ο�ͷ�ļ�

const int SCREEN_H = 600;
const int SCREEN_W = 800;

typedef struct text {			//�ַ�������
	int x1, x2, y1, y2;
	wchar_t text[30];
	int len;
	int fps;		//�����˸Ƶ��
}Text, *PText;
