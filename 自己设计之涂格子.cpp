// 我的涂格子练习.cpp: 定义控制台应用程序的入口点。
//
//Visual studio 2017版本下运行，easyX图形库 
/*
二维数组
结构体
游戏欢迎界面
游戏主界面
左键按下填色
右键按下重来
判断游戏是否结束
进入下一关
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
	int left;//格子左右上下
	int right;
	int up;
	int down;
	int arr[M][M];//二维数组创建格子，-1为不亮，1为亮
	int num;//边界格子数
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

//游戏主界面
void welcome() {
	//初始化界面
	initgraph(680, 500);

	//标题
	settextcolor(RGB(50,100,100));
	settextstyle(60, 0, _T("楷体"));
	outtextxy(180, 60, _T("点灯小游戏"));

	//提示玩法文字
	settextcolor(WHITE);
	settextstyle(20, 0, _T("楷体"));
	outtextxy(50,200,_T("点击方格，方格及方格的上下左右格子，采用偶消奇不消的规律来填图"));
	outtextxy(10, 240, _T("直到方格被涂满，则进行下一关;鼠标左击点亮，右击重置"));

	//实现闪烁文字，按任意键继续
	int c = 255;
	while (!_kbhit()) {
		settextcolor(RGB(0, c, 0));
		settextstyle(30, 0, _T("楷体"));
		outtextxy(230, 400, _T("^_^按任意键继续"));
		c -= 8;
		if (c < 0) {
			c = 255;
		}
		Sleep(20);
	}
	//继续则清屏
	cleardevice();
}

void PaintGrid(int mx, int my, int num, int color) {
	int c = 255;
	int p = 0;
	while (p<100) {
		settextcolor(RGB(0,0,c));
		settextstyle(30, 0, _T("楷体"));
		outtextxy(250, 60, _T("加油FIGHTING！"));
		c -= 8;
		if (c < 0) {
			c = 255;
		}
		p++;
		Sleep(18);
	}
	

	int x, y, nx, ny;
	//游戏区域上下左右边界坐标
	grid.left = mx - num * G / 2;
	grid.right = mx + num * G / 2;
	grid.up = my - num * G / 2;
	grid.down = my + num * G / 2;

	//绘制格子
	setlinecolor(color);
	for (x = grid.left; x <= grid.right; x += G)
		line(x, grid.up, x, grid.down);
	for (y = grid.up; y <= grid.down; y += G)
		line(grid.left, y, grid.right, y);

	//外边框
	for (x = 20; x >= 10; x--) {
		rectangle(grid.left - x, grid.up - x, grid.right + x, grid.down + x);
		Sleep(40);
	}
	
	//清空单元格
	for (x = 0; x < num; x++)
		for (y = 0; y < num; y++)
			grid.arr[x][y] = -1;

	//单元格填充
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
		settextstyle(30, 0, _T("楷体"));
		outtextxy(250, 400, _T("加油FIGHTING！"));
		c -= 8;
		if (c < 0) {
			c = 255;
		}
		q++;
		Sleep(20);
	}
}

//左键按下
void OnLButtonDown(MOUSEMSG m, int num) {
	int nx, ny, x, y;
	if (m.x > grid.left && m.x < grid.right && m.y > grid.up && m.y < grid.down) {
		//计算坐标转换成数组下标
		nx = (int)(m.x - grid.left) / G;
		ny = (int)(m.y - grid.up) / G;

		//转换格子状态
		grid.arr[nx][ny] = -grid.arr[nx][ny];
		
		if (nx >= 0 && nx < num - 1)
			grid.arr[nx + 1][ny] = -grid.arr[nx + 1][ny];//右边
		if (nx > 0 && nx <= num - 1)
			grid.arr[nx - 1][ny] = -grid.arr[nx - 1][ny];//左边
		if (ny >= 0 && ny < num - 1)
			grid.arr[nx][ny + 1] = -grid.arr[nx][ny + 1];//下
		if (ny > 0 && ny <= num - 1)
			grid.arr[nx][ny - 1] = -grid.arr[nx][ny - 1];//上

		//扫描填色
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

//右键清除
void OnRButtonDown(int num) {
	int x, y, nx, ny;
	//清空单元格
	for (x = 0; x < num; x++)
		for (y = 0; y < num; y++)
			grid.arr[x][y] = -1;

	//单元格填充
	for (nx = 0; nx < num; nx++)
		for (ny = 0; ny < num; ny++) {
			setfillcolor(BLACK);
			x = nx * G + grid.left;
			y = ny * G + grid.up;
			solidrectangle(x + 1, y + 1, x + G - 1, y + G - 1);
		}
}
//判断是否填满过关
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

//下一关
void NextLevel(int num){
	//清屏
	BeginBatchDraw();
	for (int y = 0; y <= 500; y += 5) {
		setlinecolor(RGB(200, 30, 10));
		settextcolor(RGB(200, 30, 10));
		line(0, y, 680, y);//从上到下
		line(0, 500 - y, 680, 500 - y);//从下到上
		outtextxy(270, y, _T("Next_Level"));
		FlushBatchDraw();//执行未完成的绘制任务
		Sleep(20);
		setfillcolor(BLACK);
		solidrectangle(0, y, 680, y - 10);
		solidrectangle(0, 500 - y, 680, 500 - y + 10);
	}
	EndBatchDraw();

	//绘制下一关格子
	PaintGrid(340, 250, num, RGB(150, 0, 0));
}

//鼠标坐标
int DisPatch() {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		switch (m.uMsg) {
		case WM_LBUTTONDOWN:
			OnLButtonDown(m, grid.num);//左键填色
			//判断是否填满
			if (JudgeFull(grid.num, grid.arr) == 1) {
				grid.num++;
				//格子数目超过最大值通关
				if (grid.num > M) {
					return 1;
					break;
				}
				else
					NextLevel(grid.num);
			}
			break;
		case WM_RBUTTONDOWN:
			//右键清除
			OnRButtonDown(grid.num);
			break;
		}
	}
}

