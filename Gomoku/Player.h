#pragma once
#include "Board.h"

class Player
{
	Board* board;
	IntersectionType intersectionType;
	std::string name;

	std::chrono::seconds remainingTime{ 900 }; // 900 = 15 minutes in seconds
	bool isTimerPaused = true;
public:
	Player() {};
	virtual ~Player();

	std::chrono::seconds GetRemainingTime() { return remainingTime; };
	void PauseTimer() { isTimerPaused = true; };
	void StartTimerAsync();

	void SetupPlayer(std::string name, IntersectionType intersectionType);
	void SetBoard(Board* board) { this->board = board; };
	bool MakeMove();
	std::string GetName();
	bool CheckInput(char* p_str);
};