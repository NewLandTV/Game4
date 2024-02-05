#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <Windows.h>

// Functions
void GraphicInit();
void GraphicUpdate();
void GraphicRelease();

void ScreenFlipping();
void ScreenPrint(unsigned int x, unsigned int y, const char* string);
void ScreenClear();

// Scenes
void DrawTitle();
void DrawCountDown();
void DrawGame();
void DrawGameOver();

// Snake Game
void DrawSnake(unsigned int x, unsigned int y);
void DrawTails(unsigned int length, unsigned int x[], unsigned int y[]);
void DrawFood(unsigned int x, unsigned int y);
void DrawScore(unsigned int score);

// Tic Tac Toe Game
void DrawBoard(unsigned char board[]);
void DrawWin(unsigned char shape);

// Dice Game
void DrawDice(unsigned int x, unsigned char number);

// Up Down Game
void DrawUpDownPosition(unsigned int snakeY, unsigned int foodY);

#endif