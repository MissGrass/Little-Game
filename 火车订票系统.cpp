// �𳵶�Ʊϵͳ.cpp: �������̨Ӧ�ó������ڵ㡣
//visual studio 2017�汾�����У�easyXͼ���
/**********************************
*
*	�������ƣ�	�𳵶�Ʊϵͳ
*	���뻷����	VS2017 && easyX
*	������أ�	����
*	��ʼʱ�䣺	2018��4��3��
*	����޸ģ�	2018��4��4��
*
***********************************/

#include "stdafx.h"
#include <stdio.h>
#include <graphics.h>//ͼ��ͼ��ͷ�ļ�
#include <conio.h>//��Ļ����
#include <string>
#include <tchar.h>

/********����������**********/

void welcome();//��ӭ����
void administratorORcustomer();//����ԱOR�ͻ�ѡ��
void OnLButtonDown1(MOUSEMSG m);//�������
void OnLButtonDown2(MOUSEMSG m);
void OnLButtonDown3(MOUSEMSG m);
void administrator();//����Աѡ��
void customer();//�˿�ѡ��




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
	cleardevice();//����
	setfillcolor(BLUE);
	int r = 0;
	while (!_kbhit()) {
		settextcolor(RGB(80, r, 0));//����������ɫ
		settextstyle(40, 0, _T("����"));//����������ʽ��40����0��
		outtextxy(340, 200, _T("��ӭ����"));
		settextstyle(50, 0, _T("����"));//����������ʽ��50����0��
		outtextxy(380, 270, _T("�𳵶�Ʊϵͳ"));
		settextstyle(20, 0, _T("����"));//����������ʽ��20����0��
		outtextxy(700, 450, _T("(�����������)"));
		if (r > 240) {
			r = 0;
		}
		r += 5;
		Sleep(100);
	}
	administratorORcustomer();
}

void administratorORcustomer() {
	cleardevice();//����
	settextcolor(RGB(80, 230, 0));//����������ɫ
	settextstyle(40, 0, _T("����"));//����������ʽ��25����0��
	outtextxy(230, 250, _T("����"));
	//int r = 0;
	//do{
	settextcolor(RGB(80, 100, 0));//����������ɫ
	setlinecolor(BLUE);
	rectangle(580, 130, 740, 190);
	rectangle(580, 350, 740, 410);
	outtextxy(600, 140, _T("����Ա"));
	outtextxy(600, 360, _T("��  ��"));
	//if (r > 240) {
	//	r = 0;
	//	}
	//r += 5;
	//Sleep(70);
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//��ȡ����Ϣ�Ƿ����������
			OnLButtonDown1(m);
		//	switch (m.uMsg)
		//{
		//case WM_LBUTTONDOWN:
		//	OnLButtonDown(m);
		//}
	}


	//} while(!_kbhit());
	getchar();
	// �����ַ������������������û�����
	TCHAR s[10];
	InputBox(s, 10, _T("������뾶"));

	// ���û�����ת��Ϊ����
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
		cleardevice();//����
		settextcolor(RGB(80, 230, 0));//����������ɫ
		settextstyle(40, 0, _T("����"));//����������ʽ��25����0��
		outtextxy(230, 250, _T("����1"));
	}
	else if (m.x > 480 && m.x < 560 && m.y>330 && m.y < 370) {
		cleardevice();//����
		settextcolor(RGB(80, 230, 0));//����������ɫ
		settextstyle(40, 0, _T("����"));//����������ʽ��25����0��
		outtextxy(230, 250, _T("����2"));
	}
	else if (m.x > 710 && m.x < 790 && m.y>330 && m.y < 370) {
		administratorORcustomer();
	}
}

void administrator() {
	cleardevice();//����
	settextcolor(RGB(80, 230, 0));//����������ɫ
	settextstyle(40, 0, _T("����"));
	setlinecolor(GREEN);
	outtextxy(460, 30, _T("����Ա"));
	outtextxy(170, 170, _T("�г���Ϣ��"));
	line(200, 370, 280, 370);
	outtextxy(200, 330, _T("���"));
	line(480, 370, 560, 370);
	outtextxy(480, 330, _T("�鿴"));
	line(710, 370, 790, 370);
	outtextxy(710, 330, _T("����"));
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//��ȡ����Ϣ�Ƿ����������
			OnLButtonDown2(m);
	}
}
void OnLButtonDown3(MOUSEMSG m) {
	if (m.x > 200 && m.x < 680 && m.y>150 && m.y < 190) {
		cleardevice();//����
		settextcolor(RGB(80, 230, 0));//����������ɫ
		settextstyle(40, 0, _T("����"));//����������ʽ��25����0��
		outtextxy(230, 250, _T("����12"));
	}
	else if (m.x > 200 && m.x < 360 && m.y>300 && m.y < 340) {
		cleardevice();//����
		settextcolor(RGB(80, 230, 0));//����������ɫ
		settextstyle(40, 0, _T("����"));//����������ʽ��25����0��
		outtextxy(230, 250, _T("����22"));
	}
	else if (m.x > 200 && m.x < 280 && m.y>450 && m.y < 490) {
		administratorORcustomer();
	}
}
void customer() {
	cleardevice();//����
	settextcolor(RGB(80, 230, 0));//����������ɫ
	settextstyle(40, 0, _T("����"));
	setlinecolor(GREEN);

	outtextxy(460, 30, _T("��  ��"));
	line(200, 190, 440, 190);
	outtextxy(200, 150, _T("��ѯ�г���Ϣ"));
	line(200, 340, 360, 340);
	outtextxy(200, 300, _T("�ҵĶ���"));
	line(200, 490, 280, 490);
	outtextxy(200, 450, _T("����"));
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//��ȡ����Ϣ�Ƿ����������
			OnLButtonDown3(m);
	}
}




































#include "stdafx.h"
//#include <stdio.h>
#include <iostream>
#include <graphics.h>//ͼ��ͼ��ͷ�ļ�
#include <conio.h>//��Ļ����
#include <string>
using namespace std;
int main() {
	initgraph(640, 480);
	BeginBatchDraw();
	string str("���nihao");
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




