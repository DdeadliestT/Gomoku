#include "pch.h"
#include "Board.h"

Board::Board(unsigned int boardsize)
{
	if (boardsize < 5)
	{
		std::cout << "Error: The playing field is smaller than allowed";
		_getch();
		exit(1);
	}

	this->boardsize = boardsize;
	intersections = new IntersectionType*[this->boardsize];
	for (unsigned int i = 0; i < this->boardsize; i++)
		intersections[i] = new IntersectionType[this->boardsize];

	for (unsigned int i = 0; i < this->boardsize; i++)
		for (unsigned int j = 0; j < this->boardsize; j++)
			intersections[i][j] = IntersectionType_Empty;
}

Board::~Board()
{
	for (unsigned int i = 0; i < this->boardsize; i++)
		delete[] intersections[i];
	delete[] intersections;
}

bool Board::isRowMade(unsigned int row)
{
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < boardsize; i++)
	{
		if (intersections[row][i] == IntersectionType_X)
			numX++;
		if (intersections[row][i] == IntersectionType_O)
			numO++;
	}
	if ((numX == 5) || (numO == 5))
	{
		bVictory = true;
		return true;
	}

	return false;
}

bool Board::isColumnMade(unsigned int col)
{
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < boardsize; i++)
	{
		if (intersections[i][col] == IntersectionType_X)
			numX++;
		if (intersections[i][col] == IntersectionType_O)
			numO++;
	}
	if ((numX == 5) || (numO == 5))
	{
		bVictory = true;
		return true;
	}

	return false;
}

bool Board::isDiagMade() {
	int numX = 0, numO = 0;

	// ѕроверка диагоналей с левого верхнего угла до центральной диагонали включительно
	for (unsigned int i = 0; i <= boardsize - 5; i++) {
		for (unsigned int j = 0; j <= boardsize - 5; j++) {
			numX = 0;
			numO = 0;

			for (unsigned int k = 0; k < 5; k++) {
				if (intersections[i + k][j + k] == IntersectionType_X)
					numX++;
				if (intersections[i + k][j + k] == IntersectionType_O)
					numO++;
			}

			if (numX == 5 || numO == 5) {
				bVictory = true;
				return true;
			}
		}
	}

	// ѕроверка диагоналей с правого верхнего угла до центральной диагонали включительно
	for (unsigned int i = 0; i <= boardsize - 5; i++) {
		for (unsigned int j = boardsize - 1; j >= 4; j--) {
			numX = 0;
			numO = 0;

			for (unsigned int k = 0; k < 5; k++) {
				if (intersections[i + k][j - k] == IntersectionType_X)
					numX++;
				if (intersections[i + k][j - k] == IntersectionType_O)
					numO++;
			}

			if (numX == 5 || numO == 5) {
				bVictory = true;
				return true;
			}
		}
	}

	return false;
}

bool Board::isBoardFull()
{
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < boardsize; i++)
	{
		for (unsigned int j = 0; j < boardsize; j++)
		{
			if (intersections[i][j] == IntersectionType_X)
				numX++;
			if (intersections[i][j] == IntersectionType_O)
				numO++;
		}
	}
	if ((numX + numO) == (boardsize * boardsize))
		return true;

	return false;
}

bool Board::CheckEndCondition()
{
	for (unsigned int i = 0; i < boardsize; i++)
		if (isRowMade(i) || isColumnMade(i))
			return true;
	if (isDiagMade() || isBoardFull())
		return true;

	return false;
}

bool Board::isVictory() { return bVictory; }

void Board::Show()
{
	// print column coordinate
	std::cout << "   ";
	for (unsigned int i = 0; i < this->boardsize; i++) {
		if (i < 9)
			std::cout << i + 1 << "   ";
		else
			std::cout << i + 1 << "  ";
	}

	std::cout << std::endl;
	for (unsigned int i = 0; i < this->boardsize; i++) {
		// print row coordinate
		if (i < 9)
			std::cout << i + 1 << "  ";
		else
			std::cout << i + 1 << " ";

		for (unsigned int j = 0; j < this->boardsize; j++) {
			switch (intersections[i][j])
			{
			case IntersectionType_X:
				std::cout << "X";
				break;
			case IntersectionType_O:
				std::cout << "O";
				break;
			case IntersectionType_Empty:
				std::cout << " ";
				break;
			}
			if (j != this->boardsize-1)
				std::cout << "---";
		}
		std::cout << std::endl;

		if (i != this->boardsize - 1) {
			std::cout << " ";
			for (unsigned int j = 0; j < this->boardsize - 1; j++)
				std::cout << "  | ";
			std::cout << "  |" << std::endl;
		}
	}
}

void Board::SetIntersection(unsigned int xpos, unsigned int ypos, IntersectionType it)
{
	intersections[ypos-1][xpos-1] = it;
}

bool Board::CheckLegal(unsigned int xpos, unsigned int ypos)
{
	if ((xpos < 1) || (xpos > boardsize) || (ypos < 1) || (ypos > boardsize))
		return false;
	return (intersections[ypos-1][xpos-1] == IntersectionType_Empty);
}