#ifndef __GAME_H__
#define __GAME_H__

#define CONSOLE_WIDTH 88
#define CONSOLE_HEIGHT 44

// Functions
void Init();
void Update();
void Release();

void InitSnake();
void InitTicTacToe();
void Food();
void TicTacToeMarker(unsigned char shape);
void CheckTicTacToeWin();
void RollDice();

#endif