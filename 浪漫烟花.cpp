/********************************************************
*														*
*	�������ƣ�	����ף���̻�							*
*	���뻷����	VS2017 && easyX							*
*	������أ�	����									*
*	����޸ģ�	2018��2��21��							*
*														*
*********************************************************/
#include "stdafx.h"
#include <graphics.h>//ͼ��ͼ��ͷ�ļ�
#include <conio.h>//��Ļ����
#include <math.h>//��ѧͷ�ļ�
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>// windows�����ý���йصĴ�����ӿ�
#pragma comment (lib,"Winmm.lib")//����ָ������ڹ�������ӣ�winmm.lib���Ĺ���һ�������߱�����Ҫ����winmm��
/******�궨����******/

#define NUM 13		//�̻����������궨��
#define PI	3.1415927

/******�ṹ������******/

//�̻��ṹ
struct FIRE {
	int r;					//��ǰ��ը�뾶
	int max_r;				//��ը���ľ����Ե���뾶
	int x, y;				//��ը�����ڴ��ڵ�����
	int cen_x, cen_y;		//��ը�������ͼƬ���Ͻǵ�����
	int width, height;		//ͼƬ�Ŀ��
	int xy[240][240];		//�洢ͼƬ���ص�

	bool show;				//�Ƿ�����
	bool draw;				//��ʼ������ص�
	DWORD t1, t2, dt;		//�����ٶ�
} Fire[NUM];

//�̻����ṹ
struct JET {
	int x, y;				//���������
	int hx, hy;				//��ߵ�����------����ֵ��FIRE�����x,y
	int height;				//�̻��߶�
	bool shoot;				//�Ƿ���Է���

	DWORD t1, t2, dt;		//�����ٶ�
	IMAGE img[2];			//�洢����һ��һ��ͼƬ
	byte n : 1;				//ͼƬ�±�
}Jet[NUM];

/******����������******/

void welcome();//��ӭ����
void Init(int);//��ʼ���̻�
void Load();//����ͼƬ
void Chose(DWORD&);//ɸѡ�̻�
void Shoot();//�����̻�
void Show(DWORD*);//�����̻�
void Style(DWORD&);//������ʽ

int main() {
	initgraph(1200, 800);
	srand(time(0));

	//���ű�������
	mciSendString(_T("open ./fire/С����.mp3 alias bk"), 0, 0, 0);//��С����alias��ȡ����)Ϊbk
	mciSendString(_T("play bk"), 0, 0, 0);//����bk(С����)

	welcome();

	DWORD t1 = timeGetTime();//�ú����õ���ʱ���ĵ�ǰֵ(ɸѡ�̻���ʱ)
	DWORD st1 = timeGetTime();//���Ż�����ʱ
	DWORD *pMem = GetImageBuffer();//��ȡ�����Դ�ָ��

	for (int i = 0; i < NUM; i++) {//��ʼ���̻�
		Init(i);
	}
	Load();	// ���̻�ͼƬ��Ϣ���ؽ���Ӧ�ṹ��
	BeginBatchDraw();		//��ʼ������ͼ

	while (!_kbhit()) {
		Sleep(10);

		//���ѡ��4000�����ص����������Ч����
		for (int clr = 0; clr < 1000; clr++) {
			for (int j = 0; j < 2; j++) {
				int px1 = rand() % 1200;
				int py1 = rand() % 800;

				if (py1 < 799) {//��ֹԽ��
					pMem[py1 * 1200 + px1] = pMem[py1 * 1200 + px1 + 1] = BLACK;//���Դ渳ֵ�������ص�
				}
			}
		}

		Chose(t1);//ɸѡ�̻�
		Shoot();//�����̻�
		Show(pMem);//�����̻�
		Style(st1);//��������
		FlushBatchDraw();//��ʾǰ������л�ͼ����
	}
	while (1);
	return 0;
}

//��ӭ����
void welcome() {

	setcolor(YELLOW);//������ɫΪ��ɫ

	for (int i = 0; i < 50; i++) {//��ȡ��ʮ����

								  //Բ����ѧ��ʽ
		int x = 600 + int(180 * sin(PI * 2 * i / 60));//�켣x = Բ��x + ���뾶 * sin( PI * 2 * i / 60 ) )
		int y = 200 + int(180 * cos(PI * 2 * i / 60));//�켣y = Բ��y + ���뾶 * cos( PI * 2 * i / 60 ) )

		cleardevice();//����
		settextstyle(i, 0, _T("����"));
		outtextxy(x - 20, y, _T("�װ��ģ����"));
		outtextxy(x + 60, y + 100, _T("���ҵ�X��ɭ"));
		Sleep(25);

	}
	getchar();

	cleardevice();//����
	int r = 0;
	while (!_kbhit()) {
		settextcolor(RGB(80, r, 0));//����������ɫ
		settextstyle(25, 0, _T("����"));//����������ʽ��25����0��
		outtextxy(400, 200, _T("����������������"));//��ָ��λ�ã�400��200������ַ���
		outtextxy(400, 250, _T("����������������"));
		outtextxy(400, 300, _T("����������������"));
		outtextxy(400, 350, _T("����������������"));
		outtextxy(400, 400, _T("����������������"));
		outtextxy(400, 450, _T("����������������"));
		outtextxy(700, 500, _T("--����"));
		if (r > 240) {
			r = 0;
		}
		r += 5;
		Sleep(100);
	}
	getchar();

}


void Init(int i) {
	// �ֱ�Ϊ���̻����ĵ�ͼƬ��Ե����Զ���롢�̻����ĵ�ͼƬ���Ͻǵľ��� (x��y) ��������
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	//��ʼ���̻�
	Fire[i].x = 0;					//�̻���������
	Fire[i].y = 0;
	Fire[i].width = 240;			// ͼƬ��
	Fire[i].height = 240;			// ͼƬ��
	Fire[i].max_r = r[i];			// ���뾶
	Fire[i].cen_x = x[i];			// ���ľ����ϽǾ���
	Fire[i].cen_y = y[i];
	Fire[i].show = false;			// �Ƿ�����
	Fire[i].dt = 5;					// ����ʱ����
	Fire[i].t1 = timeGetTime();
	Fire[i].r = 0;					// �� 0 ��ʼ����

									//��ʼ���̻���
	Jet[i].x = -240;				// �̻������Ͻ�����
	Jet[i].y = -240;
	Jet[i].hx = -240;				// �̻���������ߵ�����
	Jet[i].hy = -240;
	Jet[i].height = 0;				// ����߶�
	Jet[i].t1 = timeGetTime();
	Jet[i].dt = rand() % 10;		// �����ٶ�ʱ����(0-9)
	Jet[i].n = 0;				// �̻�����˸ͼƬ�±�
	Jet[i].shoot = false;			// �Ƿ���
}


void Load() {
	//�洢�̻������ص���ɫ
	IMAGE fm, gm;
	loadimage(&fm, _T("./fire/flower.jpg"), 3120, 240);//��("./fire/flower.jpg")ͼƬ���浽fm��ͼƬ��С3120*240

	for (int i = 0; i < 13; i++) {
		SetWorkingImage(&fm);//���ã�set�����ڹ����ģ�working��ͼƬ����image��
		getimage(&gm, i * 240, 0, 240, 240);//��ȡͼƬ��ͼƬ���浽gm��ͼƬx��ͼƬy��ͼƬ�ߣ�ͼƬ��

		SetWorkingImage(&gm);//�������ڹ�����ͼƬ��gm��
		for (int a = 0; a < 240; a++) {
			for (int b = 0; b < 240; b++) {
				Fire[i].xy[a][b] = getpixel(a, b);//������ص�
			}
		}
	}


	//�����̻���
	IMAGE sm;
	loadimage(&sm, _T("./fire/shoot.jpg"), 200, 50);

	for (int i = 0; i < 13; i++) {
		SetWorkingImage(&sm);//���ڹ�����ͼƬsm
		int n = rand() % 5;//���ȡnֵ��0-4����ʹ���̻������

		getimage(&Jet[i].img[0], n * 20, 0, 20, 50);//ͼƬ���浽Jet[i].img[0]��ͨ��n��ȷ��ͼƬ�����Ͻ����꣨��ɫ�̻�����
		getimage(&Jet[i].img[1], (n + 5) * 20, 0, 20, 50);//ͼƬ���浽Jet[i].img[1]��ͨ��n��ȷ��ͼƬ�����Ͻ����꣨��ɫ�̻�����
	}

	SetWorkingImage();//���ûػ�ͼ����
}

//ɸѡ�ɷ�����̻�
void Chose(DWORD& t1) {
	DWORD t2 = timeGetTime();

	if (t2 - t1 > 100) {
		int n = rand() % 20;

		if (n < 13 && Jet[n].shoot == false && Fire[n].show == false) {
			//�����̻�����Ԥ������
			Jet[n].x = rand() % 1200;
			Jet[n].y = rand() % 100 + 600;
			Jet[n].hx = Jet[n].x;
			Jet[n].hy = rand() % 400;
			Jet[n].height = Jet[n].y - Jet[n].hy;
			Jet[n].shoot = true;
			putimage(Jet[n].x, Jet[n].y, &Jet[n].img[Jet[n].n], SRCINVERT);//(����x,����y,ͼƬ,����ͼ���Ժ��ַ�ʽ�������Ļ��)
		}
		t1 = t2;
	}
}


//ɨ���̻���������
void Shoot() {
	for (int i = 0; i < 13; i++) {
		Jet[i].t2 = timeGetTime();

		if (Jet[i].t2 - Jet[i].t1 > Jet[i].dt&&Jet[i].shoot == true) {
			//�̻���������
			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);

			if (Jet[i].y > Jet[i].hy) {
				Jet[i].n++;
				Jet[i].y -= 5;
			}

			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);
			//�������߶ȵ�3/4,����
			if ((Jet[i].y - Jet[i].hy) * 4 < Jet[i].height)
				Jet[i].dt = rand() % 4 + 10;

			//���������߶�
			if (Jet[i].y <= Jet[i].hy) {
				putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);//�����̻���
				Fire[i].x = Jet[i].hx + 10;//���̻����м䱬ը
				Fire[i].y = Jet[i].hy;//����ߵ�����
				Fire[i].show = true;//��ʼ����
				Jet[i].shoot = false;//ֹͣ����

			}
			Jet[i].t1 = Jet[i].t2;
		}
	}
}




void Show(DWORD* pMem) {
	//�̻����׶�����ʱ������������������Ч��
	int drt[16] = { 5,5,5,5,5,6,25,25,25,25,25,55,55,55,55,55 };

	for (int i = 0; i < NUM; i++) {
		Fire[i].t2 = timeGetTime();

		//���ӱ�ը�뾶�������̻�������ʱ����������Ч��
		if (Fire[i].t2 - Fire[i].t1 > Fire[i].dt && Fire[i].show == true) {
			if (Fire[i].r < Fire[i].max_r) {
				Fire[i].r++;
				Fire[i].dt = drt[Fire[i].r / 10];
				Fire[i].draw = true;
			}

			if (Fire[i].r >= Fire[i].max_r - 1) {
				Fire[i].draw = false;
				Init(i);
			}
			Fire[i].t1 = Fire[i].t2;
		}

		//����ú��ڻ��ɱ�ը�����ݵ�Ǯ��ը�뾶���̻�����ɫֵ�ӽ���ɫ�Ĳ����
		if (Fire[i].draw) {
			for (double a = 0; a <= 6.28; a += 0.01) {
				int x1 = (int)(Fire[i].cen_x + Fire[i].r*cos(a));// �����ͼƬ���Ͻǵ�����
				int y1 = (int)(Fire[i].cen_y - Fire[i].r*sin(a));

				if (x1 > 0 && x1 < Fire[i].width&&y1>0 && y1 < Fire[i].height) {// ֻ���ͼƬ�ڵ����ص�
					int b = Fire[i].xy[x1][y1] & 0xff;
					int g = (Fire[i].xy[x1][y1] >> 8) & 0xff;
					int r = (Fire[i].xy[x1][y1] >> 16);

					//�̻����ص��ڴ����ϵ�����
					int xx = (int)(Fire[i].x + Fire[i].r*cos(a));
					int yy = (int)(Fire[i].y - Fire[i].r*sin(a));

					//�ϰ������ص㲻�������ֹԽ��
					if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800) {
						pMem[yy * 1200 + xx] = BGR(Fire[i].xy[x1][y1]);//�Դ���������̻�
					}
				}
				Fire[i].draw = false;
			}
		}
	}
}



void Style(DWORD& st1) {
	DWORD st2 = timeGetTime();

	if (st2 - st1 > 20000) {//һ�׸��ʱ��
		//��������
		int x[13] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
		int y[13] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };
		for (int i = 0; i < NUM; i++) {
			//���ɷֲ��̻���
			Jet[i].x = x[i] * 10;
			Jet[i].y = (y[i] + 75) * 10;
			Jet[i].hx = Jet[i].x;
			Jet[i].hy = y[i] * 10;
			Jet[i].height = Jet[i].y - Jet[i].hy;
			Jet[i].shoot = true;
			Jet[i].dt = 7;
			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);//��ʾ�̻���


			//�����̻�����
			Fire[i].x = Jet[i].x + 10;
			Fire[i].y = Jet[i].hy;
			Fire[i].show = false;
			Fire[i].r = 0;
		}
		st1 = st2;
	}
}
