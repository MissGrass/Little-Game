// 火车订票系统.cpp: 定义控制台应用程序的入口点。
//visual studio 2017版本下运行，easyX图像库
/**********************************
*
*	程序名称：	火车订票系统
*	编译环境：	VS2017 && easyX
*	作者相关：	沉香
*	开始时间：	2018年4月3日
*	最后修改：	2018年4月4日
*
***********************************/

#include "stdafx.h"
#include <stdio.h>
#include <graphics.h>//图形图像头文件
#include <conio.h>//屏幕操作
#include <string>
#include <tchar.h>

/********函数声明区**********/

void welcome();//欢迎界面
void administratorORcustomer();//管理员OR客户选择
void OnLButtonDown1(MOUSEMSG m);//按下左键
void OnLButtonDown2(MOUSEMSG m);
void OnLButtonDown3(MOUSEMSG m);
void administrator();//管理员选择
void customer();//顾客选择




int main() {
	initgraph(1000, 600);
	welcome();

	//administratorORcustomer();
	//OnLButtonDown(m);
	closegraph();
	getchar();
	//getchar();
	//printf("abcd");
	return 0;
}

void welcome() {
	cleardevice();//清屏
	setfillcolor(BLUE);
	int r = 0;
	while (!_kbhit()) {
		settextcolor(RGB(80, r, 0));//设置文字颜色
		settextstyle(40, 0, _T("楷体"));//设置文字样式高40，宽0；
		outtextxy(340, 200, _T("欢迎进入"));
		settextstyle(50, 0, _T("楷体"));//设置文字样式高50，宽0；
		outtextxy(380, 270, _T("火车订票系统"));
		settextstyle(20, 0, _T("楷体"));//设置文字样式高20，宽0；
		outtextxy(700, 450, _T("(按任意键继续)"));
		if (r > 240) {
			r = 0;
		}
		r += 5;
		Sleep(100);
	}
	administratorORcustomer();
}

void administratorORcustomer() {
	cleardevice();//清屏
	settextcolor(RGB(80, 230, 0));//设置文字颜色
	settextstyle(40, 0, _T("楷体"));//设置文字样式高25，宽0；
	outtextxy(230, 250, _T("我是"));
	//int r = 0;
	//do{
	settextcolor(RGB(80, 100, 0));//设置文字颜色
	setlinecolor(BLUE);
	rectangle(580, 130, 740, 190);
	rectangle(580, 350, 740, 410);
	outtextxy(600, 140, _T("管理员"));
	outtextxy(600, 360, _T("客  户"));
	//if (r > 240) {
	//	r = 0;
	//	}
	//r += 5;
	//Sleep(70);
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//获取的消息是否是左键按下
			OnLButtonDown1(m);
		//	switch (m.uMsg)
		//{
		//case WM_LBUTTONDOWN:
		//	OnLButtonDown(m);
		//}
	}


	//} while(!_kbhit());
	getchar();
	// 定义字符串缓冲区，并接收用户输入
	TCHAR s[10];
	InputBox(s, 10, _T("请输入半径"));

	// 将用户输入转换为数字
	int r;
	sscanf(s, "%d", &r);

	getchar();
}
void OnLButtonDown1(MOUSEMSG m) {
	if (m.x > 580 && m.x < 740 && m.y>130 && m.y < 190) {
		//welcome();
		administrator();
	}
	else if (m.x > 580 && m.x < 740 && m.y>350 && m.y < 410) {
		customer();
	}
}

void OnLButtonDown2(MOUSEMSG m) {
	if (m.x > 230 && m.x < 310 && m.y>330 && m.y < 370) {
		cleardevice();//清屏
		settextcolor(RGB(80, 230, 0));//设置文字颜色
		settextstyle(40, 0, _T("楷体"));//设置文字样式高25，宽0；
		outtextxy(230, 250, _T("我是1"));
	}
	else if (m.x > 480 && m.x < 560 && m.y>330 && m.y < 370) {
		cleardevice();//清屏
		settextcolor(RGB(80, 230, 0));//设置文字颜色
		settextstyle(40, 0, _T("楷体"));//设置文字样式高25，宽0；
		outtextxy(230, 250, _T("我是2"));
	}
	else if (m.x > 710 && m.x < 790 && m.y>330 && m.y < 370) {
		administratorORcustomer();
	}
}

void administrator() {
	cleardevice();//清屏
	settextcolor(RGB(80, 230, 0));//设置文字颜色
	settextstyle(40, 0, _T("楷体"));
	setlinecolor(GREEN);
	outtextxy(460, 30, _T("管理员"));
	outtextxy(170, 170, _T("列车信息："));
	line(200, 370, 280, 370);
	outtextxy(200, 330, _T("添加"));
	line(480, 370, 560, 370);
	outtextxy(480, 330, _T("查看"));
	line(710, 370, 790, 370);
	outtextxy(710, 330, _T("返回"));
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//获取的消息是否是左键按下
			OnLButtonDown2(m);
	}
}
void OnLButtonDown3(MOUSEMSG m) {
	if (m.x > 200 && m.x < 680 && m.y>150 && m.y < 190) {
		cleardevice();//清屏
		settextcolor(RGB(80, 230, 0));//设置文字颜色
		settextstyle(40, 0, _T("楷体"));//设置文字样式高25，宽0；
		outtextxy(230, 250, _T("我是12"));
	}
	else if (m.x > 200 && m.x < 360 && m.y>300 && m.y < 340) {
		cleardevice();//清屏
		settextcolor(RGB(80, 230, 0));//设置文字颜色
		settextstyle(40, 0, _T("楷体"));//设置文字样式高25，宽0；
		outtextxy(230, 250, _T("我是22"));
	}
	else if (m.x > 200 && m.x < 280 && m.y>450 && m.y < 490) {
		administratorORcustomer();
	}
}
void customer() {
	cleardevice();//清屏
	settextcolor(RGB(80, 230, 0));//设置文字颜色
	settextstyle(40, 0, _T("楷体"));
	setlinecolor(GREEN);

	outtextxy(460, 30, _T("客  户"));
	line(200, 190, 440, 190);
	outtextxy(200, 150, _T("查询列车信息"));
	line(200, 340, 360, 340);
	outtextxy(200, 300, _T("我的订单"));
	line(200, 490, 280, 490);
	outtextxy(200, 450, _T("返回"));
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//获取的消息是否是左键按下
			OnLButtonDown3(m);
	}
}




































#include "stdafx.h"
//#include <stdio.h>
#include <iostream>
#include <graphics.h>//图形图像头文件
#include <conio.h>//屏幕操作
#include <string>
using namespace std;
int main() {
	initgraph(640, 480);
	BeginBatchDraw();
	string str("你好nihao");
	while (true) {
		if (_kbhit()) {
			char c = getch();
			if (str.at(str.length() > 0)) {
				if (str.at(str.length() - 1) & 0x8000)
					str.erase(str.end() - 1);
				str.erase(str.end() - 1);
			}
		}
		else if (c == 27) 	{}
		else {
			str += c;
		}
		outtextxy(0, 0, str.c_str());
		FlushBatchDraw();
		Sleep(15);
		cleardevice();
	}
	closegraph();
}




