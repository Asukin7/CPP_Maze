#include "stdafx.h"

int main()
{
	system("title Maze v2.2.190105z");//设置窗口标题
	system("mode con cols=122 lines=32");//设置窗口大小

	/*获取并隐藏控制台光标*/
	HANDLE p = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(p, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(p, &CursorInfo);

	srand((unsigned)time(NULL));//随机数初始化

	start();
	while (1)
	{
		maze_cz();
		maze_dyqd();
		maze_dybs();
		if (maze_qdxy.x == maze_zdxy.x && maze_qdxy.y == maze_zdxy.y)
			break;
	}
	win();

	return 0;
}

void start()//初始化数据并生成迷宫
{
	maze_csh();
	maze_dyjm();
	maze_scdt();
}

void win()//到达终点提示游戏结束
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_RED);
	gotoxy(103, 18);
	printf("                  ");
	gotoxy(103, 19);
	printf("                  ");
	gotoxy(103, 20);
	printf("  恭喜您到达终点！");
	gotoxy(103, 21);
	printf("                  ");
	gotoxy(103, 22);
	printf("    步数：  %-6d", bs);
	gotoxy(103, 23);
	printf("                  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED);
	gotoxy(103, 24);
	printf("   按任意键退出   ");
	getch();
}

void maze_csh()//数据初始化
{
	int i, j;
	for (i = 0; i < GAO; i++)
	{
		for (j = 0; j < KUANG; j++)
		{
			if ((i != 0 && i != (GAO - 1) && j != 0 && j != (KUANG - 1)) && (i % 2 == 1 && j % 2 == 1))
				ij[i][j] = 1;
			else
				ij[i][j] = 0;
		}
	}
	bs = 0;
	maze_sjqd();
	maze_sjzd();
}

void maze_sjqd()//随机生成起点
{
	do
	{
		maze_qdxy.x = rand() % 6 + 1;
		maze_qdxy.y = rand() % 29 + 1;
	} while (ij[maze_qdxy.y][maze_qdxy.x] == 0);
}

void maze_sjzd()//随机终点起点
{
	do
	{
		maze_zdxy.x = rand() % 10 + 39;
		maze_zdxy.y = rand() % 29 + 1;
	} while (ij[maze_zdxy.y][maze_zdxy.x] == 0);
}

void maze_scdt()//随机生成地图
{
	int i, j;
	xy t_xy;
	t_xy.x = 1;
	t_xy.y = 1;
	maze_ijbj(t_xy);
	while (1)
	{
		if (maze_ijsj() == 0) break;
		maze_ijpd();
		Sleep(1);
	}
	for (i = 0; i < GAO; i++)
	{
		for (j = 0; j < KUANG; j++)
		{
			if (ij[i][j] == 11)
				ij[i][j] = 1;
			else if (ij[i][j] == 10)
				ij[i][j] = 0;
		}
	}
}

void maze_ijbj(xy t_xy)//标记一点为11后，将其四周符合要求的点入队
{
	ij[t_xy.y][t_xy.x] = 11;
	if (ij[t_xy.y - 1][t_xy.x] == 0 && t_xy.y - 1 != 0)
		if (ij[t_xy.y - 2][t_xy.x] == 1)
		{
			t_xy.y--;
			maze_tijxy.push(t_xy);
			t_xy.y++;
		}
	if (ij[t_xy.y + 1][t_xy.x] == 0 && t_xy.y + 1 != GAO - 1)
		if (ij[t_xy.y + 2][t_xy.x] == 1)
		{
			t_xy.y++;
			maze_tijxy.push(t_xy);
			t_xy.y--;
		}
	if (ij[t_xy.y][t_xy.x - 1] == 0 && t_xy.x - 1 != 0)
		if (ij[t_xy.y][t_xy.x - 2] == 1)
		{
			t_xy.x--;
			maze_tijxy.push(t_xy);
			t_xy.x++;
		}
	if (ij[t_xy.y][t_xy.x + 1] == 0 && t_xy.x + 1 != KUANG - 1)
		if (ij[t_xy.y][t_xy.x + 2] == 1)
		{
			t_xy.x++;
			maze_tijxy.push(t_xy);
			t_xy.x--;
		}
}

int maze_ijsj()//队列为空则返回0，不为空则随机在队列中取一坐标后返回1
{
	if (maze_tijxy.size() == 0) return 0;
	int i;
	int n = rand() % maze_tijxy.size();
	for (i = 0; i < n; i++)
	{
		maze_tijxy.push(maze_tijxy.front());
		maze_tijxy.pop();
	}
	return 1;
}

void maze_ijpd()//判断一点是否可通路，可以标记为11，不可以标记为10
{
	xy t_xy;
	t_xy = maze_tijxy.front();
	maze_tijxy.pop();

	gotoxy(t_xy.x * 2 + 1, t_xy.y + 1);
	maze_dyl();

	if (ij[t_xy.y - 1][t_xy.x] == 1 && ij[t_xy.y + 1][t_xy.x] == 11)
	{
		ij[t_xy.y][t_xy.x] = 11;
		t_xy.y--;
		maze_ijbj(t_xy);
		return;
	}
	if (ij[t_xy.y + 1][t_xy.x] == 1 && ij[t_xy.y - 1][t_xy.x] == 11)
	{
		ij[t_xy.y][t_xy.x] = 11;
		t_xy.y++;
		maze_ijbj(t_xy);
		return;
	}
	if (ij[t_xy.y][t_xy.x - 1] == 1 && ij[t_xy.y][t_xy.x + 1] == 11)
	{
		ij[t_xy.y][t_xy.x] = 11;
		t_xy.x--;
		maze_ijbj(t_xy);
		return;
	}
	if (ij[t_xy.y][t_xy.x + 1] == 1 && ij[t_xy.y][t_xy.x - 1] == 11)
	{
		ij[t_xy.y][t_xy.x] = 11;
		t_xy.x++;
		maze_ijbj(t_xy);
		return;
	}
	ij[t_xy.y][t_xy.x] = 10;

	gotoxy(t_xy.x * 2 + 1, t_xy.y + 1);
	maze_dyq();
}

void maze_dyjm()//打印游戏界面
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	system("cls");
	int i, j;
	for (j = 0; j < KUANG; j++)
	{
		for (i = 0; i < GAO; i++)
		{
			gotoxy(j * 2 + 1, i + 1);
			switch (ij[i][j])
			{
			case 0:maze_dyq(); break;
			case 1:maze_dyl(); break;
			}
			if (j == KUANG - 1)
			{
				gotoxy(103, i + 1);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				switch (i)
				{
				case 2:
				{
					printf(" \"    \"  当前位置 ");
					gotoxy(106, i + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("●");
					break;
				}
				case 4:
				{
					printf(" \"    \"   终  点  ");
					gotoxy(106, i + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
					printf("★");
					break;
				}
				case 8:printf("   \" ↑ \"  上移   "); break;
				case 10:printf("   \" ↓ \"  下移   "); break;
				case 12:printf("   \" ← \"  左移   "); break;
				case 14:printf("   \" → \"  右移   "); break;
				case 20:printf("    步数：        "); break;
				case 26:printf(" \"空格\"  切换模式 "); break;
				case 28:printf(" 当前：  手动模式 "); break;
				case 0:case 6:case 16:case 24:case 30:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				default:printf("                  "); break;
				}
				gotoxy(121, i + 1);
				maze_dyq();
				Sleep(10);
			}
		}
		Sleep(10);
	}
	maze_dybs();
	Sleep(100);
	maze_dyzd();
	Sleep(100);
	maze_dyqd();
}

void maze_dyl()//打印路
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("  ");
}

void maze_dyq()//打印墙
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	printf("  ");
}

void maze_dyqd()//打印起点
{
	gotoxy(maze_qdxy.x * 2 + 1, maze_qdxy.y + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("●");
}

void maze_dyzd()//打印终点
{
	gotoxy(maze_zdxy.x * 2 + 1, maze_zdxy.y + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	printf("★");
}

void maze_dybs()//打印步数
{
	gotoxy(115, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("%-6d", bs);
}

void maze_cz()//操作圆点
{
	char userHit;
	while (1)
	{
		Sleep(10);
		if (kbhit())
		{
			userHit = getch();
			switch (userHit)
			{
			case 72:case 80:case 75:case 77:maze_fx(userHit); break;
			case 32:maze_zd(); break;
			}
			break;
		}
	}
}

void maze_fx(char userHit)//判断该方向是否可以移动，可以则移动
{
	switch (userHit)
	{
	case 72:
		if (ij[maze_qdxy.y - 1][maze_qdxy.x] == 1)
		{
			gotoxy(maze_qdxy.x * 2 + 1, maze_qdxy.y + 1);
			printf("  ");
			maze_qdxy.y--;
			bs++;
		}
		break;
	case 80:
		if (ij[maze_qdxy.y + 1][maze_qdxy.x] == 1)
		{
			gotoxy(maze_qdxy.x * 2 + 1, maze_qdxy.y + 1);
			printf("  ");
			maze_qdxy.y++;
			bs++;
		}
		break;
	case 75:
		if (ij[maze_qdxy.y][maze_qdxy.x - 1] == 1)
		{
			gotoxy(maze_qdxy.x * 2 + 1, maze_qdxy.y + 1);
			printf("  ");
			maze_qdxy.x--;
			bs++;
		}
		break;
	case 77:
		if (ij[maze_qdxy.y][maze_qdxy.x + 1] == 1)
		{
			gotoxy(maze_qdxy.x * 2 + 1, maze_qdxy.y + 1);
			printf("  ");
			maze_qdxy.x++;
			bs++;
		}
		break;
	}
}

void gotoxy(int x, int y)//移动光标
{
	COORD p;
	p.X = x - 1;
	p.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void maze_zd()//自动模式
{
	gotoxy(112, 29);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("自动");
	memcpy(t_ij, ij, sizeof(ij));
	while (!dl.empty()) dl.pop();
	while (!dz.empty()) dz.pop();
	while (!cz.empty()) cz.pop();
	xys zd_xys;
	zd_xys.x = maze_qdxy.x;
	zd_xys.y = maze_qdxy.y;
	zd_xys.s = 0;
	t_ij[zd_xys.x][zd_xys.y] = -1;
	dl.push(zd_xys);
	if (maze_zd_bl() == 0)
	{
		gotoxy(112, 29);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("手动");
		return;
	}
	maze_zd_cz();
	gotoxy(112, 29);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("手动");
}

int maze_zd_bl()//遍历所有路径得出最短路径，成功返回1，失败返回0
{
	xys zd_xys;
	while (1)
	{
		if (dl.empty()) return 0;
		maze_zd_fx();
		dz.push(dl.front());
		zd_xys = dl.front();
		if (zd_xys.x == maze_zdxy.x && zd_xys.y == maze_zdxy.y) break;
		dl.pop();
	}

	xys t_xys;
	zd_xys = dz.top();
	dz.pop();
	cz.push(zd_xys);
	while (!dz.empty())
	{
		t_xys = dz.top();
		dz.pop();
		if (zd_xys.s == t_xys.s + 1)
		{
			if ((zd_xys.x == t_xys.x - 1 && zd_xys.y == t_xys.y)
				|| (zd_xys.x == t_xys.x + 1 && zd_xys.y == t_xys.y)
				|| (zd_xys.x == t_xys.x && zd_xys.y == t_xys.y - 1)
				|| (zd_xys.x == t_xys.x && zd_xys.y == t_xys.y + 1))
			{
				cz.push(t_xys);
				zd_xys = t_xys;
			}
		}
	}
	return 1;
}

void maze_zd_fx()//将一点四周可走的点入队
{
	xys zd_xys;
	xys t_xys;
	t_xys = dl.front();
	zd_xys = t_xys;
	if (t_ij[zd_xys.y - 1][zd_xys.x] == 1)
	{
		zd_xys.y--;
		zd_xys.s++;
		t_ij[zd_xys.y][zd_xys.x] = -1;
		dl.push(zd_xys);
	}
	zd_xys = t_xys;
	if (t_ij[zd_xys.y + 1][zd_xys.x] == 1)
	{
		zd_xys.y++;
		zd_xys.s++;
		t_ij[zd_xys.y][zd_xys.x] = -1;
		dl.push(zd_xys);
	}
	zd_xys = t_xys;
	if (t_ij[zd_xys.y][zd_xys.x - 1] == 1)
	{
		zd_xys.x--;
		zd_xys.s++;
		t_ij[zd_xys.y][zd_xys.x] = -1;
		dl.push(zd_xys);
	}
	zd_xys = t_xys;
	if (t_ij[zd_xys.y][zd_xys.x + 1] == 1)
	{
		zd_xys.x++;
		zd_xys.s++;
		t_ij[zd_xys.y][zd_xys.x] = -1;
		dl.push(zd_xys);
	}
}

void maze_zd_cz()//使用最短路径操作圆点
{
	xys zd_xys;
	int i;
	char userHit;
	cz.pop();
	while (!cz.empty())
	{
		gotoxy(maze_qdxy.x * 2 + 1, maze_qdxy.y + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("·");

		zd_xys = cz.top();
		cz.pop();
		maze_qdxy.x = zd_xys.x;
		maze_qdxy.y = zd_xys.y;
		bs++;

		maze_dyqd();
		maze_dybs();

		if (zd_xys.x == maze_zdxy.x && zd_xys.y == maze_zdxy.y) break;

		for (i = 0; i < 10; i++)
		{
			Sleep(10);
			if (kbhit())
			{
				userHit = getch();
				if (userHit == 32) return;
			}
		}
	}
}