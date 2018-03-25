#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include <string.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

//��ʾ��ҳ
void FirstPage();

//��������
void MyPlaySound();

//���ո�
void TestSpace();

//ֹͣ����
void MyStopPlay();

//������
void ShowBackground();

//Ϊ�߲������λ��
void SetSnakeRandPosition();

//����
void DrawSnake();

void SnakeMove();

void DestroySnake();

//�ı䷽��
void ChangeDirection();
//�ж��Ƿ�����
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
	//��ʾ��ҳ
	FirstPage();
	//play music
	MyPlaySound();
	//���ո�
	TestSpace();
	//ֹͣ����
	//MyStopPlay();
	//����
	system("cls");
	//������Ϸ
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
	printf("����");
	rd.Y = 6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf(" %d", g_snake_length - 2);
	rd.Y = 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("U I O P�����ٶ�");
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

//�߳���
void SnakeGrow()
{
	//��ͷ�����ʳ�������غ�
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
	strncpy(&background[g_x_food][2 * g_y_food], "��", 2);
	Food = false;
}

//�Ƿ�����
bool IsSnakeDie()
{
	if (left == SnakeBody[0][2] || right == SnakeBody[0][2])
	{
		if (0 == strncmp(&background[SnakeBody[0][0]][SnakeBody[0][1] + SnakeBody[0][2]], "��", 2))
		{
			return false;
		}
	}
	else
	{
		if (0 == strncmp(&background[SnakeBody[0][0] + SnakeBody[0][2]][SnakeBody[0][1]], "��", 2))
		{
			return false;
		}
	}

	return true;
}

//�ı䷽��
void ChangeDirection()
{
	if (GetAsyncKeyState('W'))//����ֵshort�����ֽڲ�Ϊ�㣬˵��һֱ��W�����ֽڲ�Ϊ�㣬˵������һֱ��
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
	//������ͷ
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
	x_pos = rand() % 21 + 1;//��
	y_pos = rand() % 24 + 1;//��

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

//����
void DrawSnake()
{
	for (int i = 0; SnakeBody[i][0] != 0; ++i)
	{
		strncpy(&background[SnakeBody[i][0]][SnakeBody[i][1]], "��", 2);
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
	printf("\t\t<<��ӭ����̰���ߵ�����>>\n");
	printf("\t\t  <<W S A D���Ʒ���>>\n");
	printf("\t\t  <<���ո�ʼ��Ϸ>>\n");
}
//play music
void MyPlaySound()
{
	PlaySound(L"Faded.wav", NULL, SND_FILENAME | SND_ASYNC);
	//����·��
	//���·��
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
