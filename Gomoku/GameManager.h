#pragma once
#include "Board.h"
#include "Player.h"

class GameManager
{
	Board* board;
	Player* playerX;
	Player* playerO;
	Player* currentPlayer;
	bool bGameFinished = false;
public:
	GameManager();
	virtual ~GameManager();

	bool Init();
	void ShowBoard();
	void MakeMove();
	bool isGameFinished();
};