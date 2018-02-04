// �ҵ�Ϳ������ϰ.cpp: �������̨Ӧ�ó������ڵ㡣
//
//Visual studio 2017�汾�����У�easyXͼ�ο� 
/*
��ά����
�ṹ��
��Ϸ��ӭ����
��Ϸ������
���������ɫ
�Ҽ���������
�ж���Ϸ�Ƿ����
������һ��
*/

#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#define M 12
#define G 30

void welcome();
void PaintGrid(int Mid_x, int Mid_y, int num, int color);
void OnLButtonDown(MOUSEMSG m, int num);
void OnRButtonDown(int num);
void NextLevel(int num);
int JudgeFull(int num, int arr[M][M]);
int DisPatch();

struct Grid {
	int left;//������������
	int right;
	int up;
	int down;
	int arr[M][M];//��ά���鴴�����ӣ�-1Ϊ������1Ϊ��
	int num;//�߽������
}grid;

int main(){
	int end = 0;
	grid.num = 4;
	welcome();
	PaintGrid(340, 250, grid.num, RGB(150, 0, 0));
	while (end != 1) {
		end = DisPatch();
	}
	closegraph();
	getchar();
    return 0;
}

//��Ϸ������
void welcome() {
	//��ʼ������
	initgraph(680, 500);

	//����
	settextcolor(RGB(50,100,100));
	settextstyle(60, 0, _T("����"));
	outtextxy(180, 60, _T("���С��Ϸ"));

	//��ʾ�淨����
	settextcolor(WHITE);
	settextstyle(20, 0, _T("����"));
	outtextxy(50,200,_T("������񣬷��񼰷�����������Ҹ��ӣ�����ż���治���Ĺ�������ͼ"));
	outtextxy(10, 240, _T("ֱ������Ϳ�����������һ��;�������������һ�����"));

	//ʵ����˸���֣������������
	int c = 255;
	while (!_kbhit()) {
		settextcolor(RGB(0, c, 0));
		settextstyle(30, 0, _T("����"));
		outtextxy(230, 400, _T("^_^�����������"));
		c -= 8;
		if (c < 0) {
			c = 255;
		}
		Sleep(20);
	}
	//����������
	cleardevice();
}

void PaintGrid(int mx, int my, int num, int color) {
	int c = 255;
	int p = 0;
	while (p<100) {
		settextcolor(RGB(0,0,c));
		settextstyle(30, 0, _T("����"));
		outtextxy(250, 60, _T("����FIGHTING��"));
		c -= 8;
		if (c < 0) {
			c = 255;
		}
		p++;
		Sleep(18);
	}
	

	int x, y, nx, ny;
	//��Ϸ�����������ұ߽�����
	grid.left = mx - num * G / 2;
	grid.right = mx + num * G / 2;
	grid.up = my - num * G / 2;
	grid.down = my + num * G / 2;

	//���Ƹ���
	setlinecolor(color);
	for (x = grid.left; x <= grid.right; x += G)
		line(x, grid.up, x, grid.down);
	for (y = grid.up; y <= grid.down; y += G)
		line(grid.left, y, grid.right, y);

	//��߿�
	for (x = 20; x >= 10; x--) {
		rectangle(grid.left - x, grid.up - x, grid.right + x, grid.down + x);
		Sleep(40);
	}
	
	//��յ�Ԫ��
	for (x = 0; x < num; x++)
		for (y = 0; y < num; y++)
			grid.arr[x][y] = -1;

	//��Ԫ�����
	for (nx = 0; nx < num; nx++)
		for (ny = 0; ny < num; ny++) {
			setfillcolor(BLACK);
			x = nx * G + grid.left;;
			y = ny * G + grid.up;
			solidrectangle(x + 1, y + 1, x + G - 1, y + G - 1);
		}
	int q = 0;
	while (q<100) {
		settextcolor(RGB(0, 0, c));
		settextstyle(30, 0, _T("����"));
		outtextxy(250, 400, _T("����FIGHTING��"));
		c -= 8;
		if (c < 0) {
			c = 255;
		}
		q++;
		Sleep(20);
	}
}

//�������
void OnLButtonDown(MOUSEMSG m, int num) {
	int nx, ny, x, y;
	if (m.x > grid.left && m.x < grid.right && m.y > grid.up && m.y < grid.down) {
		//��������ת���������±�
		nx = (int)(m.x - grid.left) / G;
		ny = (int)(m.y - grid.up) / G;

		//ת������״̬
		grid.arr[nx][ny] = -grid.arr[nx][ny];
		
		if (nx >= 0 && nx < num - 1)
			grid.arr[nx + 1][ny] = -grid.arr[nx + 1][ny];//�ұ�
		if (nx > 0 && nx <= num - 1)
			grid.arr[nx - 1][ny] = -grid.arr[nx - 1][ny];//���
		if (ny >= 0 && ny < num - 1)
			grid.arr[nx][ny + 1] = -grid.arr[nx][ny + 1];//��
		if (ny > 0 && ny <= num - 1)
			grid.arr[nx][ny - 1] = -grid.arr[nx][ny - 1];//��

		//ɨ����ɫ
		for (nx = 0; nx < num; nx++)
			for (ny = 0; ny < num; ny++) {
				if (grid.arr[nx][ny] == 1)
					setfillcolor(LIGHTCYAN);
				else
					setfillcolor(BLACK);
				x = nx * G + grid.left;
				y = ny * G + grid.up;
				solidrectangle(x + 1, y + 1, x + G - 1, y + G - 1);
			}
	}
}

//�Ҽ����
void OnRButtonDown(int num) {
	int x, y, nx, ny;
	//��յ�Ԫ��
	for (x = 0; x < num; x++)
		for (y = 0; y < num; y++)
			grid.arr[x][y] = -1;

	//��Ԫ�����
	for (nx = 0; nx < num; nx++)
		for (ny = 0; ny < num; ny++) {
			setfillcolor(BLACK);
			x = nx * G + grid.left;
			y = ny * G + grid.up;
			solidrectangle(x + 1, y + 1, x + G - 1, y + G - 1);
		}
}
//�ж��Ƿ���������
int JudgeFull(int num, int arr[M][M]) {
	int c = -1;
	int nx = 0, ny = 0;
	while (nx < num && ny < num) {
		for (nx = 0; nx < num; nx++)
			for (ny = 0; ny < num; ny++)
				if (grid.arr[nx][ny] == 1)
					continue;
				else
					return c;
	}
	c = 1;
	return c;
}

//��һ��
void NextLevel(int num){
	//����
	BeginBatchDraw();
	for (int y = 0; y <= 500; y += 5) {
		setlinecolor(RGB(200, 30, 10));
		settextcolor(RGB(200, 30, 10));
		line(0, y, 680, y);//���ϵ���
		line(0, 500 - y, 680, 500 - y);//���µ���
		outtextxy(270, y, _T("Next_Level"));
		FlushBatchDraw();//ִ��δ��ɵĻ�������
		Sleep(20);
		setfillcolor(BLACK);
		solidrectangle(0, y, 680, y - 10);
		solidrectangle(0, 500 - y, 680, 500 - y + 10);
	}
	EndBatchDraw();

	//������һ�ظ���
	PaintGrid(340, 250, num, RGB(150, 0, 0));
}

//�������
int DisPatch() {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		switch (m.uMsg) {
		case WM_LBUTTONDOWN:
			OnLButtonDown(m, grid.num);//�����ɫ
			//�ж��Ƿ�����
			if (JudgeFull(grid.num, grid.arr) == 1) {
				grid.num++;
				//������Ŀ�������ֵͨ��
				if (grid.num > M) {
					return 1;
					break;
				}
				else
					NextLevel(grid.num);
			}
			break;
		case WM_RBUTTONDOWN:
			//�Ҽ����
			OnRButtonDown(grid.num);
			break;
		}
	}
}

