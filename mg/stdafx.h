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

#define KUANG 51//�Թ���
#define GAO 31//�Թ���

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

int ij[GAO][KUANG];//�Թ�����
int t_ij[GAO][KUANG];
int bs;//���߲���

xy maze_qdxy;//��ǰλ������
xy maze_zdxy;//�յ�����
queue<xy> maze_tijxy;
queue<xys> dl;
stack<xys> dz;
stack<xys> cz;

void start();//��ʼ�����ݲ������Թ�
void win();//�����յ���ʾ��Ϸ����

void maze_csh();//���ݳ�ʼ��
void maze_sjqd();//����������
void maze_sjzd();//����յ����

void maze_scdt();//������ɵ�ͼ
void maze_ijbj(xy t_xy);//���һ��Ϊ11�󣬽������ܷ���Ҫ��ĵ����
int maze_ijsj();//����Ϊ���򷵻�0����Ϊ��������ڶ�����ȡһ����󷵻�1
void maze_ijpd();//�ж�һ���Ƿ��ͨ·�����Ա��Ϊ11�������Ա��Ϊ10

void maze_dyjm();//��ӡ��Ϸ����
void maze_dyl();//��ӡ·
void maze_dyq();//��ӡǽ
void maze_dyqd();//��ӡ���
void maze_dyzd();//��ӡ�յ�
void maze_dybs();//��ӡ����

void maze_cz();//����Բ��
void maze_fx(char userHit);//�жϸ÷����Ƿ�����ƶ����������ƶ�

void gotoxy(int x, int y);//�ƶ����

void maze_zd();//�Զ�ģʽ
int maze_zd_bl();//��������·���ó����·�����ɹ�����1��ʧ�ܷ���0
void maze_zd_fx();//��һ�����ܿ��ߵĵ����
void maze_zd_cz();//ʹ�����·������Բ��