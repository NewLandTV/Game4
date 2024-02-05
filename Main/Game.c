#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include "Game.h"
#include "Graphic.h"
#include "Input.h"
#include "Sound.h"

// Enums
typedef enum _Direction
{
	Left,
	Right,
	Up,
	Down
} Direction;

// Structs
typedef struct _Snake
{
	Direction direction;

	unsigned int x;
	unsigned int y;
	unsigned int length;
	unsigned int score;
} Snake;

// Global variables
clock_t startTimer;
Snake snake;

unsigned int foodX;
unsigned int foodY;
unsigned int tailsX[100];
unsigned int tailsY[100];
unsigned char ticTacToeBoard[9];
unsigned char xTurn;
unsigned short flags;

// Functions
void Init()
{
	// Random seed set
	srand((unsigned int)time(NULL));

	// Setup console
	system("title Game 4");
	system("mode con cols=88 lines=44");

	// Init
	GraphicInit();
}

void Update()
{
	GraphicUpdate(flags);

	switch (flags)
	{
	case 0:
		while (!GetAnyKey());

		flags = 1;

		break;
	case 1:
		flags = 2;

		InitSnake();
		InitTicTacToe();
		Food();

		break;
	case 2:
		// Eat food
		if (snake.x == foodX && snake.y == foodY)
		{
			Food();
			TicTacToeMarker(xTurn);
			CheckTicTacToeWin();

			xTurn = xTurn == 1 ? 2 : 1;
			tailsX[snake.length] = tailsX[snake.length - 1];
			tailsY[snake.length] = tailsY[snake.length - 1];
			snake.length++;
		}

		// Check collision to wall
		if (snake.x == 2 || snake.x == CONSOLE_WIDTH - 4 || snake.y == 1 || snake.y == CONSOLE_HEIGHT - 2)
		{
			flags = 3;

			return;
		}

		// Check collision to self
		for (int i = 3; i < snake.length; i++)
		{
			if (snake.x == tailsX[i] && snake.y == tailsY[i])
			{
				flags = 3;

				return;
			}
		}

		// Move snake
		for (int i = snake.length - 1; i > 0; i--)
		{
			tailsX[i] = tailsX[i - 1];
			tailsY[i] = tailsY[i - 1];
		}

		switch (snake.direction)
		{
		case Left:
			snake.x -= 2;
			tailsX[0] = snake.x + 2;
			tailsY[0] = snake.y;

			break;
		case Right:
			snake.x += 2;
			tailsX[0] = snake.x - 2;
			tailsY[0] = snake.y;

			break;
		case Up:
			snake.y--;
			tailsX[0] = snake.x;
			tailsY[0] = snake.y + 1;

			break;
		case Down:
			snake.y++;
			tailsX[0] = snake.x;
			tailsY[0] = snake.y - 1;

			break;
		}

		// Input process
		if ((GetKeyDown('A') || GetKeyDown('a')) && snake.direction != Right)
		{
			snake.direction = Left;
		}
		if ((GetKeyDown('D') || GetKeyDown('d')) && snake.direction != Left)
		{
			snake.direction = Right;
		}
		if ((GetKeyDown('W') || GetKeyDown('w')) && snake.direction != Down)
		{
			snake.direction = Up;
		}
		if ((GetKeyDown('S') || GetKeyDown('s')) && snake.direction != Up)
		{
			snake.direction = Down;
		}
		if (GetKeyDown(' '))
		{
			RollDice();
		}

		// Draw
		DrawSnake(snake.x, snake.y);
		DrawTails(snake.length, tailsX, tailsY);
		DrawFood(foodX, foodY);
		DrawScore(snake.score);
		DrawBoard(ticTacToeBoard);
		DrawUpDownPosition(snake.y, foodY);
		Sleep(70);

		break;
	case 3:
		Sleep(1000);

		while (!GetAnyKey());

		flags = 1;

		break;
	}
}

void Release()
{
	GraphicRelease();
}

void InitSnake()
{
	snake.direction = Right;
	snake.x = (CONSOLE_WIDTH >> 1) - 6;
	snake.y = CONSOLE_HEIGHT >> 1;
	snake.length = 3;
	snake.score = 0;

	for (int i = 0; i < snake.length; i++)
	{
		tailsX[i] = (CONSOLE_WIDTH >> 1) - i * 2 - 8;
		tailsY[i] = CONSOLE_HEIGHT >> 1;
	}
}

void InitTicTacToe()
{
	memset(ticTacToeBoard, 0, sizeof(ticTacToeBoard));

	for (int i = 0; i < 9; i++)
	{
		ticTacToeBoard[i] = 0;
	}

	xTurn = 1;
}

void Food()
{
	foodX = rand() % (CONSOLE_WIDTH - 8) + 4;
	foodY = rand() % (CONSOLE_HEIGHT - 4) + 2;

	if (foodX & 1)
	{
		Food();

		return;
	}

	if (foodX >= 4 && foodX <= 8 && foodY >= 2 && foodY <= 4)
	{
		Food();

		return;
	}

	for (int i = 0; i < snake.length; i++)
	{
		if (foodX == tailsX[i] && foodY == tailsY[i])
		{
			Food();

			return;
		}
	}

	snake.score++;
}

void TicTacToeMarker(unsigned char shape)
{
	int x = rand() % 3;
	int y = rand() % 3;

	if (ticTacToeBoard[x + y * 3])
	{
		TicTacToeMarker(shape);
	}

	ticTacToeBoard[x + y * 3] = shape;
}

void CheckTicTacToeWin()
{
	// X Win
	if ((ticTacToeBoard[0] == 1 && ticTacToeBoard[3] == 1 && ticTacToeBoard[6] == 1) || (ticTacToeBoard[1] == 1 && ticTacToeBoard[4] == 1 && ticTacToeBoard[7] == 1) || (ticTacToeBoard[2] == 1 && ticTacToeBoard[5] == 1 && ticTacToeBoard[8] == 1) || (ticTacToeBoard[0] == 1 && ticTacToeBoard[1] == 1 && ticTacToeBoard[2] == 1) || (ticTacToeBoard[3] == 1 && ticTacToeBoard[4] == 1 && ticTacToeBoard[5] == 1) || (ticTacToeBoard[6] == 1 && ticTacToeBoard[7] == 1 && ticTacToeBoard[8] == 1) || (ticTacToeBoard[0] == 1 && ticTacToeBoard[4] == 1 && ticTacToeBoard[8] == 1) || (ticTacToeBoard[2] == 1 && ticTacToeBoard[4] == 1 && ticTacToeBoard[6] == 1))
	{
		DrawWin(1);
		Sleep(1000);
		InitTicTacToe();

		return;
	}

	// O Win
	if ((ticTacToeBoard[0] == 2 && ticTacToeBoard[3] == 2 && ticTacToeBoard[6] == 2) || (ticTacToeBoard[1] == 2 && ticTacToeBoard[4] == 2 && ticTacToeBoard[7] == 2) || (ticTacToeBoard[2] == 2 && ticTacToeBoard[5] == 2 && ticTacToeBoard[8] == 2) || (ticTacToeBoard[0] == 2 && ticTacToeBoard[1] == 2 && ticTacToeBoard[2] == 2) || (ticTacToeBoard[3] == 2 && ticTacToeBoard[4] == 2 && ticTacToeBoard[5] == 2) || (ticTacToeBoard[6] == 2 && ticTacToeBoard[7] == 2 && ticTacToeBoard[8] == 2) || (ticTacToeBoard[0] == 2 && ticTacToeBoard[4] == 2 && ticTacToeBoard[8] == 2) || (ticTacToeBoard[2] == 2 && ticTacToeBoard[4] == 2 && ticTacToeBoard[6] == 2))
	{
		DrawWin(2);
		Sleep(1000);
		InitTicTacToe();
	}
}

void RollDice()
{
	unsigned char number = rand() % 6 + 1;

	DrawDice(snake.x, number);

	snake.score += number;

	Sleep(1000);
}