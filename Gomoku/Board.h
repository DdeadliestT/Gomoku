#pragma once
#include "IntersectionType.h"

class Board
{
	unsigned int boardsize; // from 5 to infinity
	IntersectionType** intersections;
	bool bVictory = false;
	bool isRowMade(unsigned int row);
	bool isColumnMade(unsigned int col);
	bool isDiagMade();
	bool isBoardFull();
public:
	Board(unsigned int boardsize);
	virtual ~Board();

	void Show();
	void SetIntersection(unsigned int xpos, unsigned int ypos, IntersectionType it);
	bool CheckLegal(unsigned int xpos, unsigned int ypos);
	bool CheckEndCondition();
	bool isVictory();
};