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
#define M 14    //������������
#define G 30    //���ӱ߳�

void welcome();                                             // ��ʾ��Ϸ������
void PaintGrid(int Mid_x, int Mid_y, int num, int color);   // ������Ϸ���ӣ���ʼ������
void OnLButtonDown(MOUSEMSG m, int num);                    // �������
void OnRButtonDown(int num);                                // �Ҽ�����
void NextLevel(int num);                                    // ��һ��
int  Dispatch();                                            // �ַ������Ϣ
int  JudgeFull(int num, int arr[M][M]);                     // �����Ƿ�����


															//������Ϸ���ӽṹ��
struct Grid
{
	int left;//������Χ�ĸ����򣬷�Ϊ��������
	int right;
	int up;
	int down;
	int arr[M][M];  // ��¼����״̬,ֵΪ1�����ɫ��-1����ɫ
	int num;        //��¼�߽������Ŀ
}grid;

int main()
{
	int end = 0;
	grid.num = 4;
	welcome();
	PaintGrid(320, 240, grid.num, RGB(0, 255, 0));
	while (end != 1)//û��ͨ�أ���Ϸ����
	{
		end = Dispatch();
	}
	closegraph();
	return 0;
}

// ��ʾ��Ϸ������
void welcome()
{
	// ��ʼ������
	initgraph(640, 480);
	// �����Ļ��ʾ
	// cleardevice();

	settextcolor(RGB(0, 255, 0));
	settextstyle(64, 0, _T("����"));
	outtextxy(70, 50, _T("Ϳ������Ϸ(���)"));

	settextcolor(WHITE);
	settextstyle(16, 0, _T("����"));
	outtextxy(100, 200, _T("ÿ��һ�����ӣ��������ҵĸ���Ҳ����������״�෴�Ķ���"));
	outtextxy(100, 240, _T("�ܹ�11�أ������ɫ���Ҽ�����"));

	// ʵ����˸��"�����������"
	int c = 255;
	while (!_kbhit())
	{
		settextcolor(RGB(0, c, 0));
		outtextxy(280, 400, _T("�����������"));
		c -= 8;
		if (c < 0)
			c = 255;
		Sleep(20);
	}

	//getch();
	cleardevice();
}

//������Ϸ����
//������mx:��Ļ�����x����  my:��Ļ�����y����
//num:���߸�����Ŀ  color:����������ɫ
void PaintGrid(int mx, int my, int num, int color)
{
	int x, y, nx, ny;
	//��Ϸ�����������±߽�����
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
	for (x = 20; x > 10; x--)
	{
		rectangle(grid.left - x, grid.up - x, grid.right + x, grid.down + x);

		Sleep(10);
	}
	//��յ�Ԫ��
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

// �������
void OnLButtonDown(MOUSEMSG m, int num)
{
	int nx, ny, x, y;//nx, ny��ʾ�����±�  x, y��ʾ���Ͻ�����

					 //�޶��������Χ
	if (m.x>grid.left && m.x<grid.right && m.y>grid.up && m.y<grid.down)
	{
		// ����λ�� ����ת�����±�
		nx = (int)(m.x - grid.left) / G;
		ny = (int)(m.y - grid.up) / G;

		// ת������״̬
		grid.arr[nx][ny] = -grid.arr[nx][ny];

		//�ұ�
		if (nx >= 0 && nx <  num - 1) grid.arr[nx + 1][ny] = -grid.arr[nx + 1][ny];
		//���
		if (nx >  0 && nx <= num - 1) grid.arr[nx - 1][ny] = -grid.arr[nx - 1][ny];
		//��
		if (ny >= 0 && ny <  num - 1) grid.arr[nx][ny + 1] = -grid.arr[nx][ny + 1];
		//��
		if (ny >  0 && ny <= num - 1) grid.arr[nx][ny - 1] = -grid.arr[nx][ny - 1];

		// ɨ����ɫ
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

// �Ҽ��������
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
/////////�жϸ����Ƿ�����        //////////////
/////////������                  //////////////
/////////num:    ���߸�����Ŀ    //////////////
/////////array:  �����������ʵ��//////////////
///////////////////////////////////////////////
int JudgeFull(int num, int array[M][M])
{
	int c = -1;//����״̬
	int nx = 0, ny = 0;
	while (nx<num && ny<num)
	{
		for (nx = 0; nx<num; nx++)
			for (ny = 0; ny<num; ny++)
				if (array[nx][ny] == 1)//������ά���飬���������ж���һ��λ��
					continue;
				else//����ֱ�ӷ���-1��������
					return c;
	}
	c = 1;
	return c;
}

// ��ʾ��һ��
// ������
// num:    ��һ�صı߽������
void NextLevel(int num)
{
	// ����
	BeginBatchDraw();
	for (int y = 0; y <= 480; y += 5)
	{
		setlinecolor(RGB(0, 255, 0));
		settextcolor(RGB(0, 255, 0));
		line(0, y, 640, y);//��������
		line(0, 480 - y, 640, 480 - y);//��������
		outtextxy(300, y, _T("��һ��"));
		FlushBatchDraw();// ִ��δ��ɵĻ�������
		Sleep(18);
		setfillcolor(BLACK);
		solidrectangle(0, y, 640, y - 10);//����
		solidrectangle(0, 480 - y, 640, 480 - y + 10);
	}
	EndBatchDraw();

	// ������һ�ظ���
	PaintGrid(320, 240, num, RGB(0, 255, 0));
}

int Dispatch()//����
{
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			// �����ɫ
			OnLButtonDown(m, grid.num);
			// �ж��Ƿ�����
			if (JudgeFull(grid.num, grid.arr) == 1)
			{
				grid.num++;
				// ������Ŀ�������ֵͨ��
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
			// �Ҽ����
			OnRButtonDown(grid.num);
			break;
		}
	}
}
