#include <iostream>
#include<stdio.h>
#include<easyx.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <graphics.h>
#include <string.h>
#include<mmsystem.h>    //��ý���ļ�
#pragma comment(lib,"winmm.lib")    //ý�����ӿ��ļ�
#include <process.h>  //��ʱ���߳�
/*---------------------------�������---------------------------------------------*/
#define WIDTH 1024
#define HEIGHT 640
#define map_WIDTH (WIDTH)*8
#define map_HEIGHT (HEIGHT)*8
#define FOOD_NUM 4000
#define AINUM 200
#define DISTANCE(x1, y1, x2, y2)	(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)))
struct ball//��Ľṹ
{
	int x;
	int y;
	double  r;
	bool flag;	//�Ƿ���
	DWORD color; //��ɫ
	double speed; //�ٶ�

};
struct ball player;
struct ball food[FOOD_NUM];
struct ball ai[AINUM];
struct UserData
{
	char name[10];     //�û���
	char id[10];        //�˺�
	char password[10];  //����
	int grade1;    //����߷�
	int grade2;    //��ͨ��߷�
	int grade3;    //������߷�
	int allgrade;   //�ܻ���
}User[1000], user;
int N = 0;
int Speed = 0;
int xx = 0;
float score = 0;
int flaggrade = 0;
int flaggrade1 = 0;
IMAGE map(map_WIDTH, map_HEIGHT); //��ͼ ͼƬ
POINT g_camreaPos;   //���������
/*---------------------------�������---------------------------------------------*/



/*-----------------------------view-----------------------------------------------*/
/*
�����ˣ���
���ܣ�����
����ֵ��void
����ֵ��void
*/
void end();
/*
�����ˣ����ϼ���
���ܣ���¼����
1.��ӡ��¼����ѡ��
2.�����û�����
3.�����ws�޸Ĺ��λ��
  ����ǻس�: �����Ӧѡ��
  ��¼�����õ�¼���� ��Ҫ��¼��������¼���ܽ���˵�
  ע�᣺����ע�ắ�� ��Ҫע�ắ��
  �˳�������exit(0);
  ����ֵ��void
����ֵ��void
*/
void Begin();
/*
�����ˣ���
���ܣ����尴ť
����ֵ��void
����ֵ��void
*/
void button(int x, int y, int w, int h, const char* text);
/*
�����ˣ���
���ܣ��û����棨�˵���
1.��ӡ�û�����ѡ��
2.�����û�����
3.�����ws�޸Ĺ��λ��
  ����ǻس�: �����Ӧѡ��
  ������Ϸ������ѡ���ѶȽ��� ��Ҫѡ���ѶȺ���
  Ƥ��������Ƥ������ ��ҪƤ������
  ���а񣺵������а���� ��Ҫ���а���
  ���ң����ÿ��ҽ��� ��Ҫ���Һ���
  ���ص�¼�����õ�¼����
  ���ã��������ý��� ��Ҫ���ú���
  ����ֵ��void
����ֵ��void
*/
void MenuView();
/*
�����ˣ�����̫��
���ܣ���������Բ�ľ�
 ����ֵ��void
����ֵ��void
*/
double distance(struct ball* b1, struct ball* b2);
/*
�����ˣ�����
���ܣ�׷���㷨
 ����ֵ��void
����ֵ��void
*/
void Chase(struct ball* chase, struct ball* run);
/*
�����ˣ����ϼ���
���ܣ���¼�н���
1.��ӡ��¼�н���
2.�����û�����
����ֵ��void
����ֵ��void
*/
void Login();
/*
�����ˣ����ϼ���
���ܣ���¼���ж�
�����û����������Ƿ���ȷ�Ҳ��Ҵ洢�ĵ����Ƿ��и��û�
����ֵ��void
����ֵ������1���˺Ŵ���  ����2���������  ����3����ȷ
*/
int LoginJudge();
/*
�����ˣ����ϼ���
���ܣ���¼�б�������
����ֵ��void
����ֵ��void
*/
void LoginDraw();  //��½�б�������
/*
�����ˣ����ϼ���
���ܣ�ע����
1.��ӡע���н���
2.�����û�����
����ֵ��void
����ֵ��void
*/
void Register();    //ע���н���
/*
�����ˣ����ϼ���
���ܣ�ע�����ж�
�����û��������Ϣ��ʽ�Ƿ�淶�Ҳ��Ҵ洢�ĵ����Ƿ����и��û�
����ֵ��void
����ֵ������0���û�����ʽ����, ����1���˺Ÿ�ʽ����  ����2�������ʽ����  ����3����ȷ
*/
int RegisterJudge();
/*
�����ˣ����ϼ���
���ܣ�ע���б�������
����ֵ��void
����ֵ��void
*/
void RegisterDraw();
/*
�����ˣ�����
���ܣ�ѡ���Ѷ�
1.��ӡѡ���ѶȽ���
2.ӵ�������Ѷȡ��򵥡������ѡ���������
3.ѡ���ѶȺ��޸�aiС��Ĵ�С���ٶ�
4.������Ϸ����
����ֵ��void
����ֵ��void
*/
void Choose();
/*
�����ˣ���
���ܣ������ڴ�
����ֵ��void
����ֵ��void
*/
void Skin();
/*
�����ˣ����ϼ���
���ܣ�չʾ���а�
1.��ӡ���а����
2.����һ����ť���ز˵�
����ֵ��void
����ֵ��void
*/
void Rank();
/*
�����ˣ�Neal
���ܣ����ҵ�����ʼ����
1.��ӡ���ҽ���
2.�����û�����Ķһ��벢�˶���ͨ����ɽ��ж������ʼ��С���ٶȽ����޸�
3.�����޸ĵĳ�ʼ�ٶȼ���С
4.����һ����ť���ز˵�
����ֵ��void
����ֵ��void
*/
void Cheat();
/*
�����ˣ�Neal
���ܣ�����
1.��ӡ���ý���
2.��w s�ƶ����س�ȷ�����ֿ����
3.����һ����ť���ز˵�
����ֵ��void
����ֵ��void
*/
void Set();
/*
�����ˣ���
���ܣ���������
����Ϸ��ʼ��
whlie(1){
����˫�����ͼ
���û��ƺ���
���ò�������
������ҳ�ʳ�ﺯ��
����ai����һ��Ժ���
����ai�ƶ�����

}
��Ϸʤ��ѡ���Ƿ�¼�����а�
���ǵ���¼�뺯�����ɼ�¼�����а�
����ֵ��void
����ֵ��void
*/
void GameView();
/*
�����ˣ�����
���ܣ����ƣ�����Ai��ʳ�
�������
����ʳ��
����ai
������Ϸ���棨ʱ�䣬������λ�ã�
����ֵ��void
����ֵ��void
*/
void draw();
/*-----------------------------view-----------------------------------------------*/



/*-----------------------------service-------------------------------------------*/
/*
�����ˣ���
���ܣ���wsad��������ƶ�
���ո�ʹС��������С�ٶȱ��
����ֵ��void
����ֵ��void
*/
void playermove();
/*
�����ˣ�����
���ܣ���ʼ���ٶ�
�������������
��ʼ�����
��ʼ��ʳ��
��ʼ��ai
����ֵ��void
����ֵ��void
*/
void initspeed();
/*
�����ˣ�����
���ܣ���ʼ��
�������������
��ʼ�����
��ʼ��ʳ��
��ʼ��ai
����ֵ��void
����ֵ��void
*/
void init();
/*
�����ˣ�����
���ܣ�����ʳ��
����ֵ��void
����ֵ��void
*/
void creatfood(int i);
/*
�����ˣ�����
���ܣ�����ai
����ֵ��void
����ֵ��void
*/
void creatai(int i);
/*
�����ˣ�//
���ܣ�����
����ҳԵ�ai��ʳ��ʱ���ӷ���
����ֵ��void
����ֵ��void
*/
void Score();
/*
�����ˣ���Ȼ��֮
���ܣ���ҳ�ʳ�ﲢ����뾶����������
����ֵ��void
����ֵ��void
*/
void gamerEatfood();
/*
�����ˣ����
���ܣ�ai��ai
����ֵ��void
����ֵ��void
*/
void gamerAndai();
/*
�����ˣ�����
���ܣ�ai��ai
����ֵ��void
����ֵ��void
*/
void aiEatai();
/*
�����ˣ�����
���ܣ�ai��ʳ��
����ֵ��void
����ֵ��void
*/
void aiEatfood();
/*
�����ˣ�����
���ܣ�ai���ƶ�
����ֵ��void
����ֵ��void
*/
void aiMove();
/*-----------------------------service-------------------------------------------*/


/*-----------------------------dao-----------------------------------------------*/
/*
�����ˣ����ϼ���
���ܣ������ļ�
����ֵ��void
����ֵ��void
*/
void SaveFile();
/*
�����ˣ����ϼ���
���ܣ� ��ʼ���ļ�
����ֵ��void
����ֵ��void
*/
void InitFile();
/*
�����ˣ����ϼ���
���ܣ�ע��ɹ��������û�
����ֵ��void
����ֵ��void
*/
void Append();
/*
�����ˣ����ϼ���
���ܣ�չʾ���а�
����ֵ��void
����ֵ��void
*/
void Rank();
/*
�����ˣ����ϼ���
���ܣ����а񱳾�����
����ֵ��void
����ֵ��void
*/
void RankDraw();
/*
�����ˣ����ϼ���
���ܣ��������û������ܷ�����
����ֵ��void
����ֵ��void
*/
void sort();
/*-------------------------------dao------------------------------------------------*/



void button(int x, int y, int w, int h, const char* text) {
	setbkmode(TRANSPARENT);
	setfillcolor(BLUE);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextstyle(30, 0, "����");
	char text1[20] = "button";
	strcpy(text1, text);
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, text);
}

void MenuView()
{
	initgraph(1024, 640);
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "�˵�");
	IMAGE img;
	loadimage(&img, "./pictures/Bk11.png", 1024, 640);
	cleardevice();
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, "����");
	button(437, 155, 150, 50, "������Ϸ");
	button(437, 225, 150, 50, "Ƥ��");
	button(437, 295, 150, 50, "���а�");
	button(437, 365, 150, 50, "����");
	button(437, 435, 150, 50, "���ص�¼");
	button(437, 505, 150, 50, "����");

	ExMessage msg;
	while (1) {

		if (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				if (msg.x >= 437 && msg.x <= 437 + 150 && msg.y >= 155 && msg.y <= 155 + 50) {
					Choose();
				}
				if (msg.x >= 437 && msg.x <= 437 + 150 && msg.y >= 225 && msg.y <= 225 + 50) {
					Skin();
				}
				if (msg.x >= 437 && msg.x <= 437 + 150 && msg.y >= 295 && msg.y <= 295 + 50) {
					Rank();
				}
				if (msg.x >= 437 && msg.x <= 437 + 150 && msg.y >= 365 && msg.y <= 365 + 50) {
					Cheat();
				}
				if (msg.x >= 437 && msg.x <= 437 + 150 && msg.y >= 435 && msg.y <= 435 + 50) {
					Begin();
				}
				if (msg.x >= 437 && msg.x <= 437 + 150 && msg.y >= 505 && msg.y <= 505 + 50) {
					Set();
				}
				break;
			}
		}
		FlushBatchDraw();
		//Sleep(100);
	}
	getchar();
	closegraph();
}

void Choose()
{
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "ѡ���Ѷ�");
	//initgraph(1024, 640, 1);
	IMAGE bk;
	cleardevice();
	loadimage(&bk, "./pictures/chose.png", WIDTH, HEIGHT);
	putimage(0, 0, &bk);
	//EndBatchDraw();
	ExMessage msg;
	while (1)
	{

		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 400 && msg.x <= 640 && msg.y >= 130 && msg.y <= 200)
			{
				flaggrade = 1;
				//printf("��\0");
				Speed = 3;
				GameView();
				break;
			}
			if (msg.x >= 400 && msg.x <= 640 && msg.y >= 270 && msg.y <= 340)
			{
				flaggrade = 2;
				//printf("��ͨ\0");
				Speed = 6;
				GameView();
				break;
			}
			if (msg.x >= 400 && msg.x <= 640 && msg.y >= 420 && msg.y <= 490)
			{
				flaggrade = 3;
				//printf("����\0");
				Speed = 9;
				GameView();
				break;
			}
		}
		FlushBatchDraw();
	}
}

void Skin()
{
	MessageBox(GetHWnd(), "�����ڴ�", "ע�⣡����", MB_OK);
}

void Cheat()
{
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);  //���Ƴ�ʼ����
	// ���ݻ���ֵ
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "����");
	int oldlinecolor = getlinecolor();
	int oldbkcolor = getbkcolor();
	int oldfillcolor = getfillcolor();

	//���Ʊ���
	IMAGE bk;
	cleardevice();
	loadimage(&bk, "./pictures/Bk11.png", WIDTH, HEIGHT);
	putimage(0, 0, &bk);

	//�����ʼ����
	int left = 312, top = 250, right = 712, bottom = 300;	//���������
	int bleft = 830, btop = 520;									//���ذ�ť����
	char text[100];											//��ʼ���ַ���
	memset(text, 0, 100);
	//���Ʊ���
	settextcolor(BLACK);
	settextstyle(100, 0, "΢���ź�");
	setbkmode(TRANSPARENT);
	outtextxy((1024 - textwidth("�һ���")) / 2, 100, "�һ���");

	setlinecolor(LIGHTGRAY);		// ���û�����ɫ
	setbkcolor(0xeeeeee);			// ���ñ�����ɫ ��һ��İ�
	setfillcolor(0xeeeeee);			// ���������ɫ ��һ��İ�
	settextstyle(30, 0, "΢���ź�");	//�������������ʽ

	fillrectangle(left, top, right, bottom);									//�������봰��

	setfillcolor(RGB(166, 173, 178));			//���ð�ť��ɫ һ����ɫ
	fillroundrect(bleft, btop, bleft + 150, btop + 80, 10, 10);				//���Ʒ��ذ�ť
	settextstyle(50, 0, "΢���ź�");	//�������������ʽ
	outtextxy(bleft + (150 - textwidth("����")) / 2, btop + 15, "����");

	int width = textwidth(text);	// �ַ����ܿ��
	int counter = 0;				// �����˸������
	bool binput = true;				// �Ƿ�������  ����������,��false��ɾ����

	HWND cheek = GetHWnd();		//���öһ����Ӵ���


	ExMessage msg;
	while (binput)
	{
		while (binput && peekmessage(&msg, EX_MOUSE | EX_CHAR, false))  //��ȡ��Ϣ,����֮��ɾ��
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x > bleft && msg.x < bleft + 150 && msg.y > btop && msg.y < btop + 80)
				{
					// �����
					clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);

					// �ָ�����ֵ
					setlinecolor(oldlinecolor);
					setbkcolor(oldbkcolor);
					setfillcolor(oldfillcolor);

					//������ر�
					binput = false;

					//��ջ������Ϣ
					msg.message = 0;

					MenuView();       //MK ����Ҫ����ת��ҳ��
					break;
				}
			}
			else if (msg.message == WM_CHAR)
			{  //�ڿ���,���밴����Ϣ
				size_t len = strlen(text);
				switch (msg.ch)
				{
				case '\b': //�˸��,ɾ��һ���ַ�
					if (len > 0)
					{
						text[len - 1] = 0;
						width = textwidth(text);
						counter = 0;
						clearrectangle(left + 10 + width, top + 1, right - 1, bottom - 1);
					}
					break;
				case '\r': //�س���,�������
					if (strcmp(text, "BasketballChicken") == 0)   //MK  �����Ƕһ���,������char����,���Բ�Ҫ������
					{
						char w[5];
						InputBox(w, 5, "��������ܶ����㷢����!\n��������ĳɵ��ٶ�");
						xx = atoi(w);	//���ٶ��޸ĳ������ֵ
					}
					else
					{
						MessageBox(cheek, "�һ�ʧ��\n����һ��롣", "�һ�ʧ��", MB_OK | MB_ICONSTOP);
					}
				default:  //������,������Ϣ
					if (len < 100) //С�������������
					{
						text[len++] = msg.ch;
						text[len] = 0;
						clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// ������Ĺ��
						width = textwidth(text);				// ���¼����ı�����
						counter = 0;
						outtextxy(left + 10, top + 5, text);		// ����µ��ַ���
					}
				}
			}
			peekmessage(NULL, EX_MOUSE | EX_CHAR);				// ����Ϣ���������ոմ������һ����Ϣ
		}
		// ���ƹ�꣨�����˸����Ϊ 20ms * 32��
		counter = (counter + 1) % 32;
		if (counter < 16)
			line(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);				// �����
		else
			clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);		// �����

		// ��ʱ 20ms
		Sleep(20);
		clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// �����
	}
}

void Set()
{
	initgraph(WIDTH, HEIGHT);
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "����");
	// ���ݻ���ֵ
	int oldlinecolor = getlinecolor();
	int oldbkcolor = getbkcolor();
	int oldfillcolor = getfillcolor();
	//���Ʊ���
	IMAGE bk;
	cleardevice();
	loadimage(&bk, "./pictures/Bk12.png", WIDTH, HEIGHT);
	putimage(0, 0, &bk);

	//���Ʊ���
	settextcolor(BLACK);																//���Ʊ���
	settextstyle(100, 0, "΢���ź�");												//��������
	setbkmode(TRANSPARENT);														 //����͸��
	outtextxy((1024 - textwidth("����")) / 2, 100, "����");
	settextstyle(50, 0, "΢���ź�");
	outtextxy((1024 - textwidth("���ֿ���")) / 2, 350, "���ֿ���");

	//���ذ�ť
	IMAGE open, close;
	loadimage(&open, "./pictures/musicOpen.png");
	loadimage(&close, "./pictures/musicClose.png");
	int x = (1024 - open.getwidth()) / 2, y = 220;							//����λ��

	//�������ֿ���ػ��ư�ť
	bool music = true;				//MK ���boolҪд��ȫ�� 

	//���Ʒ��ذ�ť
	int bleft = 830, btop = 520;									//���ذ�ť����
	setfillcolor(RGB(166, 173, 178));
	fillroundrect(bleft, btop, bleft + 150, btop + 80, 10, 10);
	settextstyle(50, 0, "΢���ź�");
	outtextxy(bleft + (150 - textwidth("����")) / 2, btop + 15, "����");


	ExMessage msg;
	msg.message = 0;
	while (true)
	{
		if (music)
		{// ͸����ͼopen

			// ������ʼ��
			DWORD* pwin = GetImageBuffer();			//���ڻ�����ָ��
			DWORD* psrc = GetImageBuffer(&open);		//ͼƬ������ָ��
			int win_w = getwidth();				//���ڿ��
			int win_h = getheight();
			int src_w = open.getwidth();				//ͼƬ���
			int src_h = open.getheight();

			// ������ͼ��ʵ�ʳ���
			int real_w = (x + src_w > win_w) ? win_w - x : src_w;			// �������ұ߽�
			int real_h = (y + src_h > win_h) ? win_h - y : src_h;			// �������±߽�
			if (x < 0) { psrc += -x;			real_w -= -x;	x = 0; }	// ��������߽�
			if (y < 0) { psrc += (src_w * -y);	real_h -= -y;	y = 0; }	// �������ϱ߽�


			// ������ͼ��ʼλ��
			pwin += (win_w * y + x);

			// ʵ��͸����ͼ
			for (int iy = 0; iy < real_h; iy++)
			{
				for (int ix = 0; ix < real_w; ix++)
				{
					byte a = (byte)(psrc[ix] >> 24);//����͸��ͨ����ֵ[0,256) 0Ϊ��ȫ͸�� 255Ϊ��ȫ��͸��
					if (a > 100)
					{
						pwin[ix] = psrc[ix];
					}
				}
				//������һ��
				pwin += win_w;
				psrc += src_w;
			}
		}
		else
		{
			// ������ʼ��
			DWORD* pwin = GetImageBuffer();			//���ڻ�����ָ��
			DWORD* psrc = GetImageBuffer(&close);		//ͼƬ������ָ��
			int win_w = getwidth();				//���ڿ��
			int win_h = getheight();
			int src_w = close.getwidth();				//ͼƬ���
			int src_h = close.getheight();

			// ������ͼ��ʵ�ʳ���
			int real_w = (x + src_w > win_w) ? win_w - x : src_w;			// �������ұ߽�
			int real_h = (y + src_h > win_h) ? win_h - y : src_h;			// �������±߽�
			if (x < 0) { psrc += -x;			real_w -= -x;	x = 0; }	// ��������߽�
			if (y < 0) { psrc += (src_w * -y);	real_h -= -y;	y = 0; }	// �������ϱ߽�


			// ������ͼ��ʼλ��
			pwin += (win_w * y + x);

			// ʵ��͸����ͼ
			for (int iy = 0; iy < real_h; iy++)
			{
				for (int ix = 0; ix < real_w; ix++)
				{
					byte a = (byte)(psrc[ix] >> 24);//����͸��ͨ����ֵ[0,256) 0Ϊ��ȫ͸�� 255Ϊ��ȫ��͸��
					if (a > 100)
					{
						pwin[ix] = psrc[ix];
					}
				}
				//������һ��
				pwin += win_w;
				psrc += src_w;
			}
		}

		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)                        //MK ���������ť��Ϣ������,��Ҫʱ���Ըĳ��Ҽ�����
			{
				if (msg.x > bleft && msg.x < bleft + 150 && msg.y > btop && msg.y < btop + 80)
				{
					// �ָ�����ֵ
					setlinecolor(oldlinecolor);
					setbkcolor(oldbkcolor);
					setfillcolor(oldfillcolor);

					//��ջ������Ϣ
					msg.message = 0;

					MenuView(); //MK ����ŷ���ҳ��
					break;
				}
				else if (msg.x > x && msg.x < x + open.getwidth() && msg.y > y && msg.y < y + open.getheight())
				{
					if (music)
					{
						mciSendString("stop ./ji2.mp3", NULL, 0, NULL);;  //MK ����ű�������·��  
						music = false;
					}
					else
					{
						mciSendString("open ./ji2.mp3", NULL, 0, NULL);
						mciSendString("play ./ji2.mp3", NULL, 0, NULL);      //MK ����ű�������·��
						music = true;
					}
				}
			}
		}
	}
}

void GameView()
{
	score = 0;
	//initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);
	//��������,˫����
	//BeginBatchDraw();//��ʼ���� 
	mciSendString("stop ./ji2.mp3", NULL, 0, NULL);
	const int countdownTime = 60;  // ����ʱʱ��
	time_t start = time(0);

	init();
	mciSendString("open ./jiji.mp3", NULL, 0, NULL);
	mciSendString("play ./jiji.mp3", NULL, 0, NULL);
	while (1)
	{

		draw();
		// ��Ϸ��ʼ��ʱ��
		time_t now = time(0);  // ��ǰʱ��
		int elapsed = (int)difftime(now, start);  // �ѹ�ȥ��ʱ��
		int remaining = countdownTime - elapsed;  // ʣ���ʱ��

		if (remaining <= 0)
		{
			// ����ʱ��������ʾʧ�ܽ���
			end();
			return;
		}

		char buffer[50];
		sprintf(buffer, "Time remaining: %d seconds", remaining);
		settextcolor(BLACK);
		Score();
		outtextxy(10, 10, buffer);
		playermove();
		gamerEatfood();
		gamerAndai();
		aiEatfood();
		aiMove();
		aiEatai();

		FlushBatchDraw();//ˢ��;


	}

}

void draw()
{

	//���û��Ƶ��豸��ͼƬ��������Ҳ��һ��ͼƬ
	SetWorkingImage(&map);
	setbkcolor(WHITE);//���ñ�����ɫ
	cleardevice();	//����		
	//������	
	setlinecolor(RGB(230, 231, 239));
	// ��ָ��λ���������
	for (int i = 0; i < map_WIDTH; i += 10)
	{
		line(i, 0, i, map_HEIGHT);//����
		line(0, i, map_WIDTH, i);//����
	}

	//����ʳ��

	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (!food[i].flag)	//���������ڵ�ʳ��
			continue;
		setfillcolor(food[i].color);
		solidcircle(food[i].x, food[i].y, food[i].r);
	}

	//����ai
	for (int i = 0; i < AINUM; i++)
	{
		if (ai[i].flag == 1)

		{
			setfillcolor(ai[i].color);
			solidcircle(ai[i].x, ai[i].y, ai[i].r);
		}
	}


	//�������
	setfillcolor(RED); //����������ɫ
	solidcircle(player.x, player.y, player.r); //��Բ
	SetWorkingImage();
	//��map�����������
	putimage(0, 0, WIDTH, HEIGHT, &map, g_camreaPos.x, g_camreaPos.y);
	{
		//�����Ϊ���ģ��������������
		g_camreaPos.x = player.x - WIDTH / 2;
		g_camreaPos.y = player.y - HEIGHT / 2;
		//��ֹ�����Խ��
		if (g_camreaPos.x < 0) g_camreaPos.x = 0;
		if (g_camreaPos.y < 0) g_camreaPos.y = 0;
		if (g_camreaPos.x > map_WIDTH - WIDTH) g_camreaPos.x = map_WIDTH - WIDTH;
		if (g_camreaPos.y > map_HEIGHT - HEIGHT) g_camreaPos.y = map_HEIGHT - HEIGHT;
	}


}

void playermove()
{
	initspeed();
	//getasynckeystate() ��ȡ�첽����״̬ ���������_getch()�����̣��ҿ���֧��ͬʱ����
	if (GetAsyncKeyState('W') & 0x8000)
	{
		player.y -= player.speed;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		player.y += player.speed;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		player.x -= player.speed;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		player.x += player.speed;
	}


}

void init()
{

	//���������
	srand((unsigned)time(NULL));

	//��ʼ�����
	player.x = rand() % map_WIDTH;
	player.y = rand() % map_HEIGHT;
	player.r = 10.0;
	player.flag = true;
	//��ʼ��ʳ��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		creatfood(i);
	}
	//��ʼ��ai
	for (int i = 0; i < AINUM; i++)
	{
		creatai(i);
	}
}

void Score()
{
	char buffer[50];
	sprintf(buffer, "����: %lf", score);
	settextcolor(BLACK);

	outtextxy(50, 50, buffer);  // ��ָ��λ���������
}

void jinHua()
{

}

void end()
{
	//initgraph(1024, 640);
	//���Ʊ���
	mciSendString("stop ./jiji.mp3", NULL, 0, NULL);
	mciSendString("open ./ji2.mp3", NULL, 0, NULL);
	mciSendString("play ./ji2.mp3", NULL, 0, NULL);
	IMAGE bk;
	cleardevice();
	loadimage(&bk, "./pictures/end.png", WIDTH, HEIGHT);
	putimage(0, 0, &bk);
	button(237, 535, 150, 50, "���¿�ʼ");
	button(637, 535, 150, 50, "���ز˵�");
	if (flaggrade == 1 && User[flaggrade1].grade1 < score)  User[flaggrade1].grade1 = score;
	else if (flaggrade == 2 && User[flaggrade1].grade2 < score)  User[flaggrade1].grade2 = score;
	else if (flaggrade == 3 && User[flaggrade1].grade3 < score)  User[flaggrade1].grade3 = score;
	User[flaggrade1].allgrade = User[flaggrade1].grade1 + User[flaggrade1].grade2 + User[flaggrade1].grade3;
	SaveFile();
	ExMessage msg;
	while (1) {
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 237 && msg.x <= 237 + 150 && msg.y >= 535 && msg.y <= 535 + 50)
			{
				Choose();

			}
			if (msg.x >= 637 && msg.x <= 637 + 150 && msg.y >= 535 && msg.y <= 535 + 50)
			{
				MenuView();

			}
		}
		FlushBatchDraw();
	}

}

void gamerEatfood()
{
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag && distance(&food[i], &player) < player.r)
		{
			if (player.r < 20)
			{
				food[i].flag = false;
				player.r += food[i].r / 5;
				score += food[i].r / 5;
			}
			else if (player.r < 40)
			{
				food[i].flag = false;
				player.r += food[i].r / 6;
				score += food[i].r / 5;
			}
			else if (player.r < 60)
			{
				food[i].flag = false;
				player.r += food[i].r / 8;
				score += food[i].r / 5;
			}
			else if (player.r < 80)
			{
				food[i].flag = false;
				player.r += food[i].r / 9;
				score += food[i].r / 5;
			}
			else if (player.r < 100)
			{
				food[i].flag = false;
				player.r += food[i].r / 10;
				score += food[i].r / 5;
			}
			else if (player.r < 120)
			{
				food[i].flag = false;
				player.r += food[i].r / 12;
				score += food[i].r / 5;
			}

			initspeed();
			//ʳ����������
			creatfood(i);

		}
	}
}

void gamerAndai()
{
	for (int i = 0; i < AINUM; i++)
	{
		if (ai[i].flag && player.flag && distance(&ai[i], &player) < player.r && ai[i].r < player.r)
		{

			ai[i].flag = false;
			player.r += ai[i].r / 5;
			score += ai[i].r / 2;
		}
		else if (ai[i].flag && player.flag && distance(&ai[i], &player) < ai[i].r && ai[i].r > player.r)
		{
			player.flag = false;
			end();
			break;
		}
	}
}

void aiMove()
{

	for (int i = 0; i < AINUM; i++)

	{

		double min_DISTANCE = map_WIDTH;//�����������

		int min = -1;//���������ҵ�Ŀ��С����±�

		if (ai[i].flag == 1)

		{

			//AI����AI

			for (int k = i + 1; k < AINUM; k++)

			{

				if (ai[i].r > ai[k].r && ai[k].flag == 1)

				{//����ܳԣ��Ҿ���ﵽҪ������¾��룬�������±�

					if (distance(&ai[i], &ai[k]) < min_DISTANCE)

					{

						min_DISTANCE = distance(&ai[i], &ai[k]);

						min = k;

					}

				}

			}

		}

		//����ҵ�Ŀ�꣬��ȥ׷��

		if ((min != -1))

		{

			Chase(&ai[i], &ai[min]);

		}

	}

}

void creatfood(int i)

{
	food[i].x = rand() % map_WIDTH;
	food[i].y = rand() % map_HEIGHT;
	food[i].r = rand() % 5 + 1.0;//1 2 3 4 5
	food[i].flag = true;
	food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);

}

void creatai(int i)
{
	ai[i].flag = 1;
	ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	ai[i].r = float(rand() % 10 + 10.0);
	ai[i].x = rand() % map_WIDTH;
	ai[i].y = rand() % map_HEIGHT;//ȷ�� AI ������������ʾ����Ϸ��ͼ�У������ᳬ���߽硣
}

void Chase(struct ball* chase, struct ball* run)
{
	if (run->x > chase->x)
	{
		chase->x += Speed;
	}
	else
	{
		chase->x -= Speed;
	}
	if (run->y > chase->y)
	{
		chase->y += Speed;
	}
	else
	{
		chase->y -= Speed;
	}

}

double distance(struct ball* b1, struct ball* b2)
{
	return  sqrt((b1->x - b2->x) * (b1->x - b2->x) + (b1->y - b2->y) * (b1->y - b2->y));
}

void aiEatfood()
{
	for (int i = 0; i < FOOD_NUM; i++)
	{
		for (int j = 0; j < AINUM; j++)
		{
			if (food[i].flag && distance(&food[i], &ai[j]) < ai[j].r)
			{
				if (ai[j].r < 20)
				{
					food[i].flag = false;
					ai[j].r += food[i].r / 4;
				}
				else if (ai[j].r < 40)
				{
					food[i].flag = false;
					ai[j].r += food[i].r / 5;
				}
				else if (ai[j].r < 60)
				{
					food[i].flag = false;
					player.r += food[i].r / 6;
				}
				else if (ai[j].r < 80)
				{
					food[i].flag = false;
					ai[j].r += food[i].r / 8;
				}
				else
				{
					food[i].flag = false;
					ai[j].r += food[i].r / 9;
				}
				//ʳ����������
				creatfood(i);
			}
		}
	}
}

void aiEatai()
{
	for (int i = 0; i < AINUM; i++)
	{
		if (ai[i].flag == 0)
			continue;
		for (int k = i + 1; k < AINUM; k++)
		{
			if (ai[k].flag == 1)
			{
				if (distance(&ai[i], &ai[k]) < ai[k].r - ai[i].r / 3)
				{
					ai[i].flag = 0;
					ai[k].r += ai[i].r / 8;
					creatai(i);
				}
				else if (distance(&ai[i], &ai[k]) < ai[i].r - ai[k].r / 3)
				{
					ai[k].flag = 0;
					ai[i].r += ai[k].r / 8;
					creatai(k);
				}
			}

		}
	}
}

int main()
{

	initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);
	//��������,˫����
	//BeginBatchDraw();
	//��ʼ���� 
	InitFile();
	Begin();
	Rank();
	getchar();
	closegraph();
	return 0;

}

void InitFile()
{
	FILE* fp = fopen("./�û���Ϣ/userinfo.txt", "r");   //���û��ļ���ֻ��
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %d %d %d %d\n",
				&User[N].name, &User[N].id, &User[N].password, &User[N].grade1, &User[N].grade2, &User[N].grade3, &User[N].allgrade);
			N++;
		}
		if (fclose(fp))
		{
			printf("�ر��ļ�ʧ��!");
		}
		fp = NULL;
	}
}

void SaveFile()
{
	remove("./�û���Ϣ/userinfo.txt");  //ɾ��ԭ�ļ�
	FILE* fp = fopen("./�û���Ϣ/userinfo.txt", "w");  //�������ļ�
	for (int i = 0; i < N; i++)  //���������ݴ������ļ�
	{
		fprintf(fp, "%-8s %-4s %-4s %-4d %-4d %-4d %-4d\n",
			User[i].name, User[i].id, User[i].password, User[i].grade1, User[i].grade2, User[i].grade3, User[i].allgrade);
	}
	if (fclose(fp))
	{
		printf("�ر��ļ�ʧ�ܣ�");
	}
}

void Begin()
{
	BeginBatchDraw();
	mciSendString("open ./ji2.mp3", NULL, 0, NULL);
	mciSendString("play ./ji2.mp3", NULL, 0, NULL);
	//ͼƬ����
	IMAGE img1;
	loadimage(&img1, "./image/R-C.jpg", 1024, 640);
	putimage(0, 0, &img1);
	//����
	char text1[] = "��¼";
	char text2[] = "ע��";
	char text3[] = "�˳�";
	settextcolor(RGB(179, 89, 0));  //����������ɫ
	settextstyle(50, 0, "����"); //���������ʽ
	setbkmode(TRANSPARENT);  //�������ֱ���
	int tx = (1024 - textwidth(text1)) / 2 - 80;  //��������λ��
	int ty = (640 - textheight(text1)) / 2;
	outtextxy(tx, ty - 80, text1);
	outtextxy(tx, ty, text2);
	outtextxy(tx, ty + 80, text3);
	//EndBatchDraw();
	//������
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= tx && msg.x <= tx + textwidth(text1) && msg.y >= ty - 80 && msg.y <= ty - 80 + textheight(text1))
			{
				printf("��¼\0");
				Login();
				break;
			}
			if (msg.x >= tx && msg.x <= tx + textwidth(text1) && msg.y >= ty && msg.y <= ty + textheight(text1))
			{
				printf("ע��\0");
				Register();
				break;
			}
			if (msg.x >= tx && msg.x <= tx + textwidth(text1) && msg.y >= ty + 80 && msg.y <= ty + 80 + textheight(text1))
			{
				SaveFile();
				exit(0);
			}
		}FlushBatchDraw();
	}
}

void Login()
{
	LoginDraw();
	//������
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 420 && msg.x <= 620 && msg.y >= 215 && msg.y <= 215 + textheight("�˺�"))
			{
				InputBox(user.id, 10, "�������˺ţ����Ϊ10���ַ�");
				LoginDraw();
			}
			if (msg.x >= 420 && msg.x <= 620 && msg.y >= 275 && msg.y <= 275 + textheight("����"))
			{
				InputBox(user.password, 10, "���������룬���Ϊ10���ַ�");
				LoginDraw();

			}
			if (msg.x >= 460 && msg.x <= 460 + textwidth("ȷ��") && msg.y >= 335 && msg.y <= 335 + textheight("ȷ��"))
			{
				int x = LoginJudge();
				switch (x)
				{
				case 1:MessageBox(GetHWnd(), "�˺Ų�����", "���棡����", MB_OK);
					break;
				case 2:MessageBox(GetHWnd(), "�������", "���棡����", MB_OK);
					break;
				case 3:printf("��¼�ɹ�"); MessageBox(GetHWnd(), "��ӭ�����������ս������", "��ϲ������", MB_OK);
					MenuView();
					break;
				default:
					break;
				}
			}
			if (msg.x >= 460 && msg.x <= 460 + textwidth("����") && msg.y >= 395 && msg.y <= 395 + textheight("����"))
			{
				Begin();
			}
		}
		FlushBatchDraw();
	}
}

int LoginJudge()
{
	int flag1 = 0, flag2 = 0;
	for (int i = 0; i < N; i++)
	{
		if (strcmp(User[i].id, user.id) == 0) flag1 = 1;
		if (flag1 == 1 && strcmp(User[i].password, user.password) == 0)
		{
			flaggrade1 = i;
			return 3;
		}
	}
	if (flag1 == 0) return 1;
	return 2;
}

void LoginDraw()
{
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "��¼");
	BeginBatchDraw();
	//ͼƬ����
	IMAGE img1;
	loadimage(&img1, "./image/R-A.jpg", 1024, 640);
	putimage(0, 0, &img1);
	//����
	char text1[] = "�˺�";
	char text2[] = "����";
	char text3[] = "ȷ��";
	char text4[] = "����";
	char text5[10];
	char text6[10];
	strcpy(text5, user.id);
	strcpy(text6, user.password);
	settextcolor(BLACK);  //����������ɫ
	settextstyle(40, 0, "����"); //���������ʽ
	setbkmode(TRANSPARENT);  //�������ֱ���
	outtextxy(420 - textwidth(text1), 215, text1);
	outtextxy(420 - textwidth(text2), 275, text2);
	outtextxy(460, 335, text3);
	outtextxy(460, 395, text4);
	fillrectangle(420, 215, 620, 215 + textheight(text1)); //�˺������
	fillrectangle(420, 275, 620, 275 + textheight(text2)); //���������
	outtextxy(430, 215, text5);
	outtextxy(430, 275, text6);
	EndBatchDraw();
}

void Register()
{
	RegisterDraw();
	//������
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 120 && msg.x <= 320 && msg.y >= 80 && msg.y <= 80 + textheight("�û���"))
				{
					InputBox(user.name, 10, "�������û���");
					RegisterDraw();
					break;
				}
				if (msg.x >= 120 && msg.x <= 320 && msg.y >= 140 && msg.y <= 140 + textheight("�˺�"))
				{
					InputBox(user.id, 10, "�������˺�");
					RegisterDraw();
					break;
				}
				if (msg.x >= 120 && msg.x <= 320 && msg.y >= 200 && msg.y <= 200 + textheight("����"))
				{
					InputBox(user.password, 10, "����������");
					RegisterDraw();
					break;
				}
				if (msg.x >= 160 && msg.x <= 160 + textwidth("ȷ��") && msg.y >= 260 && msg.y <= 260 + textheight("ȷ��"))
				{
					int x = RegisterJudge();
					switch (x)
					{
					case 0:MessageBox(GetHWnd(), "�û�����ʽ���淶", "���棡����", MB_OK);
						break;
					case 1:MessageBox(GetHWnd(), "�˺Ÿ�ʽ���淶���ظ�", "���棡����", MB_OK);
						break;
					case 2:MessageBox(GetHWnd(), "�����ʽ���淶", "���棡����", MB_OK);
						break;
					case 3:Append(); MessageBox(GetHWnd(), "ע��ɹ�", "��ϲ������", MB_OK); Begin();
						break;
					default:
						break;
					}
				}
				if (msg.x >= 160 && msg.x <= 160 + textwidth("����") && msg.y >= 320 && msg.y <= 320 + textheight("����"))
				{
					Begin();
				}
			default:
				break;
			}

		}
	}
}

int RegisterJudge()
{
	if (strlen(user.name) == 0) return 0;
	for (int i = 0; i < N; i++)
	{
		if (strcmp(User[i].id, user.id) == 0 || strlen(user.id) != 5) return 1;
	}
	if (strlen(user.id) != 5) return 2;
	return 3;
}

void RegisterDraw()
{
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "ע��");
	BeginBatchDraw();
	//ͼƬ����
	IMAGE img1;
	loadimage(&img1, "./image/R-B.jpg", 1024, 640);
	putimage(0, 0, &img1);
	//����
	char text1[] = "�û���";
	char text2[] = "�˺�";
	char text3[] = "����";
	char text4[] = "ȷ��";
	char text5[] = "����";
	char text6[10];
	char text7[10];
	char text8[10];
	strcpy(text6, user.name);
	strcpy(text7, user.id);
	strcpy(text8, user.password);
	settextcolor(BLACK);  //����������ɫ
	settextstyle(40, 0, "����"); //���������ʽ
	setbkmode(TRANSPARENT);  //�������ֱ���
	outtextxy(120 - textwidth(text1), 80, text1);
	outtextxy(120 - textwidth(text2), 140, text2);
	outtextxy(120 - textwidth(text3), 200, text3);
	outtextxy(160, 260, text4);
	outtextxy(160, 320, text5);
	fillrectangle(120, 80, 320, 80 + textheight(text1)); //�ǳ������
	fillrectangle(120, 140, 320, 140 + textheight(text2)); //�˺������
	fillrectangle(120, 200, 320, 200 + textheight(text3)); //���������
	outtextxy(130, 80, text6);
	outtextxy(130, 140, text7);
	outtextxy(130, 200, text8);
	EndBatchDraw();
}

void Append()
{
	strcpy(User[N].name, user.name);
	strcpy(User[N].id, user.id);
	strcpy(User[N].password, user.password);
	N++;
}

void Rank()
{
	char cm[10];
	sort();
	RankDraw();
	int i = 1, k = 150;
	while (i < N)
	{
		printf("%s\n", User[i - 1].name);
		outtextxy(10, k, "�� ��");
		sprintf(cm, "%d", i);
		outtextxy(40, k, cm);
		outtextxy(150, k, User[i - 1].name);
		sprintf(cm, "%d", User[i - 1].grade1);
		outtextxy(300, k, cm);
		sprintf(cm, "%d", User[i - 1].grade2);
		outtextxy(500, k, cm);
		sprintf(cm, "%d", User[i - 1].grade3);
		outtextxy(700, k, cm);
		sprintf(cm, "%d", User[i - 1].allgrade);
		outtextxy(900, k, cm);
		k += 40;
		if (i % 8 == 0)
		{
			i++;
			break;
		}
		i++;
	}
	EndBatchDraw();
	//������
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 100 && msg.x <= 100 + textwidth("��һҳ") && msg.y >= 500 && msg.y <= 500 + textheight("��һҳ"))
			{
				if (i > 16)
				{
					printf("%d\n", i);
					if ((i - 1) % 8 != 0)
					{
						i = i - 8 - (i - 1) % 8;
					}
					else i -= 16;
					printf("%d\n", i);
					RankDraw();
					k = 150;
					while (i <= N)
					{
						printf("%s\n", User[i - 1].name);
						outtextxy(10, k, "�� ��");
						sprintf(cm, "%d", i);
						outtextxy(40, k, cm);
						outtextxy(150, k, User[i - 1].name);
						sprintf(cm, "%d", User[i - 1].grade1);
						outtextxy(300, k, cm);
						sprintf(cm, "%d", User[i - 1].grade2);
						outtextxy(500, k, cm);
						sprintf(cm, "%d", User[i - 1].grade3);
						outtextxy(700, k, cm);
						sprintf(cm, "%d", User[i - 1].allgrade);
						outtextxy(900, k, cm);
						k += 40;
						if (i % 8 == 0)
						{
							i++;
							break;
						}
						i++;
					}
					EndBatchDraw();
				}
				else
				{
					MessageBox(GetHWnd(), "���ǵ�һҳ", "ע�⣡����", MB_OK);
				}

			}
			if (msg.x >= 800 && msg.x <= 800 + textwidth("��һҳ") && msg.y >= 500 && msg.y <= 500 + textheight("��һҳ"))
			{
				if (i < N)
				{
					RankDraw();
					k = 150;
					while (i <= N)
					{
						printf("%s\n", User[i - 1].name);
						outtextxy(10, k, "�� ��");
						sprintf(cm, "%d", i);
						outtextxy(40, k, cm);
						outtextxy(150, k, User[i - 1].name);
						sprintf(cm, "%d", User[i - 1].grade1);
						outtextxy(300, k, cm);
						sprintf(cm, "%d", User[i - 1].grade2);
						outtextxy(500, k, cm);
						sprintf(cm, "%d", User[i - 1].grade3);
						outtextxy(700, k, cm);
						sprintf(cm, "%d", User[i - 1].allgrade);
						outtextxy(900, k, cm);
						k += 40;
						if (i % 8 == 0)
						{
							i++;
							break;
						}
						i++;
					}
					EndBatchDraw();
				}
				else
				{
					MessageBox(GetHWnd(), "�������һҳ", "ע�⣡����", MB_OK);
				}
			}
			if (msg.x >= 450 && msg.x <= 450 + textwidth("����") && msg.y >= 500 && msg.y <= 500 + textheight("����"))
			{
				MenuView();
			}
		}
	}
}

void RankDraw()
{
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "���а�");
	BeginBatchDraw();
	//ͼƬ����
	IMAGE img1;
	loadimage(&img1, "./image/R-D.jpg", 1024, 640);
	putimage(0, 0, &img1);
	//����
	settextcolor(RED);  //����������ɫ
	settextstyle(40, 0, "����"); //���������ʽ
	setbkmode(TRANSPARENT);  //�������ֱ���
	outtextxy(450, 50, TEXT("���а�"));
	settextcolor(BLACK);  //����������ɫ
	settextstyle(40, 0, "����"); //���������ʽ
	setbkmode(TRANSPARENT);  //�������ֱ���
	outtextxy(150, 100, TEXT("�û���"));
	outtextxy(300, 100, TEXT("��"));
	outtextxy(500, 100, TEXT("��ͨ"));
	outtextxy(700, 100, TEXT("����"));
	outtextxy(900, 100, TEXT("�ܷ�"));
	outtextxy(450, 500, TEXT("����"));
	outtextxy(800, 500, TEXT("��һҳ"));
	outtextxy(100, 500, TEXT("��һҳ"));
}

void sort()
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1 - i; j++)
		{
			if (User[j].allgrade <= User[j + 1].allgrade)
			{
				user = User[j];
				User[j] = User[j + 1];
				User[j + 1] = user;
			}
		}
	}
}

void initspeed()
{
	if (player.r >= 120)
	{
		player.speed = 1 + xx;
	}
	else if (player.r > 100)
	{
		player.speed = 4 + xx - player.r / 50; //1-2
	}
	else if (player.r > 80)
	{
		player.speed = 7 + xx - player.r / 20;  //2-3
	}
	else if (player.r > 50)
	{
		player.speed = 7 + xx - player.r / 20;  //3-4.5
	}
	else if (player.r > 40)
	{
		player.speed = 10 + xx - player.r / 10;  //5-6
	}
	else if (player.r > 30)
	{
		player.speed = 10 + xx - player.r / 10;  //6-7
	}
	else if (player.r > 20)
	{
		player.speed = 10 + xx - player.r / 10;  //7-8
	}
	else if (player.r >= 10)
	{
		player.speed = 10 + xx - player.r / 10;    //8~9
	}
}