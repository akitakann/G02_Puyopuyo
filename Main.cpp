//////////////////////////////////////////////////////////////////////////////////
//				G02_ぷよぷよ

#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

//////////////////////////////////////////////////////////////////////////////////
//				マクロ定義					  

#define MAP_Y (15)
#define MAP_X (8)
#define FALL_SPEED (10)

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

enum {
	NORMAL = 0,
	FALL,
	RENSA 
};


//////////////////////////////////////////////////////////////////////////////////
//				構造体

struct MOVEPUYO
{
	int color = 0;
	int x = 3;
	int y = 0;

	int oldX = x;
	int oldY = y;

};


//////////////////////////////////////////////////////////////////////////////////
//				グローバル変数

int g_NewMap[MAP_Y][MAP_X] = {};


//////////////////////////////////////////////////////////////////////////////////
//				プロトタイプ宣言

void MapSetup();
void DisplayMap(MOVEPUYO, MOVEPUYO, int oldMap[MAP_Y][MAP_X], int);
void ColorPallet(int color);
int PuyoFalling();
int PuyoDelete();
void PuyoNakama(int Y, int X, int ExploredPuyo[MAP_Y][MAP_X], int PuyoNakamaNum[MAP_Y][MAP_X]);
MOVEPUYO PuyoUpdate(MOVEPUYO);


//////////////////////////////////////////////////////////////////////////////////
//				プログラム本文

void MoveCursorV2(int Y, int X) {
	std::cout << "\033[" << Y + 1 << ";" << X * 2 + 1 << "H";
}

int main(void)
{
	srand(time(NULL));
	MapSetup();

	int oldMap[MAP_Y][MAP_X] = {};

	int mode = NORMAL;
	int key;
	int frameCount = 0;

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
		for (int i = 0; i < MAP_Y; i++)
		{
			for (int j = 0; j < MAP_X; j++)
			{
				oldMap[i][j] = g_NewMap[i][j];
			}
		}

		if (mode == RENSA)
		{

		}

		if (mode == FALL)
		{
			// マップ描画時に配置した直後のぷよが消されないようにする
			puyoA.oldX = 20;
			puyoA.oldY = 20;
			puyoB.oldX = 20;
			puyoB.oldY = 20;

			int falledPuyo = 0;
			falledPuyo = PuyoFalling();
			if (falledPuyo == 0)
			{
				mode = NORMAL;
			}
		}

		if (mode == NORMAL && (g_NewMap[puyoA.y + 1][puyoA.x] != EMPTY || g_NewMap[puyoB.y + 1][puyoB.x] != EMPTY))
		{
			g_NewMap[puyoA.y][puyoA.x] = puyoA.color;
			g_NewMap[puyoB.y][puyoB.x] = puyoB.color;

			puyoA = PuyoUpdate(puyoA);
			puyoB = PuyoUpdate(puyoB);
			
			puyoA.color = rand() % 4 + 1;
			puyoA.x = 3;
			puyoA.y = 0;

			puyoB.color = rand() % 4 + 1;
			puyoB.x = 4;
			puyoB.y = 0;



			mode = FALL;
		}
		else if (mode == NORMAL)
		{

			if (_kbhit())
			{
				//入力されたキーを代入
				key = _getch();

				puyoA = PuyoUpdate(puyoA);
				puyoB = PuyoUpdate(puyoB);

				if (key == 'd' && g_NewMap[puyoA.y][puyoA.x + 1] == EMPTY && g_NewMap[puyoB.y][puyoB.x + 1] == EMPTY)
				{
					puyoA.x++;
					puyoB.x++;
				}
				else if (key == 'a' && g_NewMap[puyoA.y][puyoA.x - 1] == EMPTY && g_NewMap[puyoB.y][puyoB.x - 1] == EMPTY)
				{
					puyoA.x--;
					puyoB.x--;
				}
				else if (key == 's' && g_NewMap[puyoA.y + 1][puyoA.x] == EMPTY && g_NewMap[puyoB.y + 1][puyoB.x] == EMPTY)
				{
					puyoA.y++;
					puyoB.y++;
				}
				DisplayMap(puyoA, puyoB, oldMap,mode);
			}

			frameCount++;
			if (frameCount == 5 && g_NewMap[puyoA.y + 1][puyoA.x] == EMPTY && g_NewMap[puyoB.y + 1][puyoB.x] == EMPTY)
			{
				puyoA = PuyoUpdate(puyoA);
				puyoB = PuyoUpdate(puyoB);
				puyoA.y++;
				puyoB.y++;
				frameCount = 0;
			}
			else if (frameCount == FALL_SPEED)
			{
				frameCount = 0;
			}
		}

		DisplayMap(puyoA,puyoB,oldMap,mode);
		Sleep(50);
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
				g_NewMap[Y][X] = WALL;
				
			}

			if (g_NewMap[Y][X] == WALL)
			{
				std::cout << "■";
			}
			else
			{
				std::cout << "　";
			}
		}
		std::cout << "\n";
	}
}

void DisplayMap(MOVEPUYO puyoA,MOVEPUYO puyoB,int oldMap[MAP_Y][MAP_X],int mode)
{
	MoveCursorV2(puyoA.oldY, puyoA.oldX);
	std::cout << "　";
	
	MoveCursorV2(puyoB.oldY, puyoB.oldX);
	std::cout << "　";

	MoveCursorV2(puyoA.y, puyoA.x);
	ColorPallet(puyoA.color);
	std::cout << "●";

	MoveCursorV2(puyoB.y, puyoB.x);
	ColorPallet(puyoB.color);
	std::cout << "●";
	ColorPallet(RESET);

	for (int Y = 0; Y < MAP_Y; Y++)
	{
		for (int X = 0; X < MAP_X; X++)
		{
			if (oldMap[Y][X] != g_NewMap[Y][X])
			{
				MoveCursorV2(Y,X);
				if (g_NewMap[Y][X] == PUYO_1)
				{
					ColorPallet(RED);
					std::cout << "●";
					ColorPallet(RESET);
				}
				else if (g_NewMap[Y][X] == PUYO_2)
				{
					ColorPallet(GREEN);
					std::cout << "●";
					ColorPallet(RESET);
				}
				else if (g_NewMap[Y][X] == PUYO_3)
				{
					ColorPallet(YELLOW);
					std::cout << "●";
					ColorPallet(RESET);
				}
				else if (g_NewMap[Y][X] == PUYO_4)
				{
					ColorPallet(BLUE);
					std::cout << "●";
					ColorPallet(RESET);
				}
				else if (g_NewMap[Y][X] == WALL)
				{
					std::cout << "■";
				}
				else if (g_NewMap[Y][X] == EMPTY)
				{
					std::cout << "　";
				}
			}
		}
	}
	MoveCursorV2(100, 100);
}

MOVEPUYO PuyoUpdate(MOVEPUYO puyo)
{
	puyo.oldX = puyo.x;
	puyo.oldY = puyo.y;
	return puyo;
}

int PuyoFalling()
{
	int fallCount = 0;
	for (int Y = MAP_Y - 2; Y > 0; Y--)
	{
		for (int X = MAP_X - 1; X > 0; X--)
		{
			if ((g_NewMap[Y][X] == PUYO_1 || g_NewMap[Y][X] == PUYO_2 || g_NewMap[Y][X] == PUYO_3 || g_NewMap[Y][X] == PUYO_4) && g_NewMap[Y + 1][X] == EMPTY)
			{
				g_NewMap[Y + 1][X] = g_NewMap[Y][X];
				g_NewMap[Y][X] = EMPTY;
				fallCount++;
			}
		}
	}
	return fallCount;
}

int PuyoDelete()
{
	int ExploredPuyo[MAP_Y][MAP_X] = {};
	int PuyoNakamaNum[MAP_Y][MAP_X] = {};

	for (int Y = 0; Y < MAP_Y; Y++)
	{
		for (int X = 0; X < MAP_X; X++)
		{
			if (PuyoNakamaNum[Y][X] == 0)
			{
				PuyoNakama(Y, X, ExploredPuyo, PuyoNakamaNum);
			}
		}
	}

}

void PuyoNakama(int Y,int X, int ExploredPuyo[MAP_Y][MAP_X], int PuyoNakamaNum[MAP_Y][MAP_X])
{
	ExploredPuyo[Y][X] = 1;

	if (g_NewMap[Y][X])
	{

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