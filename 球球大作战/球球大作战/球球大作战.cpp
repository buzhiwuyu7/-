#include <iostream>
#include<stdio.h>
#include<easyx.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <graphics.h>
#include <string.h>
#include<mmsystem.h>    //多媒体文件
#pragma comment(lib,"winmm.lib")    //媒体链接库文件
#include <process.h>  //计时多线程
/*---------------------------数据设计---------------------------------------------*/
#define WIDTH 1024
#define HEIGHT 640
#define map_WIDTH (WIDTH)*8
#define map_HEIGHT (HEIGHT)*8
#define FOOD_NUM 4000
#define AINUM 200
#define DISTANCE(x1, y1, x2, y2)	(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)))
struct ball//球的结构
{
	int x;
	int y;
	double  r;
	bool flag;	//是否存活
	DWORD color; //颜色
	double speed; //速度

};
struct ball player;
struct ball food[FOOD_NUM];
struct ball ai[AINUM];
struct UserData
{
	char name[10];     //用户名
	char id[10];        //账号
	char password[10];  //密码
	int grade1;    //简单最高分
	int grade2;    //普通最高分
	int grade3;    //地狱最高分
	int allgrade;   //总积分
}User[1000], user;
int N = 0;
int Speed = 0;
int xx = 0;
float score = 0;
int flaggrade = 0;
int flaggrade1 = 0;
IMAGE map(map_WIDTH, map_HEIGHT); //地图 图片
POINT g_camreaPos;   //摄像机坐标
/*---------------------------数据设计---------------------------------------------*/



/*-----------------------------view-----------------------------------------------*/
/*
负责人：雨
功能：结束
参数值：void
返回值：void
*/
void end();
/*
负责人：南笙几梦
功能：登录界面
1.打印登录界面选项
2.接收用户输入
3.如果是ws修改光标位置
  如果是回车: 进入对应选项
  登录：调用登录函数 需要登录函数，登录后能进入菜单
  注册：调用注册函数 需要注册函数
  退出：则用exit(0);
  参数值：void
返回值：void
*/
void Begin();
/*
负责人：雨
功能：定义按钮
参数值：void
返回值：void
*/
void button(int x, int y, int w, int h, const char* text);
/*
负责人：雨
功能：用户界面（菜单）
1.打印用户界面选项
2.接收用户输入
3.如果是ws修改光标位置
  如果是回车: 进入对应选项
  进入游戏：调用选择难度界面 需要选择难度函数
  皮肤：调用皮肤界面 需要皮肤函数
  排行榜：调用排行榜界面 需要排行榜函数
  开挂：调用开挂界面 需要开挂函数
  返回登录：调用登录函数
  设置：调用设置界面 需要设置函数
  参数值：void
返回值：void
*/
void MenuView();
/*
负责人：空心太阳
功能：计算两球圆心距
 参数值：void
返回值：void
*/
double distance(struct ball* b1, struct ball* b2);
/*
负责人：董琦
功能：追逐算法
 参数值：void
返回值：void
*/
void Chase(struct ball* chase, struct ball* run);
/*
负责人：南笙几梦
功能：登录中界面
1.打印登录中界面
2.接收用户输入
参数值：void
返回值：void
*/
void Login();
/*
负责人：南笙几梦
功能：登录中判断
检查该用户输入密码是否正确且查找存储文档中是否有该用户
参数值：void
返回值：返回1：账号错误  返回2：密码错误  返回3：正确
*/
int LoginJudge();
/*
负责人：南笙几梦
功能：登录中背景绘制
参数值：void
返回值：void
*/
void LoginDraw();  //登陆中背景绘制
/*
负责人：南笙几梦
功能：注册中
1.打印注册中界面
2.接收用户输入
参数值：void
返回值：void
*/
void Register();    //注册中界面
/*
负责人：南笙几梦
功能：注册中判断
检查该用户输入的信息格式是否规范且查找存储文档中是否已有该用户
参数值：void
返回值：返回0：用户名格式错误, 返回1：账号格式错误  返回2：密码格式错误  返回3：正确
*/
int RegisterJudge();
/*
负责人：南笙几梦
功能：注册中背景绘制
参数值：void
返回值：void
*/
void RegisterDraw();
/*
负责人：董琦
功能：选择难度
1.打印选择难度界面
2.拥有三个难度“简单”“困难”“地狱”
3.选择难度后修改ai小球的大小和速度
4.连接游戏界面
参数值：void
返回值：void
*/
void Choose();
/*
负责人：无
功能：敬请期待
参数值：void
返回值：void
*/
void Skin();
/*
负责人：南笙几梦
功能：展示排行榜
1.打印排行榜界面
2.创建一个按钮返回菜单
参数值：void
返回值：void
*/
void Rank();
/*
负责人：Neal
功能：开挂调整初始参数
1.打印开挂界面
2.接收用户输入的兑换码并核对若通过则可进行对球球初始大小及速度进行修改
3.返回修改的初始速度及大小
4.创建一个按钮返回菜单
参数值：void
返回值：void
*/
void Cheat();
/*
负责人：Neal
功能：设置
1.打印设置界面
2.按w s移动光标回车确定音乐开或关
3.创建一个按钮返回菜单
参数值：void
返回值：void
*/
void Set();
/*
负责人：雨
功能：界面整合
对游戏初始化
whlie(1){
开启双缓冲绘图
调用绘制函数
调用操作函数
调用玩家吃食物函数
调用ai与玩家互吃函数
调用ai移动函数

}
游戏胜利选择是否录入排行榜
若是调用录入函数将成绩录入排行榜
参数值：void
返回值：void
*/
void GameView();
/*
负责人：董琦
功能：绘制（补充Ai和食物）
绘制玩家
绘制食物
绘制ai
绘制游戏界面（时间，分数的位置）
参数值：void
返回值：void
*/
void draw();
/*-----------------------------view-----------------------------------------------*/



/*-----------------------------service-------------------------------------------*/
/*
负责人：雨
功能：按wsad对球进行移动
按空格使小球的体积缩小速度变快
参数值：void
返回值：void
*/
void playermove();
/*
负责人：董琦
功能：初始化速度
设置随机数种子
初始化玩家
初始化食物
初始化ai
参数值：void
返回值：void
*/
void initspeed();
/*
负责人：董琦
功能：初始化
设置随机数种子
初始化玩家
初始化食物
初始化ai
参数值：void
返回值：void
*/
void init();
/*
负责人：董琦
功能：创造食物
参数值：void
返回值：void
*/
void creatfood(int i);
/*
负责人：董琦
功能：创造ai
参数值：void
返回值：void
*/
void creatai(int i);
/*
负责人：//
功能：分数
当玩家吃掉ai或食物时增加分数
参数值：void
返回值：void
*/
void Score();
/*
负责人：淡然置之
功能：玩家吃食物并增大半径，降低移速
参数值：void
返回值：void
*/
void gamerEatfood();
/*
负责人：晚风
功能：ai吃ai
参数值：void
返回值：void
*/
void gamerAndai();
/*
负责人：董琦
功能；ai吃ai
参数值：void
返回值：void
*/
void aiEatai();
/*
负责人：董琦
功能；ai吃食物
参数值：void
返回值：void
*/
void aiEatfood();
/*
负责人：董琦
功能；ai的移动
参数值：void
返回值：void
*/
void aiMove();
/*-----------------------------service-------------------------------------------*/


/*-----------------------------dao-----------------------------------------------*/
/*
负责人：南笙几梦
功能：存入文件
参数值：void
返回值：void
*/
void SaveFile();
/*
负责人：南笙几梦
功能： 初始化文件
参数值：void
返回值：void
*/
void InitFile();
/*
负责人：南笙几梦
功能：注册成功后增加用户
参数值：void
返回值：void
*/
void Append();
/*
负责人：南笙几梦
功能：展示排行榜
参数值：void
返回值：void
*/
void Rank();
/*
负责人：南笙几梦
功能：排行榜背景绘制
参数值：void
返回值：void
*/
void RankDraw();
/*
负责人：南笙几梦
功能：对所有用户根据总分排序
参数值：void
返回值：void
*/
void sort();
/*-------------------------------dao------------------------------------------------*/



void button(int x, int y, int w, int h, const char* text) {
	setbkmode(TRANSPARENT);
	setfillcolor(BLUE);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextstyle(30, 0, "宋体");
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
	//设置窗口标题
	SetWindowText(hnd, "菜单");
	IMAGE img;
	loadimage(&img, "./pictures/Bk11.png", 1024, 640);
	cleardevice();
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, "宋体");
	button(437, 155, 150, 50, "进入游戏");
	button(437, 225, 150, 50, "皮肤");
	button(437, 295, 150, 50, "排行榜");
	button(437, 365, 150, 50, "开挂");
	button(437, 435, 150, 50, "返回登录");
	button(437, 505, 150, 50, "设置");

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
	//设置窗口标题
	SetWindowText(hnd, "选择难度");
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
				//printf("简单\0");
				Speed = 3;
				GameView();
				break;
			}
			if (msg.x >= 400 && msg.x <= 640 && msg.y >= 270 && msg.y <= 340)
			{
				flaggrade = 2;
				//printf("普通\0");
				Speed = 6;
				GameView();
				break;
			}
			if (msg.x >= 400 && msg.x <= 640 && msg.y >= 420 && msg.y <= 490)
			{
				flaggrade = 3;
				//printf("地狱\0");
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
	MessageBox(GetHWnd(), "敬请期待", "注意！！！", MB_OK);
}

void Cheat()
{
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);  //绘制初始窗口
	// 备份环境值
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "开挂");
	int oldlinecolor = getlinecolor();
	int oldbkcolor = getbkcolor();
	int oldfillcolor = getfillcolor();

	//绘制背景
	IMAGE bk;
	cleardevice();
	loadimage(&bk, "./pictures/Bk11.png", WIDTH, HEIGHT);
	putimage(0, 0, &bk);

	//定义初始坐标
	int left = 312, top = 250, right = 712, bottom = 300;	//输入框坐标
	int bleft = 830, btop = 520;									//返回按钮坐标
	char text[100];											//初始化字符串
	memset(text, 0, 100);
	//绘制标题
	settextcolor(BLACK);
	settextstyle(100, 0, "微软雅黑");
	setbkmode(TRANSPARENT);
	outtextxy((1024 - textwidth("兑换码")) / 2, 100, "兑换码");

	setlinecolor(LIGHTGRAY);		// 设置画线颜色
	setbkcolor(0xeeeeee);			// 设置背景颜色 暗一点的白
	setfillcolor(0xeeeeee);			// 设置填充颜色 暗一点的白
	settextstyle(30, 0, "微软雅黑");	//设置输入字体格式

	fillrectangle(left, top, right, bottom);									//绘制输入窗口

	setfillcolor(RGB(166, 173, 178));			//设置按钮颜色 一个灰色
	fillroundrect(bleft, btop, bleft + 150, btop + 80, 10, 10);				//绘制返回按钮
	settextstyle(50, 0, "微软雅黑");	//设置输入字体格式
	outtextxy(bleft + (150 - textwidth("返回")) / 2, btop + 15, "返回");

	int width = textwidth(text);	// 字符串总宽度
	int counter = 0;				// 光标闪烁计数器
	bool binput = true;				// 是否输入中  检测出现问题,把false都删除了

	HWND cheek = GetHWnd();		//设置兑换的子窗口


	ExMessage msg;
	while (binput)
	{
		while (binput && peekmessage(&msg, EX_MOUSE | EX_CHAR, false))  //获取消息,并且之后不删除
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x > bleft && msg.x < bleft + 150 && msg.y > btop && msg.y < btop + 80)
				{
					// 擦光标
					clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);

					// 恢复环境值
					setlinecolor(oldlinecolor);
					setbkcolor(oldbkcolor);
					setfillcolor(oldfillcolor);

					//把输入关闭
					binput = false;

					//清空缓存的消息
					msg.message = 0;

					MenuView();       //MK 这里要放跳转的页面
					break;
				}
			}
			else if (msg.message == WM_CHAR)
			{  //在框内,读入按键信息
				size_t len = strlen(text);
				switch (msg.ch)
				{
				case '\b': //退格键,删掉一个字符
					if (len > 0)
					{
						text[len - 1] = 0;
						width = textwidth(text);
						counter = 0;
						clearrectangle(left + 10 + width, top + 1, right - 1, bottom - 1);
					}
					break;
				case '\r': //回车键,检查内容
					if (strcmp(text, "BasketballChicken") == 0)   //MK  这里是兑换码,由于是char类型,所以不要用中文
					{
						char w[5];
						InputBox(w, 5, "鸡哥的秘密都被你发现啦!\n输入你想改成的速度");
						xx = atoi(w);	//把速度修改成输入的值
					}
					else
					{
						MessageBox(cheek, "兑换失败\n请检查兑换码。", "兑换失败", MB_OK | MB_ICONSTOP);
					}
				default:  //其他键,读入信息
					if (len < 100) //小于最大数量长度
					{
						text[len++] = msg.ch;
						text[len] = 0;
						clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// 清除画的光标
						width = textwidth(text);				// 重新计算文本框宽度
						counter = 0;
						outtextxy(left + 10, top + 5, text);		// 输出新的字符串
					}
				}
			}
			peekmessage(NULL, EX_MOUSE | EX_CHAR);				// 从消息队列抛弃刚刚处理过的一个消息
		}
		// 绘制光标（光标闪烁周期为 20ms * 32）
		counter = (counter + 1) % 32;
		if (counter < 16)
			line(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);				// 画光标
		else
			clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);		// 擦光标

		// 延时 20ms
		Sleep(20);
		clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// 擦光标
	}
}

void Set()
{
	initgraph(WIDTH, HEIGHT);
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "设置");
	// 备份环境值
	int oldlinecolor = getlinecolor();
	int oldbkcolor = getbkcolor();
	int oldfillcolor = getfillcolor();
	//绘制背景
	IMAGE bk;
	cleardevice();
	loadimage(&bk, "./pictures/Bk12.png", WIDTH, HEIGHT);
	putimage(0, 0, &bk);

	//绘制标题
	settextcolor(BLACK);																//绘制标题
	settextstyle(100, 0, "微软雅黑");												//设置字体
	setbkmode(TRANSPARENT);														 //设置透明
	outtextxy((1024 - textwidth("设置")) / 2, 100, "设置");
	settextstyle(50, 0, "微软雅黑");
	outtextxy((1024 - textwidth("音乐开关")) / 2, 350, "音乐开关");

	//加载按钮
	IMAGE open, close;
	loadimage(&open, "./pictures/musicOpen.png");
	loadimage(&close, "./pictures/musicClose.png");
	int x = (1024 - open.getwidth()) / 2, y = 220;							//开关位置

	//根据音乐开与关绘制按钮
	bool music = true;				//MK 这个bool要写在全局 

	//绘制返回按钮
	int bleft = 830, btop = 520;									//返回按钮坐标
	setfillcolor(RGB(166, 173, 178));
	fillroundrect(bleft, btop, bleft + 150, btop + 80, 10, 10);
	settextstyle(50, 0, "微软雅黑");
	outtextxy(bleft + (150 - textwidth("返回")) / 2, btop + 15, "返回");


	ExMessage msg;
	msg.message = 0;
	while (true)
	{
		if (music)
		{// 透明绘图open

			// 变量初始化
			DWORD* pwin = GetImageBuffer();			//窗口缓冲区指针
			DWORD* psrc = GetImageBuffer(&open);		//图片缓冲区指针
			int win_w = getwidth();				//窗口宽高
			int win_h = getheight();
			int src_w = open.getwidth();				//图片宽高
			int src_h = open.getheight();

			// 计算贴图的实际长宽
			int real_w = (x + src_w > win_w) ? win_w - x : src_w;			// 处理超出右边界
			int real_h = (y + src_h > win_h) ? win_h - y : src_h;			// 处理超出下边界
			if (x < 0) { psrc += -x;			real_w -= -x;	x = 0; }	// 处理超出左边界
			if (y < 0) { psrc += (src_w * -y);	real_h -= -y;	y = 0; }	// 处理超出上边界


			// 修正贴图起始位置
			pwin += (win_w * y + x);

			// 实现透明贴图
			for (int iy = 0; iy < real_h; iy++)
			{
				for (int ix = 0; ix < real_w; ix++)
				{
					byte a = (byte)(psrc[ix] >> 24);//计算透明通道的值[0,256) 0为完全透明 255为完全不透明
					if (a > 100)
					{
						pwin[ix] = psrc[ix];
					}
				}
				//换到下一行
				pwin += win_w;
				psrc += src_w;
			}
		}
		else
		{
			// 变量初始化
			DWORD* pwin = GetImageBuffer();			//窗口缓冲区指针
			DWORD* psrc = GetImageBuffer(&close);		//图片缓冲区指针
			int win_w = getwidth();				//窗口宽高
			int win_h = getheight();
			int src_w = close.getwidth();				//图片宽高
			int src_h = close.getheight();

			// 计算贴图的实际长宽
			int real_w = (x + src_w > win_w) ? win_w - x : src_w;			// 处理超出右边界
			int real_h = (y + src_h > win_h) ? win_h - y : src_h;			// 处理超出下边界
			if (x < 0) { psrc += -x;			real_w -= -x;	x = 0; }	// 处理超出左边界
			if (y < 0) { psrc += (src_w * -y);	real_h -= -y;	y = 0; }	// 处理超出上边界


			// 修正贴图起始位置
			pwin += (win_w * y + x);

			// 实现透明贴图
			for (int iy = 0; iy < real_h; iy++)
			{
				for (int ix = 0; ix < real_w; ix++)
				{
					byte a = (byte)(psrc[ix] >> 24);//计算透明通道的值[0,256) 0为完全透明 255为完全不透明
					if (a > 100)
					{
						pwin[ix] = psrc[ix];
					}
				}
				//换到下一行
				pwin += win_w;
				psrc += src_w;
			}
		}

		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)                        //MK 这里如果按钮消息紧挨着,必要时可以改成右键操作
			{
				if (msg.x > bleft && msg.x < bleft + 150 && msg.y > btop && msg.y < btop + 80)
				{
					// 恢复环境值
					setlinecolor(oldlinecolor);
					setbkcolor(oldbkcolor);
					setfillcolor(oldfillcolor);

					//清空缓存的消息
					msg.message = 0;

					MenuView(); //MK 这里放返回页面
					break;
				}
				else if (msg.x > x && msg.x < x + open.getwidth() && msg.y > y && msg.y < y + open.getheight())
				{
					if (music)
					{
						mciSendString("stop ./ji2.mp3", NULL, 0, NULL);;  //MK 这里放背景音乐路径  
						music = false;
					}
					else
					{
						mciSendString("open ./ji2.mp3", NULL, 0, NULL);
						mciSendString("play ./ji2.mp3", NULL, 0, NULL);      //MK 这里放背景音乐路径
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
	//闪屏现象,双缓冲
	//BeginBatchDraw();//开始缓冲 
	mciSendString("stop ./ji2.mp3", NULL, 0, NULL);
	const int countdownTime = 60;  // 倒计时时间
	time_t start = time(0);

	init();
	mciSendString("open ./jiji.mp3", NULL, 0, NULL);
	mciSendString("play ./jiji.mp3", NULL, 0, NULL);
	while (1)
	{

		draw();
		// 游戏开始的时间
		time_t now = time(0);  // 当前时间
		int elapsed = (int)difftime(now, start);  // 已过去的时间
		int remaining = countdownTime - elapsed;  // 剩余的时间

		if (remaining <= 0)
		{
			// 倒计时结束，显示失败界面
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

		FlushBatchDraw();//刷新;


	}

}

void draw()
{

	//设置绘制的设备（图片），窗口也是一张图片
	SetWorkingImage(&map);
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();	//清屏		
	//画格子	
	setlinecolor(RGB(230, 231, 239));
	// 在指定位置输出文字
	for (int i = 0; i < map_WIDTH; i += 10)
	{
		line(i, 0, i, map_HEIGHT);//竖线
		line(0, i, map_WIDTH, i);//横线
	}

	//绘制食物

	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (!food[i].flag)	//跳过不存在的食物
			continue;
		setfillcolor(food[i].color);
		solidcircle(food[i].x, food[i].y, food[i].r);
	}

	//绘制ai
	for (int i = 0; i < AINUM; i++)
	{
		if (ai[i].flag == 1)

		{
			setfillcolor(ai[i].color);
			solidcircle(ai[i].x, ai[i].y, ai[i].r);
		}
	}


	//绘制玩家
	setfillcolor(RED); //设置球球颜色
	solidcircle(player.x, player.y, player.r); //画圆
	SetWorkingImage();
	//把map输出到窗口上
	putimage(0, 0, WIDTH, HEIGHT, &map, g_camreaPos.x, g_camreaPos.y);
	{
		//以玩家为中心，计算摄像机坐标
		g_camreaPos.x = player.x - WIDTH / 2;
		g_camreaPos.y = player.y - HEIGHT / 2;
		//防止摄像机越界
		if (g_camreaPos.x < 0) g_camreaPos.x = 0;
		if (g_camreaPos.y < 0) g_camreaPos.y = 0;
		if (g_camreaPos.x > map_WIDTH - WIDTH) g_camreaPos.x = map_WIDTH - WIDTH;
		if (g_camreaPos.y > map_HEIGHT - HEIGHT) g_camreaPos.y = map_HEIGHT - HEIGHT;
	}


}

void playermove()
{
	initspeed();
	//getasynckeystate() 获取异步按键状态 这个函数比_getch()更流程，且可以支持同时按键
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

	//随机数种子
	srand((unsigned)time(NULL));

	//初始化玩家
	player.x = rand() % map_WIDTH;
	player.y = rand() % map_HEIGHT;
	player.r = 10.0;
	player.flag = true;
	//初始化食物
	for (int i = 0; i < FOOD_NUM; i++)
	{
		creatfood(i);
	}
	//初始化ai
	for (int i = 0; i < AINUM; i++)
	{
		creatai(i);
	}
}

void Score()
{
	char buffer[50];
	sprintf(buffer, "分数: %lf", score);
	settextcolor(BLACK);

	outtextxy(50, 50, buffer);  // 在指定位置输出文字
}

void jinHua()
{

}

void end()
{
	//initgraph(1024, 640);
	//绘制背景
	mciSendString("stop ./jiji.mp3", NULL, 0, NULL);
	mciSendString("open ./ji2.mp3", NULL, 0, NULL);
	mciSendString("play ./ji2.mp3", NULL, 0, NULL);
	IMAGE bk;
	cleardevice();
	loadimage(&bk, "./pictures/end.png", WIDTH, HEIGHT);
	putimage(0, 0, &bk);
	button(237, 535, 150, 50, "重新开始");
	button(637, 535, 150, 50, "返回菜单");
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
			//食物重新生成
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

		double min_DISTANCE = map_WIDTH;//最大搜索距离

		int min = -1;//用来保存找到目标小球的下标

		if (ai[i].flag == 1)

		{

			//AI靠近AI

			for (int k = i + 1; k < AINUM; k++)

			{

				if (ai[i].r > ai[k].r && ai[k].flag == 1)

				{//如果能吃，且距离达到要求则更新距离，并保存下标

					if (distance(&ai[i], &ai[k]) < min_DISTANCE)

					{

						min_DISTANCE = distance(&ai[i], &ai[k]);

						min = k;

					}

				}

			}

		}

		//如果找到目标，则去追逐

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
	ai[i].y = rand() % map_HEIGHT;//确保 AI 对象完整地显示在游戏地图中，而不会超出边界。
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
				//食物重新生成
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
	//闪屏现象,双缓冲
	//BeginBatchDraw();
	//开始缓冲 
	InitFile();
	Begin();
	Rank();
	getchar();
	closegraph();
	return 0;

}

void InitFile()
{
	FILE* fp = fopen("./用户信息/userinfo.txt", "r");   //打开用户文件，只读
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
			printf("关闭文件失败!");
		}
		fp = NULL;
	}
}

void SaveFile()
{
	remove("./用户信息/userinfo.txt");  //删除原文件
	FILE* fp = fopen("./用户信息/userinfo.txt", "w");  //创建新文件
	for (int i = 0; i < N; i++)  //将所有数据存入新文件
	{
		fprintf(fp, "%-8s %-4s %-4s %-4d %-4d %-4d %-4d\n",
			User[i].name, User[i].id, User[i].password, User[i].grade1, User[i].grade2, User[i].grade3, User[i].allgrade);
	}
	if (fclose(fp))
	{
		printf("关闭文件失败！");
	}
}

void Begin()
{
	BeginBatchDraw();
	mciSendString("open ./ji2.mp3", NULL, 0, NULL);
	mciSendString("play ./ji2.mp3", NULL, 0, NULL);
	//图片绘制
	IMAGE img1;
	loadimage(&img1, "./image/R-C.jpg", 1024, 640);
	putimage(0, 0, &img1);
	//文字
	char text1[] = "登录";
	char text2[] = "注册";
	char text3[] = "退出";
	settextcolor(RGB(179, 89, 0));  //设置字体颜色
	settextstyle(50, 0, "楷体"); //设置字体格式
	setbkmode(TRANSPARENT);  //设置文字背景
	int tx = (1024 - textwidth(text1)) / 2 - 80;  //处理文字位置
	int ty = (640 - textheight(text1)) / 2;
	outtextxy(tx, ty - 80, text1);
	outtextxy(tx, ty, text2);
	outtextxy(tx, ty + 80, text3);
	//EndBatchDraw();
	//鼠标操作
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= tx && msg.x <= tx + textwidth(text1) && msg.y >= ty - 80 && msg.y <= ty - 80 + textheight(text1))
			{
				printf("登录\0");
				Login();
				break;
			}
			if (msg.x >= tx && msg.x <= tx + textwidth(text1) && msg.y >= ty && msg.y <= ty + textheight(text1))
			{
				printf("注册\0");
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
	//鼠标操作
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 420 && msg.x <= 620 && msg.y >= 215 && msg.y <= 215 + textheight("账号"))
			{
				InputBox(user.id, 10, "请输入账号，最多为10个字符");
				LoginDraw();
			}
			if (msg.x >= 420 && msg.x <= 620 && msg.y >= 275 && msg.y <= 275 + textheight("密码"))
			{
				InputBox(user.password, 10, "请输入密码，最多为10个字符");
				LoginDraw();

			}
			if (msg.x >= 460 && msg.x <= 460 + textwidth("确定") && msg.y >= 335 && msg.y <= 335 + textheight("确定"))
			{
				int x = LoginJudge();
				switch (x)
				{
				case 1:MessageBox(GetHWnd(), "账号不存在", "警告！！！", MB_OK);
					break;
				case 2:MessageBox(GetHWnd(), "密码错误", "警告！！！", MB_OK);
					break;
				case 3:printf("登录成功"); MessageBox(GetHWnd(), "欢迎来到球球大作战！！！", "恭喜！！！", MB_OK);
					MenuView();
					break;
				default:
					break;
				}
			}
			if (msg.x >= 460 && msg.x <= 460 + textwidth("返回") && msg.y >= 395 && msg.y <= 395 + textheight("返回"))
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
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "登录");
	BeginBatchDraw();
	//图片绘制
	IMAGE img1;
	loadimage(&img1, "./image/R-A.jpg", 1024, 640);
	putimage(0, 0, &img1);
	//文字
	char text1[] = "账号";
	char text2[] = "密码";
	char text3[] = "确定";
	char text4[] = "返回";
	char text5[10];
	char text6[10];
	strcpy(text5, user.id);
	strcpy(text6, user.password);
	settextcolor(BLACK);  //设置字体颜色
	settextstyle(40, 0, "楷体"); //设置字体格式
	setbkmode(TRANSPARENT);  //设置文字背景
	outtextxy(420 - textwidth(text1), 215, text1);
	outtextxy(420 - textwidth(text2), 275, text2);
	outtextxy(460, 335, text3);
	outtextxy(460, 395, text4);
	fillrectangle(420, 215, 620, 215 + textheight(text1)); //账号输入框
	fillrectangle(420, 275, 620, 275 + textheight(text2)); //密码输入框
	outtextxy(430, 215, text5);
	outtextxy(430, 275, text6);
	EndBatchDraw();
}

void Register()
{
	RegisterDraw();
	//鼠标操作
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 120 && msg.x <= 320 && msg.y >= 80 && msg.y <= 80 + textheight("用户名"))
				{
					InputBox(user.name, 10, "请输入用户名");
					RegisterDraw();
					break;
				}
				if (msg.x >= 120 && msg.x <= 320 && msg.y >= 140 && msg.y <= 140 + textheight("账号"))
				{
					InputBox(user.id, 10, "请输入账号");
					RegisterDraw();
					break;
				}
				if (msg.x >= 120 && msg.x <= 320 && msg.y >= 200 && msg.y <= 200 + textheight("密码"))
				{
					InputBox(user.password, 10, "请输入密码");
					RegisterDraw();
					break;
				}
				if (msg.x >= 160 && msg.x <= 160 + textwidth("确定") && msg.y >= 260 && msg.y <= 260 + textheight("确定"))
				{
					int x = RegisterJudge();
					switch (x)
					{
					case 0:MessageBox(GetHWnd(), "用户名格式不规范", "警告！！！", MB_OK);
						break;
					case 1:MessageBox(GetHWnd(), "账号格式不规范或重复", "警告！！！", MB_OK);
						break;
					case 2:MessageBox(GetHWnd(), "密码格式不规范", "警告！！！", MB_OK);
						break;
					case 3:Append(); MessageBox(GetHWnd(), "注册成功", "恭喜！！！", MB_OK); Begin();
						break;
					default:
						break;
					}
				}
				if (msg.x >= 160 && msg.x <= 160 + textwidth("返回") && msg.y >= 320 && msg.y <= 320 + textheight("返回"))
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
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "注册");
	BeginBatchDraw();
	//图片绘制
	IMAGE img1;
	loadimage(&img1, "./image/R-B.jpg", 1024, 640);
	putimage(0, 0, &img1);
	//文字
	char text1[] = "用户名";
	char text2[] = "账号";
	char text3[] = "密码";
	char text4[] = "确定";
	char text5[] = "返回";
	char text6[10];
	char text7[10];
	char text8[10];
	strcpy(text6, user.name);
	strcpy(text7, user.id);
	strcpy(text8, user.password);
	settextcolor(BLACK);  //设置字体颜色
	settextstyle(40, 0, "楷体"); //设置字体格式
	setbkmode(TRANSPARENT);  //设置文字背景
	outtextxy(120 - textwidth(text1), 80, text1);
	outtextxy(120 - textwidth(text2), 140, text2);
	outtextxy(120 - textwidth(text3), 200, text3);
	outtextxy(160, 260, text4);
	outtextxy(160, 320, text5);
	fillrectangle(120, 80, 320, 80 + textheight(text1)); //昵称输入框
	fillrectangle(120, 140, 320, 140 + textheight(text2)); //账号输入框
	fillrectangle(120, 200, 320, 200 + textheight(text3)); //密码输入框
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
		outtextxy(10, k, "第 名");
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
	//鼠标操作
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 100 && msg.x <= 100 + textwidth("上一页") && msg.y >= 500 && msg.y <= 500 + textheight("上一页"))
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
						outtextxy(10, k, "第 名");
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
					MessageBox(GetHWnd(), "已是第一页", "注意！！！", MB_OK);
				}

			}
			if (msg.x >= 800 && msg.x <= 800 + textwidth("下一页") && msg.y >= 500 && msg.y <= 500 + textheight("下一页"))
			{
				if (i < N)
				{
					RankDraw();
					k = 150;
					while (i <= N)
					{
						printf("%s\n", User[i - 1].name);
						outtextxy(10, k, "第 名");
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
					MessageBox(GetHWnd(), "已是最后一页", "注意！！！", MB_OK);
				}
			}
			if (msg.x >= 450 && msg.x <= 450 + textwidth("返回") && msg.y >= 500 && msg.y <= 500 + textheight("返回"))
			{
				MenuView();
			}
		}
	}
}

void RankDraw()
{
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "排行榜");
	BeginBatchDraw();
	//图片绘制
	IMAGE img1;
	loadimage(&img1, "./image/R-D.jpg", 1024, 640);
	putimage(0, 0, &img1);
	//文字
	settextcolor(RED);  //设置字体颜色
	settextstyle(40, 0, "楷体"); //设置字体格式
	setbkmode(TRANSPARENT);  //设置文字背景
	outtextxy(450, 50, TEXT("排行榜"));
	settextcolor(BLACK);  //设置字体颜色
	settextstyle(40, 0, "楷体"); //设置字体格式
	setbkmode(TRANSPARENT);  //设置文字背景
	outtextxy(150, 100, TEXT("用户名"));
	outtextxy(300, 100, TEXT("简单"));
	outtextxy(500, 100, TEXT("普通"));
	outtextxy(700, 100, TEXT("地狱"));
	outtextxy(900, 100, TEXT("总分"));
	outtextxy(450, 500, TEXT("返回"));
	outtextxy(800, 500, TEXT("下一页"));
	outtextxy(100, 500, TEXT("上一页"));
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