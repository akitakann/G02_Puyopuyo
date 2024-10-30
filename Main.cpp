//////////////////////////////////////////////////////////////////////////////////
//				G02_ぷよぷよ

#include<iostream>
#include<time.h>
#include<windows.h>

//////////////////////////////////////////////////////////////////////////////////
//				マクロ定義					  

#define MAP_Y (15)
#define MAP_X (8)

//////////////////////////////////////////////////////////////////////////////////
//				列挙体

enum {
	EMPTY = 0,
	PUYO_1, //赤
	PUYO_2, //緑
	PUYO_3, //黄
	PUYO_4, //青

	WALL = 9,
};

enum {
	BLACK = 0,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	GRAY,
	RESET = 9
};

//////////////////////////////////////////////////////////////////////////////////
//				構造体

struct MOVEPUYO
{
	int color = 0;
	int x = 0;
	int y = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//				グローバル変数


int g_Map[MAP_Y][MAP_X] = {};


//////////////////////////////////////////////////////////////////////////////////
//				プロトタイプ宣言

void MapSetup();
void DisplayMap(MOVEPUYO,MOVEPUYO);
void ColorPallet(int color);


//////////////////////////////////////////////////////////////////////////////////
//				プログラム本文

int main(void)
{
	srand(time(NULL));
	MapSetup();

	MOVEPUYO puyoA;
	puyoA.color = rand() % 4 + 1;
	puyoA.x = 3;
	puyoA.y = 0;

	MOVEPUYO puyoB;
	puyoB.color = rand() % 4 + 1;
	puyoB.x = 4;
	puyoB.y = 0;

	int nowMode = 0;


	while (true)
	{
		if (g_Map[puyoA.y + 1][puyoA.x] != EMPTY || g_Map[puyoB.y + 1][puyoB.x] != EMPTY)
		{
			g_Map[puyoA.y][puyoA.x] = puyoA.color;
			g_Map[puyoB.y][puyoB.x] = puyoB.color;

			puyoA.color = rand() % 4 + 1;
			puyoA.x = 3;
			puyoA.y = 0;

			puyoB.color = rand() % 4 + 1;
			puyoB.x = 4;
			puyoB.y = 0;

		}

		puyoA.y++;
		puyoB.y++;

		

		DisplayMap(puyoA,puyoB);
		Sleep(1000);
	}
}


void MapSetup()
{
	for (int Y = 0; Y < MAP_Y; Y++)
	{
		for (int X = 0; X < MAP_X; X++)
		{
			if (X == 0 || X == MAP_X - 1 || Y == MAP_Y - 1)
			{
				g_Map[Y][X] = WALL;
			}
		}
	}
}

void DisplayMap(MOVEPUYO puyoA,MOVEPUYO puyoB)
{
	system("cls");
	for (int Y = 0; Y < MAP_Y; Y++)
	{
		for (int X = 0; X < MAP_X; X++)
		{
			if (X == puyoA.x && Y == puyoA.y)
			{
				ColorPallet(puyoA.color);
				std::cout << "●";
				ColorPallet(RESET);
			}
			else if (X == puyoB.x && Y == puyoB.y)
			{
				ColorPallet(puyoB.color);
				std::cout << "●";
				ColorPallet(RESET);
			}
			else if (g_Map[Y][X] == EMPTY)
			{
				std::cout << "　";
			}
			else if (g_Map[Y][X] == PUYO_1)
			{
				ColorPallet(RED);
				std::cout << "●";
				ColorPallet(RESET);
			}
			else if (g_Map[Y][X] == PUYO_2)
			{
				ColorPallet(GREEN);
				std::cout << "●";
				ColorPallet(RESET);
			}
			else if (g_Map[Y][X] == PUYO_3)
			{
				ColorPallet(YELLOW);
				std::cout << "●";
				ColorPallet(RESET);
			}
			else if (g_Map[Y][X] == PUYO_4)
			{
				ColorPallet(BLUE);
				std::cout << "●";
				ColorPallet(RESET);
			}
			else if (g_Map[Y][X] == WALL)
			{
				std::cout << "■";
			}
		}
		std::cout << "\n";
	}
}




void ColorPallet(int color)
{
	switch (color)
	{
	case BLACK:
		std::cout << "\x1b[30m";
		break;
	case RED:
		std::cout << "\x1b[31m";
		break;
	case GREEN:
		std::cout << "\x1b[32m";
		break;
	case YELLOW:
		std::cout << "\x1b[33m";
		break;
	case BLUE:
		std::cout << "\x1b[34m";
		break;
	case MAGENTA:
		std::cout << "\x1b[35m";
		break;
	case CYAN:
		std::cout << "\x1b[36m";
		break;
	case GRAY:
		std::cout << "\x1b[37m";
		break;
	case RESET:
		std::cout << "\x1b[39m";
	default:
		break;
	}
}