#pragma once

#include <time.h>		// 时间作为随机生成种子
#include <conio.h>		// 获取键盘信息用
#include <graphics.h>	// 引用图形库头文件

const int SCREEN_H = 600;
const int SCREEN_W = 800;

typedef struct text {			//字符串类型
	int x1, x2, y1, y2;
	wchar_t text[30];
	int len;
	int fps;		//光标闪烁频率
}Text, *PText;
