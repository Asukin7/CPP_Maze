#pragma once
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <queue>
#include <stack>

using namespace std;

#define KUANG 51//迷宫宽
#define GAO 31//迷宫高

struct xy
{
	int x;
	int y;
};
struct xys
{
	int x;
	int y;
	int s;
};

int ij[GAO][KUANG];//迷宫数据
int t_ij[GAO][KUANG];
int bs;//所走步数

xy maze_qdxy;//当前位置坐标
xy maze_zdxy;//终点坐标
queue<xy> maze_tijxy;
queue<xys> dl;
stack<xys> dz;
stack<xys> cz;

void start();//初始化数据并生成迷宫
void win();//到达终点提示游戏结束

void maze_csh();//数据初始化
void maze_sjqd();//随机生成起点
void maze_sjzd();//随机终点起点

void maze_scdt();//随机生成地图
void maze_ijbj(xy t_xy);//标记一点为11后，将其四周符合要求的点入队
int maze_ijsj();//队列为空则返回0，不为空则随机在队列中取一坐标后返回1
void maze_ijpd();//判断一点是否可通路，可以标记为11，不可以标记为10

void maze_dyjm();//打印游戏界面
void maze_dyl();//打印路
void maze_dyq();//打印墙
void maze_dyqd();//打印起点
void maze_dyzd();//打印终点
void maze_dybs();//打印步数

void maze_cz();//操作圆点
void maze_fx(char userHit);//判断该方向是否可以移动，可以则移动

void gotoxy(int x, int y);//移动光标

void maze_zd();//自动模式
int maze_zd_bl();//遍历所有路径得出最短路径，成功返回1，失败返回0
void maze_zd_fx();//将一点四周可走的点入队
void maze_zd_cz();//使用最短路径操作圆点