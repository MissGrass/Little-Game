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
#define M 14    //单边最大格子数
#define G 30    //格子边长

void welcome();                                             // 显示游戏主界面
void PaintGrid(int Mid_x, int Mid_y, int num, int color);   // 绘制游戏格子，初始化格子
void OnLButtonDown(MOUSEMSG m, int num);                    // 左键按下
void OnRButtonDown(int num);                                // 右键按下
void NextLevel(int num);                                    // 下一关
int  Dispatch();                                            // 分发鼠标信息
int  JudgeFull(int num, int arr[M][M]);                     // 格子是否填满


															//定义游戏格子结构体
struct Grid
{
	int left;//格子周围四个区域，分为上下左右
	int right;
	int up;
	int down;
	int arr[M][M];  // 记录格子状态,值为1填充绿色，-1填充黑色
	int num;        //记录边界格子数目
}grid;

int main()
{
	int end = 0;
	grid.num = 4;
	welcome();
	PaintGrid(320, 240, grid.num, RGB(0, 255, 0));
	while (end != 1)//没有通关，游戏继续
	{
		end = Dispatch();
	}
	closegraph();
	return 0;
}

// 显示游戏主界面
void welcome()
{
	// 初始化窗口
	initgraph(640, 480);
	// 输出屏幕提示
	// cleardevice();

	settextcolor(RGB(0, 255, 0));
	settextstyle(64, 0, _T("黑体"));
	outtextxy(70, 50, _T("涂格子游戏(点灯)"));

	settextcolor(WHITE);
	settextstyle(16, 0, _T("宋体"));
	outtextxy(100, 200, _T("每点一个格子，上下左右的格子也会做出于现状相反的动作"));
	outtextxy(100, 240, _T("总共11关，左键填色，右键重来"));

	// 实现闪烁的"按任意键继续"
	int c = 255;
	while (!_kbhit())
	{
		settextcolor(RGB(0, c, 0));
		outtextxy(280, 400, _T("按任意键继续"));
		c -= 8;
		if (c < 0)
			c = 255;
		Sleep(20);
	}

	//getch();
	cleardevice();
}

//绘制游戏格子
//参数：mx:屏幕中央的x坐标  my:屏幕中央的y坐标
//num:单边格子数目  color:格子线条颜色
void PaintGrid(int mx, int my, int num, int color)
{
	int x, y, nx, ny;
	//游戏区域左右上下边界坐标
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
	for (x = 20; x > 10; x--)
	{
		rectangle(grid.left - x, grid.up - x, grid.right + x, grid.down + x);

		Sleep(10);
	}
	//清空单元格
	for (x = 0; x < num; x++)
		for (y = 0; y < num; y++)
		{
			grid.arr[x][y] = -1;
		}

	for (nx = 0; nx < num; nx++)
		for (ny = 0; ny < num; ny++)
		{
			setfillcolor(BLACK);
			x = nx * G + grid.left;
			y = ny * G + grid.up;
			solidrectangle(x + 1, y + 1, x + G - 1, y + G - 1);
		}
}

// 左键按下
void OnLButtonDown(MOUSEMSG m, int num)
{
	int nx, ny, x, y;//nx, ny表示数组下标  x, y表示左上角坐标

					 //限定鼠标点击范围
	if (m.x>grid.left && m.x<grid.right && m.y>grid.up && m.y<grid.down)
	{
		// 计算位置 坐标转换成下标
		nx = (int)(m.x - grid.left) / G;
		ny = (int)(m.y - grid.up) / G;

		// 转换格子状态
		grid.arr[nx][ny] = -grid.arr[nx][ny];

		//右边
		if (nx >= 0 && nx <  num - 1) grid.arr[nx + 1][ny] = -grid.arr[nx + 1][ny];
		//左边
		if (nx >  0 && nx <= num - 1) grid.arr[nx - 1][ny] = -grid.arr[nx - 1][ny];
		//下
		if (ny >= 0 && ny <  num - 1) grid.arr[nx][ny + 1] = -grid.arr[nx][ny + 1];
		//上
		if (ny >  0 && ny <= num - 1) grid.arr[nx][ny - 1] = -grid.arr[nx][ny - 1];

		// 扫描填色
		for (nx = 0; nx<num; nx++)
			for (ny = 0; ny<num; ny++)
			{
				if (grid.arr[nx][ny] == 1)
					setfillcolor(GREEN);
				else
					setfillcolor(BLACK);
				x = nx * G + grid.left;
				y = ny * G + grid.up;
				solidrectangle(x + 1, y + 1, x + G - 1, y + G - 1);
			}
	}
}

// 右键按下清空
void OnRButtonDown(int num)
{
	int x, y, nx, ny;

	for (x = 0; x<num; x++)
		for (y = 0; y<num; y++)
			grid.arr[x][y] = -1;

	for (nx = 0; nx<num; nx++)
		for (ny = 0; ny<num; ny++)
		{
			setfillcolor(BLACK);
			x = nx * G + grid.left;
			y = ny * G + grid.up;
			solidrectangle(x + 1, y + 1, x + G - 1, y + G - 1);
		}
}


///////////////////////////////////////////////
/////////判断格子是否填满        //////////////
/////////参数：                  //////////////
/////////num:    单边格子数目    //////////////
/////////array:  生成数组接收实参//////////////
///////////////////////////////////////////////
int JudgeFull(int num, int array[M][M])
{
	int c = -1;//格子状态
	int nx = 0, ny = 0;
	while (nx<num && ny<num)
	{
		for (nx = 0; nx<num; nx++)
			for (ny = 0; ny<num; ny++)
				if (array[nx][ny] == 1)//遍历二维数组，亮的重新判断下一个位置
					continue;
				else//否则直接返回-1函数结束
					return c;
	}
	c = 1;
	return c;
}

// 显示下一关
// 参数：
// num:    下一关的边界格子数
void NextLevel(int num)
{
	// 清屏
	BeginBatchDraw();
	for (int y = 0; y <= 480; y += 5)
	{
		setlinecolor(RGB(0, 255, 0));
		settextcolor(RGB(0, 255, 0));
		line(0, y, 640, y);//从上往下
		line(0, 480 - y, 640, 480 - y);//从下往上
		outtextxy(300, y, _T("下一关"));
		FlushBatchDraw();// 执行未完成的绘制任务
		Sleep(18);
		setfillcolor(BLACK);
		solidrectangle(0, y, 640, y - 10);//擦除
		solidrectangle(0, 480 - y, 640, 480 - y + 10);
	}
	EndBatchDraw();

	// 绘制下一关格子
	PaintGrid(320, 240, num, RGB(0, 255, 0));
}

int Dispatch()//调度
{
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			// 左键填色
			OnLButtonDown(m, grid.num);
			// 判断是否填满
			if (JudgeFull(grid.num, grid.arr) == 1)
			{
				grid.num++;
				// 格子数目超过最大值通关
				if (grid.num>M)
				{
					return 1;
					break;
				}
				else
					NextLevel(grid.num);
			}
			break;

		case WM_RBUTTONDOWN:
			// 右键清除
			OnRButtonDown(grid.num);
			break;
		}
	}
}
