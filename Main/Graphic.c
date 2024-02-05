#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Graphic.h"
#include "Game.h"

// Global variables
unsigned int screenIndex;

HANDLE screen[2];

// Functions
void GraphicInit()
{
	// Create two buffers
	screen[0] = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screen[1] = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// Hide cursor
	CONSOLE_CURSOR_INFO consoleCursorInfo;

	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;

	SetConsoleCursorInfo(screen[0], &consoleCursorInfo);
	SetConsoleCursorInfo(screen[1], &consoleCursorInfo);
}

void GraphicUpdate(unsigned short flags)
{
	switch (flags)
	{
	case 0:
		ScreenClear();
		DrawTitle();

		break;
	case 1:
		ScreenClear();
		DrawCountDown();

		break;
	case 2:
		DrawGame();

		break;
	case 3:
		ScreenClear();
		DrawGameOver();

		break;
	}

	ScreenFlipping();
}

void GraphicRelease()
{
	CloseHandle(screen[0]);
	CloseHandle(screen[1]);
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(screen[screenIndex]);

	screenIndex = !screenIndex;
}

void ScreenPrint(unsigned int x, unsigned int y, const char* string)
{
	COORD position = { x, y };
	DWORD dw;

	SetConsoleCursorPosition(screen[screenIndex], position);
	WriteFile(screen[screenIndex], string, strlen(string), &dw, NULL);
}

void ScreenClear()
{
	COORD position = { 0, 0 };
	DWORD dw;

	FillConsoleOutputCharacter(screen[screenIndex], ' ', CONSOLE_WIDTH * CONSOLE_HEIGHT, position, &dw);
}

// Scenes
void DrawTitle()
{
	int x = CONSOLE_WIDTH >> 2;
	int y = CONSOLE_HEIGHT >> 2;

	ScreenPrint((CONSOLE_WIDTH >> 1) - 4, 3, "G A M E 4");
	ScreenPrint(x, y, "¦£");
	ScreenPrint(x * 3, y, "¦¤");
	ScreenPrint(x * 2, y * 2, "¦«");
	ScreenPrint(x, y * 3, "¦¦");
	ScreenPrint(x * 3, y * 3, "¦¥");
}

void DrawCountDown()
{
	ScreenPrint(CONSOLE_WIDTH >> 1, 10, "3");
	ScreenFlipping();
	Sleep(1000);
	ScreenClear();
	ScreenPrint(CONSOLE_WIDTH >> 1, 10, "2");
	ScreenFlipping();
	Sleep(1000);
	ScreenClear();
	ScreenPrint(CONSOLE_WIDTH >> 1, 10, "1");
	ScreenFlipping();
	Sleep(1000);
	ScreenClear();
	ScreenPrint((CONSOLE_WIDTH >> 1) - 1, 10, "GO!");
	ScreenFlipping();
	Sleep(1000);
	ScreenClear();
}

void DrawGame()
{
	for (int x = 0; x < CONSOLE_WIDTH; x += 2)
	{
		for (int y = 0; y < CONSOLE_HEIGHT; y++)
		{
			if (x == 2 || x == CONSOLE_WIDTH - 4 || y == 1 || y == CONSOLE_HEIGHT - 2)
			{
				ScreenPrint(x, y, "¡á");
			}
		}
	}
}

void DrawGameOver()
{
	ScreenPrint((CONSOLE_WIDTH >> 1) - 7, 5, "- GAME OVER! -");
}

// Snake Game
void DrawSnake(unsigned int x, unsigned int y)
{
	ScreenClear();
	ScreenPrint(x, y, "¡à");
}

void DrawTails(unsigned int length, unsigned int x[], unsigned int y[])
{
	for (int i = 0; i < length; i++)
	{
		ScreenPrint(x[i], y[i], "¡Ü");
	}
}

void DrawFood(unsigned int x, unsigned int y)
{
	ScreenPrint(x, y, "¡Ú");
}

void DrawScore(unsigned int score)
{
	char buffer[20];

	sprintf_s(buffer, 20, "SCORE : %010u", score);
	ScreenPrint((CONSOLE_WIDTH >> 1) - (strlen(buffer) >> 1), 0, buffer);
}

// Tic Tac Toe Game
void DrawBoard(unsigned char board[])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (board[i + j * 3])
			{
			case 0:
				ScreenPrint(i + 4, j + 2, "-");

				break;
			case 1:
				ScreenPrint(i + 4, j + 2, "X");

				break;
			case 2:
				ScreenPrint(i + 4, j + 2, "O");

				break;
			}
		}
	}
}

void DrawWin(unsigned char shape)
{
	ScreenClear();
	ScreenPrint(9, 3, shape);
	ScreenPrint(11, 3, "Won!");
	ScreenFlipping();
}

// Dice Game
void DrawDice(unsigned int x, unsigned char number)
{
	ScreenClear();

	switch (number)
	{
	case 1:
		ScreenPrint(x, CONSOLE_HEIGHT - 3, "¡Ý");

		break;
	case 2:
		ScreenPrint(x - 2, CONSOLE_HEIGHT - 4, "¡Ý");
		ScreenPrint(x + 2, CONSOLE_HEIGHT - 2, "¡Ý");

		break;
	case 3:
		ScreenPrint(x - 2, CONSOLE_HEIGHT - 4, "¡Ý");
		ScreenPrint(x, CONSOLE_HEIGHT - 3, "¡Ý");
		ScreenPrint(x + 2, CONSOLE_HEIGHT - 2, "¡Ý");

		break;
	case 4:
		ScreenPrint(x - 2, CONSOLE_HEIGHT - 4, "¡Ý");
		ScreenPrint(x + 2, CONSOLE_HEIGHT - 4, "¡Ý");
		ScreenPrint(x - 2, CONSOLE_HEIGHT - 2, "¡Ý");
		ScreenPrint(x + 2, CONSOLE_HEIGHT - 2, "¡Ý");

		break;
	case 5:
		ScreenPrint(x - 2, CONSOLE_HEIGHT - 4, "¡Ý");
		ScreenPrint(x + 2, CONSOLE_HEIGHT - 4, "¡Ý");
		ScreenPrint(x, CONSOLE_HEIGHT - 3, "¡Ý");
		ScreenPrint(x - 2, CONSOLE_HEIGHT - 2, "¡Ý");
		ScreenPrint(x + 2, CONSOLE_HEIGHT - 2, "¡Ý");

		break;
	case 6:
		ScreenPrint(x - 2, CONSOLE_HEIGHT - 4, "¡Ý");
		ScreenPrint(x - 2, CONSOLE_HEIGHT - 3, "¡Ý");
		ScreenPrint(x - 2, CONSOLE_HEIGHT - 2, "¡Ý");
		ScreenPrint(x + 2, CONSOLE_HEIGHT - 4, "¡Ý");
		ScreenPrint(x + 2, CONSOLE_HEIGHT - 3, "¡Ý");
		ScreenPrint(x + 2, CONSOLE_HEIGHT - 2, "¡Ý");

		break;
	}

	ScreenFlipping();
}

// Up Down Game
void DrawUpDownPosition(unsigned int snakeY, unsigned int foodY)
{
	ScreenPrint(0, 10, snakeY > foodY ? "¡è" : snakeY < foodY ? "¡é" : "¡ë");
}