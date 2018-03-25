#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include <string.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

//显示首页
void FirstPage();

//播放音乐
void MyPlaySound();

//检测空格
void TestSpace();

//停止播放
void MyStopPlay();

//画背景
void ShowBackground();

//为蛇产生随机位置
void SetSnakeRandPosition();

//画蛇
void DrawSnake();

void SnakeMove();

void DestroySnake();

//改变方向
void ChangeDirection();
//判断是否死亡
bool IsSnakeDie();
//Food
void ProduceFood();
//
void SnakeGrow();
//
void ChangeSnakeSpeed();
//
void Score();

int main(void)
{
	//显示首页
	FirstPage();
	//play music
	MyPlaySound();
	//检测空格
	TestSpace();
	//停止播放
	//MyStopPlay();
	//清屏
	system("cls");
	//进入游戏
	//printf("Begin playing\n");
	SetSnakeRandPosition();
	
	ShowBackground();
	while (1)
	{
		system("cls");
		ChangeDirection();
		ProduceFood();
		SnakeGrow();
		if (false == IsSnakeDie())
		{
			printf("Snake is dead!\n");
			break;
		}
		SnakeMove();
		ShowBackground();
		Score();

		ChangeSnakeSpeed();
		Sleep(g_sleep_time);
	}

	system("pause");
	return 0;
}

void Score()
{
	COORD rd;
	rd.X = 63;
	rd.Y = 5;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("分数");
	rd.Y = 6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf(" %d", g_snake_length - 2);
	rd.Y = 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("U I O P调节速度");
	rd.Y = 9;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf(" U=750");
	rd.Y = 10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf(" I=500");
	rd.Y = 11;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf(" O=250");
	rd.Y = 12;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf(" P=150 ");
}

void ChangeSnakeSpeed()
{
	if (GetAsyncKeyState('U'))
	{
		g_sleep_time = 750;
	}
	else if (GetAsyncKeyState('I'))
	{
		g_sleep_time = 500;
	}
	else if (GetAsyncKeyState('O'))
	{
		g_sleep_time = 250;
	}
	else if (GetAsyncKeyState('P'))
	{
		g_sleep_time = 150;
	}
}

//蛇长大
void SnakeGrow()
{
	//蛇头坐标和食物坐标重合
	if ((g_x_food == SnakeBody[0][0]) && ((2 * g_y_food) == SnakeBody[0][1]))
	{
		if (up == SnakeBody[g_snake_length][2])
		{
			SnakeBody[g_snake_length + 1][0] = SnakeBody[g_snake_length][0] + 1;
			SnakeBody[g_snake_length + 1][1] = SnakeBody[g_snake_length][0];
			SnakeBody[g_snake_length + 1][2] = up;
		}
		else if (down == SnakeBody[g_snake_length][2])
		{
			SnakeBody[g_snake_length + 1][0] = SnakeBody[g_snake_length][0] - 1;
			SnakeBody[g_snake_length + 1][1] = SnakeBody[g_snake_length][0];
			SnakeBody[g_snake_length + 1][2] = down;
		}
		else if (right == SnakeBody[g_snake_length][2])
		{
			SnakeBody[g_snake_length + 1][0] = SnakeBody[g_snake_length][0];
			SnakeBody[g_snake_length + 1][1] = SnakeBody[g_snake_length][0] - 2;
			SnakeBody[g_snake_length + 1][2] = up;
		}
		else if (left == SnakeBody[g_snake_length][2])
		{
			SnakeBody[g_snake_length + 1][0] = SnakeBody[g_snake_length][0];
			SnakeBody[g_snake_length + 1][1] = SnakeBody[g_snake_length][0] + 2;
			SnakeBody[g_snake_length + 1][2] = up;
		}
		g_snake_length++;
		Food = true;
	}
}

//Food
void ProduceFood()
{
	//rand food position
	if (false == Food)
	{
		return;
	}

	while (1)
	{
		bool flag = true;
		g_x_food = rand() % 19 + 2;
		g_y_food = rand() % 25 + 2;

		for (int i = 0; SnakeBody[i][0] != 0; ++i)
		{
			if ((g_x_food == SnakeBody[i][0]) && (g_y_food == SnakeBody[i][1]))
			{
				flag = false;
				break;
			}
		}
		if (true == flag)
		{
			break;
		}
	}
	//draw food
	strncpy(&background[g_x_food][2 * g_y_food], "★", 2);
	Food = false;
}

//是否死亡
bool IsSnakeDie()
{
	if (left == SnakeBody[0][2] || right == SnakeBody[0][2])
	{
		if (0 == strncmp(&background[SnakeBody[0][0]][SnakeBody[0][1] + SnakeBody[0][2]], "■", 2))
		{
			return false;
		}
	}
	else
	{
		if (0 == strncmp(&background[SnakeBody[0][0] + SnakeBody[0][2]][SnakeBody[0][1]], "■", 2))
		{
			return false;
		}
	}

	return true;
}

//改变方向
void ChangeDirection()
{
	if (GetAsyncKeyState('W'))//返回值short，高字节不为零，说明一直按W，低字节不为零，说明不是一直按
	{
		if (down != SnakeBody[0][2])
		{
			SnakeDirection = up;
		}
	}
	else if (GetAsyncKeyState('S'))
	{
		if (up != SnakeBody[0][2])
		{
			SnakeDirection = down;
		}
	}
	else if (GetAsyncKeyState('D'))
	{
		if (left != SnakeBody[0][2])
		{
			SnakeDirection = right;
		}
	}
	else if (GetAsyncKeyState('A'))
	{
		if (right != SnakeBody[0][2])
		{
			SnakeDirection = left;
		}
	}
}


void DestroySnake()
{
	for (int i = 0; SnakeBody[i][0] != 0; ++i)
	{
		strncpy(&background[SnakeBody[i][0]][SnakeBody[i][1]], "  ", 2);
	}
}

void SnakeMove()
{
	DestroySnake();
	for (int i = SnakeLength - 1; i >= 1; --i)
	{
		if (0 == SnakeBody[i][0])
		{
			continue;
		}
		SnakeBody[i][0] = SnakeBody[i - 1][0];
		SnakeBody[i][1] = SnakeBody[i - 1][1];
		SnakeBody[i][2] = SnakeBody[i - 1][2];
	}
	//处理蛇头
	SnakeBody[0][2] = SnakeDirection;
	if (right == SnakeBody[0][2] || left == SnakeBody[0][2])
	{
		SnakeBody[0][1] += SnakeBody[0][2];
	}
	else
	{
		SnakeBody[0][0] += SnakeBody[0][2];
	}

	DrawSnake();
}

void SetSnakeRandPosition()
{
	int x_pos = -1;
	int y_pos = -1;
	srand(time(NULL));
	x_pos = rand() % 21 + 1;//行
	y_pos = rand() % 24 + 1;//列

	SnakeBody[0][0] = x_pos;
	SnakeBody[0][1] = y_pos * 2;
	SnakeBody[0][2] = left;

	SnakeBody[1][0] = x_pos;
	SnakeBody[1][1] = y_pos * 2 + 2;
	SnakeBody[1][2] = left;

	SnakeBody[2][0] = x_pos;
	SnakeBody[2][1] = y_pos * 2 + 4;
	SnakeBody[2][2] = left;
	DrawSnake();
}

//画蛇
void DrawSnake()
{
	for (int i = 0; SnakeBody[i][0] != 0; ++i)
	{
		strncpy(&background[SnakeBody[i][0]][SnakeBody[i][1]], "■", 2);
	}
}

void ShowBackground()
{
	for (int i = 0; i < M; ++i)
	{
		printf("%s", background[i]);
	}
}

void FirstPage()
{
	printf("\t\t<<欢迎来到贪吃蛇的世界>>\n");
	printf("\t\t  <<W S A D控制方向>>\n");
	printf("\t\t  <<按空格开始游戏>>\n");
}
//play music
void MyPlaySound()
{
	PlaySound(L"Faded.wav", NULL, SND_FILENAME | SND_ASYNC);
	//绝对路径
	//相对路径
}

void TestSpace()
{
	char chInput;
	while (1)
	{
		chInput = getch();
		if (' ' == chInput)
		{
			break;
		}
	}
}
void MyStopPlay()
{
	PlaySound(NULL, 0, 0);
	//PlaySound(NULL, NULL, NULL);
}
